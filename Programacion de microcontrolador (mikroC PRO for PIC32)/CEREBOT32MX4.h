/*
 * File         : CEREBOT32MX4.h
 * Project      : CEREBOT32MX4 Adapter
 * Revision History:
		2017/6/26:
			- Added Macros for LEDs-onBoard and SERVO-Pins control
		2017/6/2:
			- Added constants
		2017/5/20:
			- initial release

 * Author      : Jose Guerra Carmenate 
				 Leonardo González Reyes
 * Description  :
 * 				Esta biblioteca contiene definiciones y herramientas para 
 * 				facilitar el trabajo con la placa de desarrollo 
 * 				Diligent Cerebot32MX4 (con PIC32MX460F512L)
 */
#ifndef __Lib_CEREBOT32MX4
#define __Lib_CEREBOT32MX4
 //Some useful constants
const char Cerebot_INPUT = 1,
		   Cerebot_OUTPUT= 0,
	       Cerebot_LOW = 0,
		   Cerebot_HIGH = 1;
 
/** PORT_JA REGISTERS MAPS **/
//PORT->JA
#define CEREBOT_PORTJA_1_bit RE0_bit
#define CEREBOT_PORTJA_2_bit RE1_bit
#define CEREBOT_PORTJA_3_bit RE2_bit
#define CEREBOT_PORTJA_4_bit RE3_bit
#define CEREBOT_PORTJA_7_bit RE4_bit
#define CEREBOT_PORTJA_8_bit RE5_bit
#define CEREBOT_PORTJA_9_bit RE6_bit
#define CEREBOT_PORTJA_10_bit RE7_bit
//TRIS->JA
#define CEREBOT_TRISJA_1_bit TRISE0_bit
#define CEREBOT_TRISJA_2_bit TRISE1_bit
#define CEREBOT_TRISJA_3_bit TRISE2_bit
#define CEREBOT_TRISJA_4_bit TRISE3_bit
#define CEREBOT_TRISJA_7_bit TRISE4_bit
#define CEREBOT_TRISJA_8_bit TRISE5_bit
#define CEREBOT_TRISJA_9_bit TRISE6_bit
#define CEREBOT_TRISJA_10_bit TRISE7_bit
//LAT->JA
#define CEREBOT_LATJA_1_bit LATE0_bit
#define CEREBOT_LATJA_2_bit LATE1_bit
#define CEREBOT_LATJA_3_bit LATE2_bit
#define CEREBOT_LATJA_4_bit LATE3_bit
#define CEREBOT_LATJA_7_bit LATE4_bit
#define CEREBOT_LATJA_8_bit LATE5_bit
#define CEREBOT_LATJA_9_bit LATE6_bit
#define CEREBOT_LATJA_10_bit LATE7_bit
//ODC->JA
#define CEREBOT_ODCJA_1_bit ODCE0_bit
#define CEREBOT_ODCJA_2_bit ODCE1_bit
#define CEREBOT_ODCJA_3_bit ODCE2_bit
#define CEREBOT_ODCJA_4_bit ODCE3_bit
#define CEREBOT_ODCJA_7_bit ODCE4_bit
#define CEREBOT_ODCJA_8_bit ODCE5_bit
#define CEREBOT_ODCJA_9_bit ODCE6_bit
#define CEREBOT_ODCJA_10_bit ODCE7_bit


