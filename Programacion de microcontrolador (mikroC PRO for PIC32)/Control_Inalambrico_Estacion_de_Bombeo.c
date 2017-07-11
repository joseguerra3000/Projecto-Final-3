/**************************************************
 * Universidad de Pinar del Rio
 * Facultad de Ciencias Técnicas
 * Carrera de Telecomunicaciones y Electrónica
 **************************************************
 * Proyecto: Proyecto Final de 3er Año
 * Nombre  : Control Remoto de Estación de Bombeo
 * Autores :
 *     - Jose Guerra Carmenate
 *     - Leonardo Gonzales Reyes
 * Placa de Desarrollo: 
 *     - Digilent Cerebot 32MX4 @ 80 MHz
 **************************************************/
/**Bibliotecas**/
#include "CEREBOT32MX4.h"
#include "CyclicBuffer.h"
#include <stdbool.h>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;

/***** Modulo WIFI Begin *****/
/*Constantes*/
const uchar* ATcommand[] = {  //Indices de los comandos AT a ejecutar
  /*CONFIGURACION AT*/
  "AT", //Comprueba el modulo AT en el ESP8266--> ans: OK.
  "AT+RST", //Reinicia el ESP8266 --> ans: OK.
  "ATE", //Configura el Eco de Comandos --> ans: OK.
  /*CONFIGURACION DE WIFI*/
  "AT+CWMODE",//Configura el modo de trabajo del modulo ESP8266 --> OK.
  "AT+CWSAP",//Configura los parametros de SoftAP. --> OK.
  "AT+CWDHCP",//Configura el DHCP. --> OK.
  /*CONFIGURACION DE TCP/IP*/
  "AT+CIPMUX",//Enable or Disable Multiple Connections  --> ans: OK
  "AT+CIPSERVER",//Deletes/Creates TCP Server   --> OK.
  "AT+CIFSR"//Gets the Local IP Address
};
const char *ATappend[] = { // Parametros de los comandos AT a ejecutar
  "",
  "",
  "0",//0 - Apaga el eco de comandos
  "=2",//Configura el ESP8266 en modo SoftAP.
  "=\"ESTACION\",\"digilentcerebot\",1,2",// configura los parametros del modo SoftAP.
  "=0,1",//Activa el DHCP para el SoftAP.
  "=1",//Activa conexiones multiples
  "=1,5656",//Crea Servidor TCP en puerto 5656
  ""
};
const char *ATnotify[] = { //Notificacion a enviar al PC para cada Comando
   "Comprobando Modulo AT de ESP8266...\0",
   "Reiniciando Modulo ESP8266...\0",
   "Apagando el Eco de Commandos...\0",
   "Configurando Modulo ESP8266 como SoftAP...\0",
   "Configurando Access Point...\0",
   "Activando DHCP...\0",
   "Activando Conexiones Multiples...\0",
   "Creando Servidor TCP...\0",
   "Obteniendo Direccion IP Local...\0"
};
/*Funciones*/
int WIFI_Init();
void WIFI_Wait_Init();
bool WIFI_Send( unsigned short user, uchar *message, uint size );
/*****Modulo WIFI End*****/

/*****Buffer and Stack Begin*****/
//Buffer Vars
const int MAX_BUFF_STORAGE = 512;
Buffer WIFI_input;
uchar __buff_storage[MAX_BUFF_STORAGE+10];
/*****Buffer End*****/

/*****Metodos Generales Begin*****/
/*SETUP*/
void Setup();//Inicializa el uC
void Timer1_Config();//Configura el Timer1 para la alarma
bool Get_And_Procces_Data( const char *dat );
/*Send to PC*/
void Send_To_PC( const uchar *s );//Envia un string via UART1
void uint_to_str( unsigned int n, char *out );
/*****Metodos Generales End*****/

