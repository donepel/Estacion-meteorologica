void setup () 
{
    dht.begin(); //Inicializo DHT11
    Serial.begin(115200); //inicializo UART
      
// Configuracion de DHCP Client   
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));

  Serial.println(F("Setting up DHCP"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));
  
  /*ether.printIp("IP: ", ether.myip);
  ether.printIp("Netmask: ", ether.netmask);
  ether.printIp("GW: ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);
  // FIN DHCP Client
*/
  pinMode(Ventilador, OUTPUT); //inicializo puerto led
  digitalWrite(Ventilador, LOW); //dejo en cero al led

 }