/** PORT_JB REGISTERS MAPS **/
//PORT->JB
#define CEREBOT_PORTJB_1_bit RG9_bit
#define CEREBOT_PORTJB_2_bit RG8_bit
#define CEREBOT_PORTJB_3_bit RG7_bit
#define CEREBOT_PORTJB_4_bit RG6_bit
#define CEREBOT_PORTJB_7_bit RB15_bit
#define CEREBOT_PORTJB_8_bit RD5_bit
#define CEREBOT_PORTJB_9_bit RD4_bit
#define CEREBOT_PORTJB_10_bit RB14_bit
//TRIS->JB
#define CEREBOT_TRISJB_1_bit TRISG9_bit
#define CEREBOT_TRISJB_2_bit TRISG8_bit
#define CEREBOT_TRISJB_3_bit TRISG7_bit
#define CEREBOT_TRISJB_4_bit TRISG6_bit
#define CEREBOT_TRISJB_7_bit TRISB15_bit	//AN15
#define CEREBOT_TRISJB_8_bit TRISD5_bit
#define CEREBOT_TRISJB_9_bit TRISD4_bit
#define CEREBOT_TRISJB_10_bit TRISB14_bit	//AN14
//LAT->JB
#define CEREBOT_LATJB_1_bit LATG9_bit
#define CEREBOT_LATJB_2_bit LATG8_bit
#define CEREBOT_LATJB_3_bit LATG7_bit
#define CEREBOT_LATJB_4_bit LATG6_bit
#define CEREBOT_LATJB_7_bit LATB15_bit
#define CEREBOT_LATJB_8_bit LATD5_bit
#define CEREBOT_LATJB_9_bit LATD4_bit
#define CEREBOT_LATJB_10_bit LATB14_bit
//ODC->JB
#define CEREBOT_ODCJB_1_bit ODCG9_bit
#define CEREBOT_ODCJB_2_bit ODCG8_bit
#define CEREBOT_ODCJB_3_bit ODCG7_bit
#define CEREBOT_ODCJB_4_bit ODCG6_bit
#define CEREBOT_ODCJB_7_bit ODCB15_bit
#define CEREBOT_ODCJB_8_bit ODCD5_bit
#define CEREBOT_ODCJB_9_bit ODCD4_bit
#define CEREBOT_ODCJB_10_bit ODCB14_bit

/** PORT_JC REGISTERS MAPS **/
/**
 * NOTE:
  JC-01 --> Compartido con servo S1
  JC-02 --> Compartido con servo S2
  JC-03 --> Compartido con servo S3
  JC-04 --> Compartido con servo S4
  JC-07 --> Compartido con servo S5
  JC-08 --> Compartido con servo S6
  JC-09 --> Compartido con servo S7
  JC-10 --> Compartido con servo S8  
  */
//PORT->JC
#define CEREBOT_PORTJC_1_bit RG12_bit
#define CEREBOT_PORTJC_2_bit RG13_bit
#define CEREBOT_PORTJC_3_bit RG14_bit
#define CEREBOT_PORTJC_4_bit RG15_bit
#define CEREBOT_PORTJC_7_bit RG0_bit
#define CEREBOT_PORTJC_8_bit RG1_bit
#define CEREBOT_PORTJC_9_bit RF0_bit
#define CEREBOT_PORTJC_10_bit RF1_bit
//TRIS->JC
#define CEREBOT_TRISJC_1_bit TRISG12_bit
#define CEREBOT_TRISJC_2_bit TRISG13_bit
#define CEREBOT_TRISJC_3_bit TRISG14_bit
#define CEREBOT_TRISJC_4_bit TRISG15_bit
#define CEREBOT_TRISJC_7_bit TRISG0_bit
#define CEREBOT_TRISJC_8_bit TRISG1_bit
#define CEREBOT_TRISJC_9_bit TRISF0_bit
#define CEREBOT_TRISJC_10_bit TRISF1_bit
//LAT->JC
#define CEREBOT_LATJC_1_bit LATG12_bit
#define CEREBOT_LATJC_2_bit LATG13_bit
#define CEREBOT_LATJC_3_bit LATG14_bit
#define CEREBOT_LATJC_4_bit LATG15_bit
#define CEREBOT_LATJC_7_bit LATG0_bit
#define CEREBOT_LATJC_8_bit LATG1_bit
#define CEREBOT_LATJC_9_bit LATF0_bit
#define CEREBOT_LATJC_10_bit LATF1_bit
//ODC->JC
#define CEREBOT_ODCJC_1_bit ODCG12_bit
#define CEREBOT_ODCJC_2_bit ODCG13_bit
#define CEREBOT_ODCJC_3_bit ODCG14_bit
#define CEREBOT_ODCJC_4_bit ODCG15_bit
#define CEREBOT_ODCJC_7_bit ODCG0_bit
#define CEREBOT_ODCJC_8_bit ODCG1_bit
#define CEREBOT_ODCJC_9_bit ODCF0_bit
#define CEREBOT_ODCJC_10_bit ODCF1_bit

