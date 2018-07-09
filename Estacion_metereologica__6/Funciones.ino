


/************************************************
*Funcion para leer la temperatura en modulo DHT * 
*Recibe: nada                                   *
*Devuelve: temperatura en grados centigrados    *
************************************************/
unsigned char temperatura(void)
{
  // Leo la temperatura en grados centígrados
  unsigned char temp = dht.readTemperature();
  
  // Compruebo si ha habido algún error en la lectura
  if (isnan(temp)) 
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    temp =255; //como redundancia se altera el valor de temperatura a uno imposible
  }
   return temp;
}  

/**********************************************
*Funcion para leer la humedad relativa en el  * 
*modulo DHT                                   *
*Recibe: nada                                 *
*Devuelve: humedad relativa en %              *
***********************************************/
 unsigned char humedad(void)
{
  // Leo la humedad relativa
 unsigned char  hum = dht.readHumidity();

  // Compruebo si ha habido algún error en la lectura
  if (isnan(hum)) 
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    unsigned char hum=255; //como redundancia se altera el valor de temperatura a uno imposible
  }
  return hum;
}