/*****Variables Globales del Sistema Begin*****/
#define Tanque_estado CEREBOT_PORTJE_7_bit   //( 0-No Lleno, 1-Lleno )
#define Buzzer_estado CEREBOT_LATJE_8_bit   //( 0-OFF, 1-ON )
#define Bomba_estado CEREBOT_LATJE_9_bit    //( 0-OFF, 1-ON )
#define Cisterna_estado         1            //( 0-Vacio, 1-No Vacio ) --->NO USADO.
ushort Control_estado=1;                     //( 0-manual, 1-automatico )
char output_state[600];//aqui se almacena la trama que se envia al cliente

char input[600];       //aqui se almacenan los datos recividos desde el modulo
                        //wifi al sacarlos del buffer
bool user_connected = 0;//indica si la aplicacion de control esta conectada
const uchar *NO_LLENO = "No Lleno",
            *LLENO = "Lleno";
const uchar *ROOT_LABEL = "Estacion_de_bombeo",
            *TANQUE_LABEL = "Tanque_Elevado",
            *CISTERNA_LABEL = "Cisterna",
            *BOMBA_LABEL = "Bomba",
            *BUZZER_LABEL = "Buzzer",
            *CONTROL_LABEL = "Control";
const uchar *Nombre_Estacion = "Central de Bombeo";
/*****Variables Globales del Sistema End*****/

uchar* getStringDeEstado( ushort num_de_estado ){
        if( num_de_estado == 0 ) return (uchar*)NO_LLENO;
        if( num_de_estado == 1 ) return (uchar*)LLENO;
        return "";
}

/*****Analisis de Trama Begin*****/
//Analiza si t es una trama valida (1-valida, 0-invalida)
//int Check( const uchar *t );

//Crea una trama con el estado actual del sistema
void GenerarTrama( uchar *trama );

/* Crea etiqueta de apertura en 'to' con nombre 'name' y dos attributo( attrib1 , attrib2 ) con sus
 * respectivos valores( value1 , value2 ). Retorna la cantidad de caracteres agregados.
 * Si attrib(1|2) = "" este no se agrega a la etiqueta.
 */
int getOpenLabel( uchar *to, uchar *name, uchar *attrib1, uchar *value1 , uchar *attrib2 , uchar *value2  );

//Crea etiqueta de Cierre en to con nombre name. Retorna la cantidad de caracteres agregados.
int getCloseLabel( uchar *to, uchar *name );

/**Utilizamos los valores hash para comparar si dos strings son iguales**/
const uint hash_P = 53;//Numero Primo utilizado como Base en el Hash
uint get_Hash( uchar *s, int len ); //Devuelve un hash del string s
/*****Analisis de Trama End*****/


/*****Interrupciones Begin**/
/*Interrupciones UART2*/
void uart2_interrupt() iv IVT_UART_2 ilevel 7 ics ICS_SRS { ///MODULO WIFI
  if( IFS1bits.U2RXIF  ){
    uchar t = UART2_Read();
    Buffer_PushData( &WIFI_input, t );
    IFS1bits.U2RXIF = 0;
  }
  if( IFS1bits.U2TXIF ){
    IEC1bits.U2TXIE = 0;        // Disable UART2 TX ISR
    IFS1bits.U2TXIF = 0;
  }
}
/*Interrupciones UART1*/
void uart1_interrupt() iv IVT_UART_1 ilevel 6 ics ICS_AUTO {// Terminal Serie en PC
  if( IFS0bits.U1RXIF ){
    //UART1_Read();
    UART2_Write( UART1_Read() );
    IFS0bits.U1RXIF = 0;
  }
  if( IFS0bits.U1TXIF ){
      IEC0bits.U1TXIE = 0;        // Disable UART1 TX ISR
      IFS0bits.U1TXIF = 0;
  }
}
/*Interrupcion Timer1*/
void timer1_interrupt() iv IVT_TIMER_1 ilevel 5 ics ICS_SOFT {
  Buzzer_estado = ~Buzzer_estado;
  T1IF_bit = 0; // Clear T1IF.
}

/*****Interrupciones End*****/

