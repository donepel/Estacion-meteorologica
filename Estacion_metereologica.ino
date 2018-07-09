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
#define PRESENTACION 90
#define ESPERA 0
#define ESTADO 1
#define CLIMA  2

/*********************************************************** 
 *               Funcion principal                         *
 ***********************************************************/        
void loop() 
{
  unsigned char menu; //estado de la maquina
  unsigned char seleccion;
  menu=PRESENTACION;
  while (1)
  {
  switch (menu)
  {
    //delay(50);
    case PRESENTACION:
                      //Serial.println("**** PRESENTACION ****");
                      //Pantalla principal del menu donde se exponen todas las opciones
                      Serial.println("MENU");
                      Serial.println("1 Estado de RED"); //ESTADO
                      Serial.println("2 Estado del clima"); //CLIMA
                      Serial.println("");
                      Serial.println("Ingrese alguna opcion: ");
                      menu=ESPERA;
                      break;
    case ESPERA:
                    //Serial.println("**** ESPERA ****");
                    //Espero alguna accion
                    
                    if (Serial.available()>0)
                    {
                      //Serial.println("****Se ingreso un string");
                      //delay(25);
                      seleccion=Serial.read()-48; //convierto de ASCII a decimal
                      Serial.print("Ud selecciono la opcion nro ");
                      Serial.println(seleccion);
                      menu=seleccion;
                      
                    }
                    break;
              
              
  case ESTADO:
              Serial.println("");
              Serial.println("");
              Serial.println("");
              Serial.println("Estado de la configuracion de RED");
              ether.printIp("IP: ", ether.myip);
              ether.printIp("Netmask: ", ether.netmask);
              ether.printIp("GW: ", ether.gwip);
              ether.printIp("DNS: ", ether.dnsip);
              Serial.println("");
              Serial.println("");
              Serial.println("");
              menu=PRESENTACION;
              break; 

  case CLIMA:
              Serial.println("Valores climatologicos actuales");
              
              Serial.println("");
              Serial.println("");
              Serial.println("");
              menu=PRESENTACION;
              break;
              
  
  }

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

}