/** PORT_JD REGISTERS MAPS **/
//PORT->JD
#define CEREBOT_PORTJD_1_bit RD7_bit
#define CEREBOT_PORTJD_2_bit RD1_bit
#define CEREBOT_PORTJD_3_bit RD9_bit 	//Shared with SPI Port1 Connector,J1
#define CEREBOT_PORTJD_4_bit RC1_bit
#define CEREBOT_PORTJD_7_bit RD6_bit
#define CEREBOT_PORTJD_8_bit RD2_bit
#define CEREBOT_PORTJD_9_bit RD10_bit	//Shared with SPI Port1 Connector,J1
#define CEREBOT_PORTJD_10_bit RC2_bit
//TRIS->JD
#define CEREBOT_TRISJD_1_bit TRISD7_bit
#define CEREBOT_TRISJD_2_bit TRISD1_bit
#define CEREBOT_TRISJD_3_bit TRISD9_bit
#define CEREBOT_TRISJD_4_bit TRISC1_bit
#define CEREBOT_TRISJD_7_bit TRISD6_bit
#define CEREBOT_TRISJD_8_bit TRISD2_bit
#define CEREBOT_TRISJD_9_bit TRISD10_bit
#define CEREBOT_TRISJD_10_bit TRISC2_bit
//LAT->JD
#define CEREBOT_LATJD_1_bit LATD7_bit
#define CEREBOT_LATJD_2_bit LATD1_bit
#define CEREBOT_LATJD_3_bit LATD9_bit
#define CEREBOT_LATJD_4_bit LATC1_bit
#define CEREBOT_LATJD_7_bit LATD6_bit
#define CEREBOT_LATJD_8_bit LATD2_bit
#define CEREBOT_LATJD_9_bit LATD10_bit
#define CEREBOT_LATJD_10_bit LATC2_bit
//ODC->JD
#define CEREBOT_ODCJD_1_bit ODCD7_bit
#define CEREBOT_ODCJD_2_bit ODCD1_bit
#define CEREBOT_ODCJD_3_bit ODCD9_bit
#define CEREBOT_ODCJD_4_bit ODCC1_bit
#define CEREBOT_ODCJD_7_bit ODCD6_bit
#define CEREBOT_ODCJD_8_bit ODCD2_bit
#define CEREBOT_ODCJD_9_bit ODCD10_bit
#define CEREBOT_ODCJD_10_bit ODCC2_bit