void main(){
  char *ptr; //puntero para trabajo
  char num[10];
  delay_ms(200);
  user_connected = 0;
  Setup();
  delay_ms(1000);
  WIFI_Wait_Init();

  //Timer1_Enable();
  Delay_ms(1000);
  while(1){
    while( !user_connected ){
      CEREBOT_LED2_LAT = ~CEREBOT_LED2_LAT;
      if( Buffer_Data_Ready( &WIFI_input ) ){
        Buffer_GetAllData( &WIFI_input, input );
        Send_To_PC("no_conected input: ");
        Send_To_PC(input);
        if( strstr( input, "0,CONNECT" ) != 0 ){
          user_connected = 1;
          Control_estado = 0;
        }
      }
     if( Control_estado == 1 ){ //Si esta en automatico
        if( Tanque_estado == 1 ){ //y el tanque esta lleno
        Bomba_estado = 0;                              //apaga bomba
        T1CONbits.ON = 1;                              //enciende alarma
        }
        else{                                          //sino esta lleno
          T1CONbits.ON = 0;                            //apaga alarma
          Buzzer_estado = 0;
        }
      }
      delay_ms(400);
    }
     GenerarTrama(output_state);
    WIFI_Send(0, output_state, strlen(output_state));
    //Buffer_GetAllData( &WIFI_input, input );
    delay_ms(300);

    delay_ms(400);
    CEREBOT_LED3_LAT = ~CEREBOT_LED3_LAT;
    if( Buffer_Data_Ready( &WIFI_input ) ){
      Buffer_GetAllData( &WIFI_input, input );
      /*Send_To_PC("input("); int_to_str((uint)strlen(input), num);
      Send_To_PC( num );
      Send_To_PC( "): " );
      Send_To_PC(input);   */

      ptr = strstr(input, "CONNECT FAIL");
      if( ptr ){
        user_connected = 0;
        delay_ms( 500 );
        WIFI_Wait_Init();
        continue;
      }
      ptr = strstr( input, "0,CLOSED" );
      if( ptr ){
        user_connected = 0;
        Control_estado = 1;
        continue;
      }
      ptr = strstr(input, "+IPD,");
      if( ptr ){ //Datos provenientes del cliente
          Get_And_Procces_Data( ptr );
      }
      if( Control_estado == 1 ){ //Si esta en automatico
        if( Tanque_estado == 1 ){ //y el tanque esta lleno
        Bomba_estado = 0;                              //apaga bomba
        T1CONbits.ON = 1;                              //enciende alarma
        }
        else{                                          //sino esta lleno
          T1CONbits.ON = 0;                            //apaga alarma
          Buzzer_estado = 0;
        }
      }

    }

  }
}//End Main

/*****IMPLEMENTACIONES*****/
void Timer1_Config(){
//Configuracion de Timer1
  TMR1 = 0;        //inicializa en cero el valor del timer
  PR1 = 65535;     //fija el  periodo del timer

  T1IP0_bit = 1;   //fija la prioridad
  T1IP1_bit = 0;   //del timer1
  T1IP2_bit = 1;   //a 5 de 7

  TCKPS0_bit = 1;  //Set Timer Input Clock
  TCKPS1_bit = 1;  //Prescale value to 1:256

  T1IE_bit = 1;    //habilita las interrupciones por timer1
}

