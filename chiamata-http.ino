#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); // RX, TX

void setup()
{
  mySerial.begin(19200);  // the GPRS baud rate   
  Serial.begin(19200);    // the GPRS baud rate   
}

void loop()
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());  

  // AT+SAPBR=3,1,"Contype","GPRS"
  mySerial.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\""); 
  delay(1000);

  // AT+SAPBR=3,1,"APN","internet.coopvoce.it"
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"internet.coopvoce.it\""); 
  delay(1000);

  // AT command to start task
  mySerial.println("AT+SAPBR=1,1");
  delay(1000);

  // AT command to set SIM900 to HTTP mode
  mySerial.println("AT+HTTPINIT"); 
  delay(1000);

  // AT command to set HTTP parameters
  mySerial.println("AT+HTTPPARA=\"URL\",\"http://api.thingspeak.com/update?api_key=7M3U5P0KZBJO542T&field1=VALUE1&field2=VALUE2\""); 
  delay(1000);

  // AT command to start HTTP session
  mySerial.println("AT+HTTPACTION=0");
  delay(10000);

  // AT command to read HTTP response
  mySerial.println("AT+HTTPREAD"); 
  delay(1000);
}
