Listing: „Cloud“
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define LED D4            
int button=D7;
int status=1;
void setup() 
{ 
    Serial.begin(115200);
    pinMode(LED, OUTPUT);    
    digitalWrite(LED, HIGH);      
    WiFi.begin(“Ihre SSID, “Das Passwort”);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print("Connecting ...");
    }
} 

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {     
     status=digitalRead(button);
     if (status==LOW)
     {
      digitalWrite(LED, LOW);     
      BearSSL::WiFiClientSecure client;
      client.setInsecure();
      HTTPClient https;
      https.begin(client, "https://make-magazin.free.beeceptor.com");
      int httpCode = https.GET();
      if (httpCode == 200)
      {
        String payload = https.getString();
        Serial.println(payload);
      }
      else
      {
        Serial.print("Fehler: ");
        Serial.println(httpCode);
      }
      https.end();
      
     }
     else
     {
      digitalWrite(LED, HIGH);
     }      
  }
}