void Setup(){
  AD1PCFG = 0xFFFF; // config. pines analogicos como digitales
  //JTAGEN_bit = 0 ;  // Deshabilita el JTAGEN (debuger)
  /**Config. pines de leds onboard y apagando los leds**/
  CEREBOT_LED1_TRIS = 0;
  CEREBOT_LED1_LAT = 0;
  CEREBOT_LED2_TRIS = 0;
  CEREBOT_LED2_LAT = 0;
  CEREBOT_LED3_TRIS = 0;
  CEREBOT_LED3_LAT = 0;
  CEREBOT_LED4_TRIS = 0;
  CEREBOT_LED4_LAT = 0;
  /**configurando los pines de control**/
  CEREBOT_TRISJE_7_bit = 1;//config. como entrada el pin del Sensor de Precencia de Agua
  CEREBOT_TRISJE_8_bit = 0;//config. como salida el pin de control del Buzzer
  Buzzer_estado = 0;      //Apagando el Buzzer
  CEREBOT_TRISJE_9_bit = 0;//config. como salida el pin de control de la Bomba de Agua
  Bomba_estado = 0;       //Apagando la Bomba


  DisableInterrupts();                // Tell CPU to stop paying attention to interrupts

  //Configuracion de UART1
  UART1_Init(115200);
  INTCONbits.MVEC = 1;                // Multi Vector interrupts
  U1STAbits.URXISEL = 0;              // 0x = Interrupt flag bit is set when a character is received
  U1STAbits.UTXISEL = 1;              // 01 = Interrupt flag bit is set when all characters have been transmitted
  IPC6bits.U1IP = 6;                  // Set UART1 priority 6 of 7
  IPC6bits.U1IS = 0;                  // Set UART1 sub priority to 0
  IFS0bits.U1RXIF = 0;                // Clear UART1 RX interrupt flag
  IFS0bits.U1TXIF = 0;                // Clear UART1 TX interrupt flag
  IEC0bits.U1RXIE = 1;                // Enable UART1 RX ISR

//Configuracion de UART2
  UART2_Init(115200);
  INTCONbits.MVEC = 1;                // Multi Vector interrupts
  U2STAbits.URXISEL = 0;              // 0x = Interrupt flag bit is set when a character is received
  U2STAbits.UTXISEL = 1;              // 01 = Interrupt flag bit is set when all characters have been transmitted
  IPC8bits.U2IP = 7;                  // Set UART2 priority 7 of 7
  IPC8bits.U2IS = 0;                  // Set UART2 sub priority to 0
  IFS1bits.U2RXIF = 0;                // Clear UART2 RX interrupt flag
  IFS1bits.U2TXIF = 0;                // Clear UART2 TX interrupt flag
  IEC1bits.U2RXIE = 1;                // Enable UART2 RX ISR

  Timer1_Config();

  EnableInterrupts();

  //Configuracion de Buffer de UART2 ( Comunicacion con Modulo Wifi)
  Buffer_Init( &WIFI_input, __buff_storage, MAX_BUFF_STORAGE );
}

void Send_To_PC( const uchar *s ){
  int i = 0;
  while( s[i] != 0 )
    UART1_Write( s[i++] );
}

int WIFI_Init(){
  uchar tmp[50];
  int i;
  Send_To_PC( "Inicializando WIFI:\r\n" );
  delay_ms(1000);
  for( i = 0; i < 9; i++ ){
    CEREBOT_LATJK_1_bit = ~CEREBOT_LATJK_1_bit;
    strcpy( tmp, (uchar*)ATcommand[ i ] );// tmp = ATcommand[ i ];
    strcat( tmp, (uchar*)ATappend[i] );   // tmp = tmp +  ATappend[i];
    UART2_Write_Text( tmp );
    UART2_Write_Text( "\r\n" );
    delay_ms(500);
    Send_To_PC(ATnotify[i]);
    delay_ms(500);
    Buffer_GetAllData( &WIFI_input, input );

    if( strstr( input, "ERROR" ) || strlen(input) == 0 ){ //Compruebo que el modulo responda sin ERRORES
        Send_To_PC( "ERROR!!!\r\n" );
        return 0;
    }
    else{
         Send_To_PC( "OK!!!\r\n" );
    }
    //Send_To_PC( sms );
    //delay_ms(1000);
  }
  return 1;
}

