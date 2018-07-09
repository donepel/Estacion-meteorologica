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
  return hum;
}
