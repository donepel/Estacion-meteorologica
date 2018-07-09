/***************************************
*****Estacion metereologica v2

23-06-2018
se configura el modulo ethernet enc28j60 con ip fija 
se configura servidor web basico
se configura DHT11
sitio web muestra temperatura

****************************************/


#include <EtherCard.h>
#include <DHT.h>

//Configuracion correspondiente al modulo ethernet
static byte mymac[] = {0xDD,0xDD,0xDD,0x00,0x01,0x05};
static byte myip[] = {192,168,1,177};
byte Ethernet::buffer[700];
//*****************

//configuracion correspondiente al DHT11
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 11
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11 //DHT22
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);


int temperatura(void);

const int ledPin = 12;

char* EstadoLed="OFF";

void setup () 
  {
    dht.begin(); //Inicializo DHT11
    Serial.begin(115200); //inicializo UART
    Serial.println("Estacion Metereologica");
 
 // inicializo modulo ethernet
  if (!ether.begin(sizeof Ethernet::buffer, mymac, 53))
    Serial.println( "No se ha podido acceder a la controlador Ethernet");
 else
   Serial.println("Controlador Ethernet inicializado");
 
  if (!ether.staticSetup(myip))
    Serial.println("No se pudo establecer la dirección IP");

  Serial.println();
 // FIN inicializacion ethernet
  
  pinMode(ledPin, OUTPUT); //inicializo puerto led
  digitalWrite(ledPin, LOW); //dejo en cero al led
}

static word homePage() {
  
 BufferFiller bfill = ether.tcpOffset();
 bfill.emit_p(PSTR("HTTP/1.0 200 OK \rn"
      "Content-Type: text/htmlrnPragma: no-cachernRefresh: 5\r\n\r\n"
      "<html><head><title>Estacion Metereologica .::Epelbyte::.</title></head>"
      "<body>"
      "<div style='text-align:center;'>"
      "<h1>Estacion Metereologica</h1>"      
      "Tiempo transcurrido : $L segundos"
      "<br /><br />Estado del LED: $S<br />"      
      "<a href=\"/?status=ON\"><input type=\"button\" value=\"ON\"></a>"
      "<a href=\"/?status=OFF\"><input type=\"button\" value=\"OFF\"></a>"
      "<br /><br />Temperatura actual: $D"
      "<br /><br />"
      "<a href='http://www.EpelByte.com/'>www.epelbyte.com</a>"
      "</body></html>"      
      ),millis()/1000,EstadoLed,temperatura());
     
  return bfill.position();
}
  
void loop() {
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  //delay(1000);
  //Serial.println(temperatura());
  
  if(pos) 
  {
    
    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=ON") != 0) {
      Serial.println("Comando ON recibido");
      digitalWrite(ledPin, HIGH);
      EstadoLed = "ON";
    }

    if(strstr((char *)Ethernet::buffer + pos, "GET /?status=OFF") != 0) {
      Serial.println("Comando OFF recibido");
      digitalWrite(ledPin, LOW);
       EstadoLed= "OFF";
    }         
    ether.httpServerReply(homePage()); // se envia página Web
  }
}


/********************************************
Funcion temperatura 
devuelve el valor de temperatura
Recibe: nada
Devuelve: temperatura en grados centigrados
********************************************/
int temperatura(void)
{
// delay(1000);
 
  // Leo la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  int t = dht.readTemperature();
  
  // Comprobamos si ha habido algún error en la lectura
  Serial.println(isnan(h));
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    t =999;
    //return;
  }
 
  // Calcular el índice de calor en Fahrenheit
  //float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  //float hic = dht.computeHeatIndex(t, h, false);
 
 // Serial.print("Temperatura: ");
 // Serial.print(t);
 // Serial.print("*C ");
 // Serial.print("Humedad: ");
 // Serial.print(h);
 // Serial.print("%\t");
  //Serial.print("Índice de calor: ");
  //Serial.print(hic);
  //Serial.print(" *C ");
  //Serial.println();
 Serial.println("Se solicita valor de temperatura");
return t;
}  