void GenerarTrama( uchar *t ){
        int sz = 0;//tamaño de la trama
        uchar *aux;
        sz += getOpenLabel( t, ROOT_LABEL, "name", Nombre_Estacion, "control", ((Control_estado==0)?"Manual":"Autonomo") );
        t[sz++] = '\r';t[sz++] = '\n';

        aux = (Bomba_estado==0)?"OFF":"ON";
        sz += getOpenLabel( t+sz, (uchar*)BOMBA_LABEL,"estado",aux, "","" );
        sz += getCloseLabel( t+sz, (uchar*)BOMBA_LABEL );
        t[sz++] = '\r';t[sz++] = '\n';

        aux = getStringDeEstado( (bool)Tanque_estado );
        sz += getOpenLabel( t+sz, (uchar*)TANQUE_LABEL, "estado", aux,"","" );
        sz += getCloseLabel( t+sz, (uchar*)TANQUE_LABEL );
        t[sz++] = '\r';t[sz++] = '\n';

        aux = getStringDeEstado( Cisterna_estado );
        sz += getOpenLabel( t+sz, (uchar*)CISTERNA_LABEL, "estado", aux,"","" );
        sz += getCloseLabel( t+sz, (uchar*)CISTERNA_LABEL );
        t[sz++] = '\r';t[sz++] = '\n';

        aux = (Buzzer_estado==0)?"OFF":"ON";
        sz += getOpenLabel( t+sz, (uchar*)BUZZER_LABEL, "estado", aux, "","" );
        sz += getCloseLabel( t+sz, (uchar*)BUZZER_LABEL );
        t[sz++] = '\r';t[sz++] = '\n';

        sz += getCloseLabel( t+sz, ROOT_LABEL );
}

int getOpenLabel( uchar *to, uchar *name, uchar *attrib1, uchar *value1 , uchar *attrib2 , uchar *value2 ){
        int sz;
        sz = 1+strlen(name);
        strcpy( to, "<" );
        strcpy( to+1, name );
        if( strlen(attrib1) > 0 ){
                strcpy( to+sz, " " ); sz++;
                strcpy( to+sz, attrib1 ); sz += strlen(attrib1);
                strcpy( to+sz, "=\"" ); sz += 2;
                strcpy( to+sz, value1 ); sz += strlen(value1);
                strcpy( to+sz, "\"" ); sz ++;

        }
        if( strlen(attrib2) > 0){
                strcpy( to+sz, " " ); sz++;
                strcpy( to+sz, attrib2 ); sz += strlen(attrib2);
                strcpy( to+sz, "=\"" ); sz += 2;
                strcpy( to+sz, value2 ); sz += strlen(value2);
                strcpy( to+sz, "\"" ); sz ++;
        }
        strcpy( to+sz, ">" ); sz++;
        return sz;
}

int getCloseLabel( uchar *to, uchar *name ){
        int sz = 2+strlen(name);
        strcpy( to, "</" );
        strcpy( to+2, name );
        strcpy( to+sz, ">" ); sz++;
        return sz;
}

uint getHash( char *s, int len ){
        uint hash = 1, i;
        for( i = 0; s[i] != 0; i++ ){
                hash = hash + hash_P*s[i];
        }
        return hash;
}

void Write_to_Wifi( const uchar *s ){
  int i = 0;
  while( s[i] != 0 )
    UART2_Write( s[i++] );
}

void WIFI_Wait_Init(){
  while( !WIFI_Init() );
  Buzzer_estado = 1;
  delay_ms(200);
  Buzzer_estado = 0;
}

void uint_to_str( unsigned int n, char *out ){
     int len;
     if(n == 0){
          out[0] = '0';
          out[1] = '\0';
          return;
     }
     len = log10(n)+1;
     out[len] = '\0';
     while( n ){
       len--;
       out[len] = '0' + (n%10);
       n /= 10;
     }

}
bool WIFI_Send( unsigned short user, const uchar *message, unsigned int size ){
  char aux[10];
  CEREBOT_LED4_LAT = 0;
  uint_to_str( size, aux );
  Write_to_Wifi( "AT+CIPSEND=0," );
  Write_to_Wifi( aux );
  Write_to_Wifi( "\r\n" );


  delay_ms(200);
  Write_to_Wifi(message);
  delay_ms(200);
  CEREBOT_LED4_LAT = 1;
  return true;
}