/** PORT_JE REGISTERS MAPS **/
//PORT->JE
#define CEREBOT_PORTJE_1_bit RD14_bit
#define CEREBOT_PORTJE_2_bit RD15_bit
#define CEREBOT_PORTJE_3_bit RF2_bit
#define CEREBOT_PORTJE_4_bit RF8_bit
#define CEREBOT_PORTJE_7_bit RD13_bit
#define CEREBOT_PORTJE_8_bit RD3_bit
#define CEREBOT_PORTJE_9_bit RD11_bit
#define CEREBOT_PORTJE_10_bit RC3_bit
//TRIS->JE
#define CEREBOT_TRISJE_1_bit TRISD14_bit
#define CEREBOT_TRISJE_2_bit TRISD15_bit
#define CEREBOT_TRISJE_3_bit TRISF2_bit
#define CEREBOT_TRISJE_4_bit TRISF8_bit
#define CEREBOT_TRISJE_7_bit TRISD13_bit
#define CEREBOT_TRISJE_8_bit TRISD3_bit
#define CEREBOT_TRISJE_9_bit TRISD11_bit
#define CEREBOT_TRISJE_10_bit TRISC3_bit
//LAT->JE
#define CEREBOT_LATJE_1_bit LATD14_bit
#define CEREBOT_LATJE_2_bit LATD15_bit
#define CEREBOT_LATJE_3_bit LATF2_bit
#define CEREBOT_LATJE_4_bit LATF8_bit
#define CEREBOT_LATJE_7_bit LATD13_bit
#define CEREBOT_LATJE_8_bit LATD3_bit
#define CEREBOT_LATJE_9_bit LATD11_bit
#define CEREBOT_LATJE_10_bit LATC3_bit
//ODC->JE
#define CEREBOT_ODCJE_1_bit ODCD14_bit
#define CEREBOT_ODCJE_2_bit ODCD15_bit
#define CEREBOT_ODCJE_3_bit ODCF2_bit
#define CEREBOT_ODCJE_4_bit ODCF8_bit
#define CEREBOT_ODCJE_7_bit ODCD13_bit
#define CEREBOT_ODCJE_8_bit ODCD3_bit
#define CEREBOT_ODCJE_9_bit ODCD11_bit
#define CEREBOT_ODCJE_10_bit ODCC3_bit

/** PORT_JF REGISTERS MAPS **/
//PORT->JF
#define CEREBOT_PORTJF_1_bit RA2_bit	//Shared with I2C daisy chain #2,J6
#define CEREBOT_PORTJF_2_bit RA3_bit	//Shared with I2C daisy chain #2,J6
#define CEREBOT_PORTJF_3_bit RA6_bit	//Shared with BTN1
#define CEREBOT_PORTJF_4_bit RA7_bit	//Shared with BTN2
//TRIS->JF
#define CEREBOT_TRISJF_1_bit TRISA2_bit
#define CEREBOT_TRISJF_2_bit TRISA3_bit
#define CEREBOT_TRISJF_3_bit TRISA6_bit
#define CEREBOT_TRISJF_4_bit TRISA7_bit
//LAT->JF
#define CEREBOT_LATJF_1_bit LATA2_bit
#define CEREBOT_LATJF_2_bit LATA3_bit
#define CEREBOT_LATJF_3_bit LATA6_bit
#define CEREBOT_LATJF_4_bit LATA7_bit
//ODC->JF
#define CEREBOT_ODCJF_1_bit ODCA2_bit
#define CEREBOT_ODCJF_2_bit ODCA3_bit
#define CEREBOT_ODCJF_3_bit ODCA6_bit
#define CEREBOT_ODCJF_4_bit ODCA7_bit

