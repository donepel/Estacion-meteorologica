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
      "<html><head><title>Estacion Meteorologica .::Epelbyte::.</title></head>"
      "<body><div style='text-align:center;'>"
      "<h1 style='border:3px solid DodgerBlue;'>Estacion Meteorologica</h1>"      
      "<br>Temperatura actual: $D *C "
      "<br>Humedad relativa actual:$D % "
      "<br>Tiempo de uptime : $L segundos"
      "<br><br>Estado del ventilador: $S<br>"      
      "<a href=\"/?status=ON\"><input type=\"button\" value=\"ON\"></a>"
      "<a href=\"/?status=OFF\"><input type=\"button\" value=\"OFF\"></a>"
      "<br><br><br><a href='http://www.EpelByte.com/'>www.epelbyte.com</a>"
      "</body></html>"      
      ),temperatura(),humedad(),millis()/1000,EstadoVent1);
     
  return bfill.position();
}
