#include <EtherCard.h>
#include <DHT.h>

//Configuracion correspondiente al modulo ethernet
static byte mymac[] = {0x74,0x69,0x69,0x2D,0x30,0x38};
//static byte myip[] = {192,168,1,177};
byte Ethernet::buffer[700];
//*****************

//configuracion correspondiente al DHT11
#define DHTPIN 11 // Defino pin datos DHT
#define DHTTYPE DHT11 //Defino modelo de sensor DHT11 o DHT22
 
// Inicializo el sensor DHT
DHT dht(DHTPIN, DHTTYPE);

const int Ventilador = 12; //pin donde se encuentra un forzador pra encender de forma remota
const char* EstadoVent1="OFF";

  
void loop() 
{
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
    
  if(pos) 
  {
    
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=ON") != 0) {
      Serial.println("Comando ON recibido");
      digitalWrite(Ventilador, HIGH);
      EstadoVent1 = "ON";
    }

    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=OFF") != 0) {
      Serial.println("Comando OFF recibido");
      digitalWrite(Ventilador, LOW);
       EstadoVent1= "OFF";
    }         
    ether.httpServerReply(homePage()); // se envia página Web
  }
}
