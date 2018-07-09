
/******************************************************
 * Estacion metereologica v3 (23-06-2018)
se agrega medicion de humedad
se pule el codigo refente al dht11
Se mejoran los comentarios de la funcion homePage()
Se mejora un poco la pagina web

*******************************************************
Estacion metereologica v2 (23-06-2018)
se configura el modulo ethernet enc28j60 con ip fija 
se configura servidor web basico
se configura DHT11
sitio web muestra temperatura
*****************************************************
Estacion metereologica v1 (23-06-2018)
se configura el modulo ethernet enc28j60 con ip fija
*****************************************************
Prerequisitos:
Libreria adafruit dht11-dht22 (instalable desde el gestor de librerias
Libreria ethernetcard disponible en https://github.com/jcw/ethercard

 */



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
int humedad(void);


const int ledPin = 12;

char* EstadoLed="OFF";

void setup () 
  {
    dht.begin(); //Inicializo DHT11
    Serial.begin(115200); //inicializo UART
    Serial.println("Iniciando Estacion Metereologica");
 
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

static word homePage() 
{
//$D = word data type
//$L = long data type
//$S = c string
//$F = progmem string
//$E = byte from the eeprom. 
 BufferFiller bfill = ether.tcpOffset();
 bfill.emit_p(PSTR("HTTP/1.0 200 OK \rn"
      "Content-Type: text/htmlrnPragma: no-cachernRefresh: 5\r\n\r\n"
      "<html><head><title>Estacion Metereologica .::Epelbyte::.</title></head>"
      "<body>"
      "<div style='text-align:center;'>"
      "<h1 style='border:2px solid DodgerBlue;'>Estacion Metereologica</h1>"      
      "<br>Temperatura actual: $D *C "
      "<br>Humedad relativa actual:$D % "
      "<br>Tiempo de uptime : $L segundos"
      "<br><br>Estado del ventilador: $S<br />"      
      "<a href=\"/?status=ON\"><input type=\"button\" value=\"ON\"></a>"
      "<a href=\"/?status=OFF\"><input type=\"button\" value=\"OFF\"></a>"
      "<br><br><br>"
      "<a href='http://www.EpelByte.com/'>www.epelbyte.com</a>"
      "</body></html>"      
      ),temperatura(),humedad(),millis()/1000,EstadoLed);
     
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
 
  // Leo la temperatura en grados centígrados
  int temp = dht.readTemperature();
  
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(temp)) 
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    temp =999; //como redundancia se altera el valor de temperatura a uno imposible
    
  }
 
   Serial.println("Se solicita valor de temperatura");
return temp;
}  

/********************************************
Funcion humedad
devuelve el valor de humedad relativa
Recibe: nada
Devuelve: humedad relativa en %
********************************************/
int humedad(void)
{
// delay(1000);
 
  // Leo la humedad relativa
  int hum = dht.readHumidity();

  // Comprobamos si ha habido algún error en la lectura
  if (isnan(hum)) 
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    hum=999; //como redundancia se altera el valor de temperatura a uno imposible
    
  }
 
   //Serial.println("Se solicita valor de humedad");
  Serial.print("% de Humedad: ");
  Serial.println( hum);
return hum;
}