char p_data[50];  //arreglo temporal para procesar datos
char p_label[20]; //almacena la etiqueta del comando recibido
char p_estado[15];//almacena el valor del atributo estado del comando
bool Get_And_Procces_Data( const char *dat ){
  int len, p_data_id = 0, p_label_id = 0, p_estado_id = 0;
  //Get Data
  dat += 7; //me posiciono en el principio de la cant de datos ej: +IPD,0,120: ....
            //                                                            ^
  for( p_data_id =0; *dat != ':'; p_data_id++, dat++ )  //guardo el numero en p_data
    p_data[p_data_id] = *dat;
  p_data[p_data_id] = '\0';

  len = atoi(p_data);
  dat++;
  for( p_data_id = 0; p_data_id < len; p_data_id++ ){
         p_data[p_data_id] = *dat;
         dat++;
  }
  p_data[p_data_id] = '\0';
  Send_To_PC( "Get Data:" );
  Send_To_PC( p_data );
  Send_To_PC( "\r\n" );

  //Process Data
  p_data_id =0;
  while( isspace(p_data[p_data_id]) ) //salto espacios en blanco
    p_data_id++;

  if( p_data[ p_data_id ] != '<' ){//ERROR falta llave(<) de apertura
      Send_To_PC( "Get And Process ERROR 1\r\n" );
      return 0;
  }
  p_data_id++;
  //get label
  while( !isspace( p_data[ p_data_id ] ) ){
    p_label[p_label_id++] = p_data[p_data_id];
    p_data_id++;
  }
  p_label[p_label_id] = '\0';

  //get attrib estado
  while( isspace(p_data[p_data_id]) ) //salto espacios en blanco
    p_data_id++;

  while( p_data[ p_data_id ] != '=' ){ //guardo el attributo
    p_estado[p_estado_id++] = p_data[p_data_id];
    p_data_id++;
  }
  p_estado[p_estado_id] = '\0';
  if( strcmp( p_estado, "estado" ) != 0 ){//ERROR atributo incorrecto
      Send_To_PC( "Get And Process ERROR 2\r\n" );
      return 0;
  }
  p_data_id++;
  if( p_data[ p_data_id ] != '"' ){//ERROR falta comilla
      Send_To_PC( "Get And Process ERROR 3\r\n" );
      return 0;
  }
  p_data_id++;
  p_estado_id = 0;
  while( p_data[p_data_id] != '"' ){
    p_estado[p_estado_id++] = p_data[p_data_id];
    p_data_id++;
  }
  p_estado[p_estado_id] = '\0';
  //Send_to_PC("label:");
  //Send_To_PC(p_label);
  //Send_To_PC("\r\n");

  //Send_To_PC("value: ");
  //Send_To_PC( p_estado );
  //Send_To_PC( "\r\n" );
  p_data_id++;
  while( isspace(p_data[p_data_id]) ) //salto espacios en blanco
    p_data_id++;

  if( p_data[p_data_id] != '/' || p_data[p_data_id+1] != '>' ){//ERROR falta cierre
      Send_To_PC( "Get And Process ERROR 4\r\n" );
  }
  if( strcmp( p_label, BOMBA_LABEL ) == 0 ){
      //Send_To_PC("Es Bomba\r\n");
      if( strcmp( p_estado, "ON" ) == 0 ){
         // Send_To_PC( "estoy encendiendo!!!\r\n" );
          Bomba_estado = 1;
      }
      else if( strcmp( p_estado, "OFF" ) == 0 )
          Bomba_estado = 0;
      else{//ERROR estado invalido
          Send_To_PC( "Get And Process ERROR 5\r\n" );
      }
  }
  else if( strcmp( p_label, BUZZER_LABEL ) == 0 ){
      if( strcmp( p_estado, "ON" ) == 0 )
          Buzzer_estado = 1;
      else if( strcmp( p_estado, "OFF" ) == 0 )
          Buzzer_estado = 0;
      else{//ERROR estado invalido
          Send_To_PC( "Get And Process ERROR 6\r\n" );
      }
  }
  else if( strcmp( p_label, CONTROL_LABEL ) == 0 ){
      if( strcmp( p_estado, "Autonomo" ) == 0 )
          Control_estado = 1;
      else if( strcmp( p_estado, "Manual" ) == 0 )
          Control_estado = 0;
      else{//ERROR estado invalido
          Send_To_PC( "Get And Process ERROR 7\r\n" );
      }

  }
  else{//ERROR label incorrecto
    Send_To_PC( "Get And Process ERROR 8\r\n" );
  }
  return 1;
}