/** PORT_JH REGISTERS MAPS **/
//PORT->JH
#define CEREBOT_PORTJH_1_bit RF12_bit
#define CEREBOT_PORTJH_2_bit RF13_bit
#define CEREBOT_PORTJH_3_bit RF4_bit
#define CEREBOT_PORTJH_4_bit RF5_bit
#define CEREBOT_PORTJH_7_bit RE8_bit
#define CEREBOT_PORTJH_8_bit RD0_bit	//Shared with SPI Port1 Connector,J1
#define CEREBOT_PORTJH_9_bit RD8_bit
#define CEREBOT_PORTJH_10_bit RE9_bit	//Shared with USB OC_SENSE via JP5
//TRIS->JH
#define CEREBOT_TRISJH_1_bit TRISF12_bit
#define CEREBOT_TRISJH_2_bit TRISF13_bit
#define CEREBOT_TRISJH_3_bit TRISF4_bit
#define CEREBOT_TRISJH_4_bit TRISF5_bit
#define CEREBOT_TRISJH_7_bit TRISE8_bit
#define CEREBOT_TRISJH_8_bit TRISD0_bit
#define CEREBOT_TRISJH_9_bit TRISD8_bit
#define CEREBOT_TRISJH_10_bit TRISE9_bit
//LAT->JH
#define CEREBOT_LATJH_1_bit LATF12_bit
#define CEREBOT_LATJH_2_bit LATF13_bit
#define CEREBOT_LATJH_3_bit LATF4_bit
#define CEREBOT_LATJH_4_bit LATF5_bit
#define CEREBOT_LATJH_7_bit LATE8_bit
#define CEREBOT_LATJH_8_bit LATD0_bit
#define CEREBOT_LATJH_9_bit LATD8_bit
#define CEREBOT_LATJH_10_bit LATE9_bit
//ODC->JH
#define CEREBOT_ODCJH_1_bit ODCF12_bit
#define CEREBOT_ODCJH_2_bit ODCF13_bit
#define CEREBOT_ODCJH_3_bit ODCF4_bit
#define CEREBOT_ODCJH_4_bit ODCF5_bit
#define CEREBOT_ODCJH_7_bit ODCE8_bit
#define CEREBOT_ODCJH_8_bit ODCD0_bit
#define CEREBOT_ODCJH_9_bit ODCD8_bit
#define CEREBOT_ODCJH_10_bit ODCE9_bit

/** PORT_JJ REGISTERS MAPS **/
//PORT->JJ
#define CEREBOT_PORTJJ_1_bit RB0_bit	//AN0
#define CEREBOT_PORTJJ_2_bit RB1_bit	//AN1
#define CEREBOT_PORTJJ_3_bit RB2_bit	//AN2
#define CEREBOT_PORTJJ_4_bit RB3_bit	//AN3
#define CEREBOT_PORTJJ_7_bit RB4_bit	//AN4
#define CEREBOT_PORTJJ_8_bit RB5_bit	//AN5//Selected by J16
#define CEREBOT_PORTJJ_9_bit RB8_bit	//AN8
#define CEREBOT_PORTJJ_10_bit RB9_bit	//AN9
//TRIS->JJ
#define CEREBOT_TRISJJ_1_bit TRISB0_bit
#define CEREBOT_TRISJJ_2_bit TRISB1_bit
#define CEREBOT_TRISJJ_3_bit TRISB2_bit
#define CEREBOT_TRISJJ_4_bit TRISB3_bit
#define CEREBOT_TRISJJ_7_bit TRISB4_bit
#define CEREBOT_TRISJJ_8_bit TRISB5_bit
#define CEREBOT_TRISJJ_9_bit TRISB8_bit
#define CEREBOT_TRISJJ_10_bit TRISB9_bit
//LAT->JJ
#define CEREBOT_LATJJ_1_bit LATB0_bit
#define CEREBOT_LATJJ_2_bit LATB1_bit
#define CEREBOT_LATJJ_3_bit LATB2_bit
#define CEREBOT_LATJJ_4_bit LATB3_bit
#define CEREBOT_LATJJ_7_bit LATB4_bit
#define CEREBOT_LATJJ_8_bit LATB5_bit
#define CEREBOT_LATJJ_9_bit LATB8_bit
#define CEREBOT_LATJJ_10_bit LATB9_bit
//ODC->JJ
#define CEREBOT_ODCJJ_1_bit ODCB0_bit
#define CEREBOT_ODCJJ_2_bit ODCB1_bit
#define CEREBOT_ODCJJ_3_bit ODCB2_bit
#define CEREBOT_ODCJJ_4_bit ODCB3_bit
#define CEREBOT_ODCJJ_7_bit ODCB4_bit
#define CEREBOT_ODCJJ_8_bit ODCB5_bit
#define CEREBOT_ODCJJ_9_bit ODCB8_bit
#define CEREBOT_ODCJJ_10_bit ODCB9_bit

