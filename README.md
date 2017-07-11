#Proyecto Final de 3er Año


###Resumen
Este proyecto da solución a la necesidad de realizar el telecontrol de estaciones de bombeo de agua, a partir del uso del sistema inteligente DIGILENT CEREBOT (PIC 32MX460F512L) asociado al módulo de red inalámbrica ESP8266. Se diseñó e implementó a nivel de maqueta todo el sistema, incluyendo las interfaces de potencia, el sensor de nivel de agua. Se realizó la programación del microntrolador y la aplicación de escritorio para el control del sistema creada en Python.


###Arquitectura del Sistema
El núcleo del sistema es la Placa de Desarrollo Digilent Cerebot 32MX4  siendo esta la encargada de  censar  y actuar  físicamente en la  estación  de bombeo.  Además actúa  como servidor para la aplicación cliente (desarrollada en Python) que controla el sistema. Esta placa realiza también la configuración del módulo de red inalámbrica ESP8266 y el intercambio de datos por esta vía. 

###Desarrollo de Aplicación para PIC32 
MikroC PRO for PIC32  es un IDE especialmente diseñado  para programar PIC32 con  depurador  incluido,  que a pesar de no ser compatible  con la Digilent Cerebot si resulta un entorno agradable y factible para generar nuestra aplicación con una sintaxis de lenguaje  muy similar al lenguaje de programación C. Además, este IDE trae consigo un extenso conjunto de bibliotecas para los más variados usos entre los que destacan el trabajo con cadenas de caracteres (strings), comunicación con periféricos y operaciones matemáticas. Mediante este IDE podemos obtener tanto el código en ensamblador (*.asm), como el código (*.hex)  que se debe ‘quemar’ hacia el microcontrolador. Luego para grabar este código, ya sea en ensamblador o directamente el hex, utilizamos el IDE MPLAB que si es compatible con la Digilent Cerebot. 
