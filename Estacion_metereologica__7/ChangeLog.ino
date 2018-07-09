/*****************************************************************
 ****Estacion meteorologica v7 (29-06-2018)
Se quitan modulos de la libreria ethercard .. 11072 bytes de ROM
ehercard.h
#define ETHERCARD_DHCP 0
#define ETHERCARD_TCPCLIENT 0
#define ETHERCARD_ICMP 0
#define ETHERCARD_STASH 0

Se quitan componentes de la libreria DHT11 correspondiente a 
los modulos DHT21 e intercambio de unidades centigrado a F
se logra reducir el programa a 10444 bytes de ROM y 1236bytes de RAM

con Ethernet::buffer[700]; la ram utilizada es de 1236 bytes
este valor se deja en 1500 ya que acelera la red, RAM =2036 bytes
******************************************************************
**** Estacion METEOROLOGICA v6 (24-06-2018)
Se corrige el nombre de meteorologica que estaba mal escrito
Se continua ordenando y prolijando el codigo.
Tamaño: 11838 bytes ROM / 1245 bytes RAM
******************************************************************
**** Estacion meteorologica v5 (23-06-2018)
Se elimina advertencia de C++ con la variable char* EstadoVent1
Se divide el main principal en varios archivos
Tamaño: 11838 bytes ROM / 1245 bytes RAM
******************************************************************* 
**** Estacion meteorologica v4 (23-06-2018) 
Se corrige el tiempo anunciado en el sitio. en realidad es uptime
Tamaño v3 pulida un poco 11368B ROM y 1357B RAM
Se condigura con DHCP CLient para mejorar el Pulg & Play
Tamaño: 12068 bytes ROM / 1309 bytes RAM

Se pule el codigo actual con los cambios anteriores
Tamaño: 11930 bytes ROM / 1261 bytes RAM
*******************************************************************
**** Estacion meteorologica v3 (23-06-2018)
se agrega medicion de humedad
se pule el codigo refente al dht11
Se mejoran los comentarios de la funcion homePage()
Se mejora un poco la pagina web
Tamaño: 11482bites rom 1357 ram
******************************************************************
**** Estacion meteorologica v2 (23-06-2018)
se configura el modulo ethernet enc28j60 con ip fija 
se configura servidor web basico
se configura DHT11
sitio web muestra temperatura
*******************************************************************
**** Estacion meteorologica v1 (23-06-2018)
se configura el modulo ethernet enc28j60 con ip fija
*******************************************************************
Prerequisitos:
Libreria adafruit dht11-dht22 (instalable desde el gestor de librerias
Libreria ethernetcard disponible en https://github.com/jcw/ethercard

 *******************************************************************/