/** PORT_JK REGISTERS MAPS **/
//PORT->JK
#define CEREBOT_PORTJK_1_bit RB10_bit	//AN10//Shared with LED1
#define CEREBOT_PORTJK_2_bit RB11_bit	//AN11//Shared with LED2
#define CEREBOT_PORTJK_3_bit RB12_bit	//AN12//Shared with LED3
#define CEREBOT_PORTJK_4_bit RB13_bit	//AN13//Shared with LED4
#define CEREBOT_PORTJK_7_bit RA9_bit
#define CEREBOT_PORTJK_8_bit RA10_bit
#define CEREBOT_PORTJK_9_bit RD12_bit
#define CEREBOT_PORTJK_10_bit RC4_bit
//TRIS->JK
#define CEREBOT_TRISJK_1_bit TRISB10_bit
#define CEREBOT_TRISJK_2_bit TRISB11_bit
#define CEREBOT_TRISJK_3_bit TRISB12_bit
#define CEREBOT_TRISJK_4_bit TRISB13_bit
#define CEREBOT_TRISJK_7_bit TRISA9_bit
#define CEREBOT_TRISJK_8_bit TRISA10_bit
#define CEREBOT_TRISJK_9_bit TRISD12_bit
#define CEREBOT_TRISJK_10_bit TRISC4_bit
//LAT->JK
#define CEREBOT_LATJK_1_bit LATB10_bit
#define CEREBOT_LATJK_2_bit LATB11_bit
#define CEREBOT_LATJK_3_bit LATB12_bit
#define CEREBOT_LATJK_4_bit LATB13_bit
#define CEREBOT_LATJK_7_bit LATA9_bit
#define CEREBOT_LATJK_8_bit LATA10_bit
#define CEREBOT_LATJK_9_bit LATD12_bit
#define CEREBOT_LATJK_10_bit LATC4_bit
//ODC->JK
#define CEREBOT_ODCJK_1_bit ODCB10_bit
#define CEREBOT_ODCJK_2_bit ODCB11_bit
#define CEREBOT_ODCJK_3_bit ODCB12_bit
#define CEREBOT_ODCJK_4_bit ODCB13_bit
#define CEREBOT_ODCJK_7_bit ODCA9_bit
#define CEREBOT_ODCJK_8_bit ODCA10_bit
#define CEREBOT_ODCJK_9_bit ODCD12_bit
#define CEREBOT_ODCJK_10_bit ODCC4_bit


//////////////HARDWARE CONSTANTS\\\\\\\\\\\\\\\\
//---------->BUTTONS<---------------\\
//Button 1
#define CEREBOT_BTN1_TRIS CEREBOT_TRISJF_3_bit
#define CEREBOT_BTN1_PORT CEREBOT_PORTJF_3_bit
#define CEREBOT_BTN1_LAT  CEREBOT_LATJF_3_bit
#define CEREBOT_BTN1_ODC  CEREBOT_ODCJF_3_bit
//Button 2
#define CEREBOT_BTN2_TRIS CEREBOT_TRISJF_4_bit
#define CEREBOT_BTN2_PORT CEREBOT_PORTJF_4_bit
#define CEREBOT_BTN2_LAT  CEREBOT_LATJF_4_bit
#define CEREBOT_BTN2_ODC  CEREBOT_ODCJF_4_bit
//----------->LEDS<---------\\
//LED 1
#define CEREBOT_LED1_TRIS CEREBOT_TRISJK_1_bit
#define CEREBOT_LED1_PORT CEREBOT_PORTJK_1_bit
#define CEREBOT_LED1_LAT  CEREBOT_LATJK_1_bit
#define CEREBOT_LED1_ODC  CEREBOT_ODCJK_1_bit
//LED 2
#define CEREBOT_LED2_TRIS CEREBOT_TRISJK_2_bit
#define CEREBOT_LED2_PORT CEREBOT_PORTJK_2_bit
#define CEREBOT_LED2_LAT  CEREBOT_LATJK_2_bit
#define CEREBOT_LED2_ODC  CEREBOT_ODCJK_2_bit
//LED 3
#define CEREBOT_LED3_TRIS CEREBOT_TRISJK_3_bit
#define CEREBOT_LED3_PORT CEREBOT_PORTJK_3_bit
#define CEREBOT_LED3_LAT  CEREBOT_LATJK_3_bit
#define CEREBOT_LED3_ODC  CEREBOT_ODCJK_3_bit
//LED 4
#define CEREBOT_LED4_TRIS CEREBOT_TRISJK_4_bit
#define CEREBOT_LED4_PORT CEREBOT_PORTJK_4_bit
#define CEREBOT_LED4_LAT  CEREBOT_LATJK_4_bit
#define CEREBOT_LED4_ODC  CEREBOT_ODCJK_4_bit

