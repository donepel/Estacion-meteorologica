
/*****************************************************
**** Estacion metereologica v4 (23-06-2018)
Se corrige el tiempo anunciado en el sitio. en realidad es uptime
Tamaño v3 pulida un poco 11368B ROM y 1357B RAM
Se condigura con DHCP CLient para mejorar el Pulg & Play
Tamaño: 12068 bytes ROM / 1309 bytes RAM

Se pule el codigo actual con los cambios anteriores
Tamaño: 11930 bytes ROM / 1261 bytes RAM

******************************************************
**** Estacion metereologica v3 (23-06-2018)
se agrega medicion de humedad
se pule el codigo refente al dht11
Se mejoran los comentarios de la funcion homePage()
Se mejora un poco la pagina web

Tamaño: 11482bites rom 1357 ram
*******************************************************
**** Estacion metereologica v2 (23-06-2018)
se configura el modulo ethernet enc28j60 con ip fija 
se configura servidor web basico
se configura DHT11
sitio web muestra temperatura
*****************************************************
**** Estacion metereologica v1 (23-06-2018)
se configura el modulo ethernet enc28j60 con ip fija
*****************************************************
Prerequisitos:
Libreria adafruit dht11-dht22 (instalable desde el gestor de librerias
Libreria ethernetcard disponible en https://github.com/jcw/ethercard

 */



#include <EtherCard.h>
#include <DHT.h>

//Configuracion correspondiente al modulo ethernet
static byte mymac[] = {0x74,0x69,0x69,0x2D,0x30,0x38};
//static byte myip[] = {192,168,1,177};
byte Ethernet::buffer[700];
//*****************

//configuracion correspondiente al DHT11
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 11
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11 //DHT22
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Declaracion de funciones
unsigned char temperatura(void);
unsigned char humedad(void);


const int ledPin = 12;

char* EstadoLed="OFF";

void setup () 
  {
    dht.begin(); //Inicializo DHT11
    Serial.begin(115200); //inicializo UART
    Serial.println("Iniciando Estacion Metereologica");
  
// Configuracion de DHCP Client   
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));

  Serial.println(F("Setting up DHCP"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));
  
  ether.printIp("IP: ", ether.myip);
  ether.printIp("Netmask: ", ether.netmask);
  ether.printIp("GW: ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);
  // FIN DHCP Client
 
 
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
      "<body><div style='text-align:center;'>"
      "<h1 style='border:3px solid DodgerBlue;'>Estacion Metereologica</h1>"      
      "<br>Temperatura actual: $D *C "
      "<br>Humedad relativa actual:$D % "
      "<br>Tiempo de uptime : $L segundos"
      "<br><br>Estado del ventilador: $S<br>"      
      "<a href=\"/?status=ON\"><input type=\"button\" value=\"ON\"></a>"
      "<a href=\"/?status=OFF\"><input type=\"button\" value=\"OFF\"></a>"
      "<br><br><br><a href='http://www.EpelByte.com/'>www.epelbyte.com</a>"
      "</body></html>"      
      ),temperatura(),humedad(),millis()/1000,EstadoLed);
     
  return bfill.position();
}
  
void loop() {
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
    
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
unsigned char temperatura(void)
{
  // Leo la temperatura en grados centígrados
  unsigned char temp = dht.readTemperature();
  
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(temp)) 
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    temp =255; //como redundancia se altera el valor de temperatura a uno imposible
   }
    //Serial.println("Se solicita valor de temperatura");
return temp;
}  

/********************************************
Funcion humedad
devuelve el valor de humedad relativa
Recibe: nada
Devuelve: humedad relativa en %
********************************************/
 unsigned char humedad(void)
{
  // Leo la humedad relativa
 unsigned char  hum = dht.readHumidity();

  // Comprobamos si ha habido algún error en la lectura
  if (isnan(hum)) 
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
   unsigned char hum=255; //como redundancia se altera el valor de temperatura a uno imposible
    
  }
 
   //Serial.println("Se solicita valor de humedad");
  Serial.print("% de Humedad: ");
  Serial.println( hum);
return hum;
}
