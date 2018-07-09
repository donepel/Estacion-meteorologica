/************************************************************
 *                                                          *
 *       MAIN Estacion Meteorologica                        * 
 *       ver notas para conocer el versionado               *
 *                                                          *
 ************************************************************/ 

#include <EtherCard.h> //https://github.com/jcw/ethercard
#include <DHT.h>

/*******************************************************
 *Configuracion correspondiente al modulo ethernet     *
 *******************************************************/
static byte mymac[] = {0x74,0x69,0x69,0x2D,0x30,0x38};
byte Ethernet::buffer[1500]; //consume ram pero acelera la red
/******************** FIN ENC28J60 ********************/


/**************************************************************
 *Configuracion correspondiente al modulo DHT11               *
 **************************************************************/
#define DHTPIN 11 // Defino pin datos DHT
#define DHTTYPE DHT11 //Defino modelo de sensor DHT11 o DHT22
// Inicializo el sensor DHT
DHT dht(DHTPIN, DHTTYPE);
/************************* FIN DHT ***************************/


//Definiciones varias, controles externos, variables, etc.
const int Ventilador = 12; //pin donde se encuentra un forzador pra encender de forma remota
const char* EstadoVent1="OFF";



/*********************************************************** 
 *               Funcion principal                         *
 ***********************************************************/        
void loop() 
{
  // cata x tiempo consulto los sensores y los envio a climaar
  
  //consultas al sitio web
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  if(pos) 
  {
    
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=ON") != 0) 
    {
      Serial.println("Comando ON recibido");
      digitalWrite(Ventilador, HIGH);
      EstadoVent1 = "ON";
    }

    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=OFF") != 0) 
    {
      Serial.println("Comando OFF recibido");
      digitalWrite(Ventilador, LOW);
       EstadoVent1= "OFF";
    }         
    ether.httpServerReply(homePage()); // se envia página Web
  }
  //Fin sitioweb
}