//---------------->SERVOS<------------------\\
//SERVO 1
#define CEREBOT_SERVO1_TRIS CEREBOT_TRISJC_1_bit
#define CEREBOT_SERVO1_PORT CEREBOT_PORTJC_1_bit
#define CEREBOT_SERVO1_LAT  CEREBOT_LATJC_1_bit
#define CEREBOT_SERVO1_ODC  CEREBOT_ODCJC_1_bit
//SERVO 2
#define CEREBOT_SERVO2_TRIS CEREBOT_TRISJC_2_bit
#define CEREBOT_SERVO2_PORT CEREBOT_PORTJC_2_bit
#define CEREBOT_SERVO2_LAT  CEREBOT_LATJC_2_bit
#define CEREBOT_SERVO2_ODC  CEREBOT_ODCJC_2_bit
//SERVO 3
#define CEREBOT_SERVO3_TRIS CEREBOT_TRISJC_3_bit
#define CEREBOT_SERVO3_PORT CEREBOT_PORTJC_3_bit
#define CEREBOT_SERVO3_LAT  CEREBOT_LATJC_3_bit
#define CEREBOT_SERVO3_ODC  CEREBOT_ODCJC_3_bit
//SERVO 4
#define CEREBOT_SERVO4_TRIS CEREBOT_TRISJC_4_bit
#define CEREBOT_SERVO4_PORT CEREBOT_PORTJC_4_bit
#define CEREBOT_SERVO4_LAT  CEREBOT_LATJC_4_bit
#define CEREBOT_SERVO4_ODC  CEREBOT_ODCJC_4_bit
//SERVO 5
#define CEREBOT_SERVO5_TRIS CEREBOT_TRISJC_7_bit
#define CEREBOT_SERVO5_PORT CEREBOT_PORTJC_7_bit
#define CEREBOT_SERVO5_LAT  CEREBOT_LATJC_7_bit
#define CEREBOT_SERVO5_ODC  CEREBOT_ODCJC_7_bit
//SERVO 6
#define CEREBOT_SERVO6_TRIS CEREBOT_TRISJC_8_bit
#define CEREBOT_SERVO6_PORT CEREBOT_PORTJC_8_bit
#define CEREBOT_SERVO6_LAT  CEREBOT_LATJC_8_bit
#define CEREBOT_SERVO6_ODC  CEREBOT_ODCJC_8_bit
//SERVO 7
#define CEREBOT_SERVO7_TRIS CEREBOT_TRISJC_9_bit
#define CEREBOT_SERVO7_PORT CEREBOT_PORTJC_9_bit
#define CEREBOT_SERVO7_LAT  CEREBOT_LATJC_9_bit
#define CEREBOT_SERVO7_ODC  CEREBOT_ODCJC_9_bit
//SERVO 8
#define CEREBOT_SERVO8_TRIS CEREBOT_TRISJC_10_bit
#define CEREBOT_SERVO8_PORT CEREBOT_PORTJC_10_bit
#define CEREBOT_SERVO8_LAT  CEREBOT_LATJC_10_bit
#define CEREBOT_SERVO8_ODC  CEREBOT_ODCJC_10_bit

#endif