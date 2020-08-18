#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define LED D4        
void setup() 
{ 
    Serial.begin(115200);
    pinMode(LED, OUTPUT);    
    digitalWrite(LED, HIGH);      
    WiFi.begin("EasyBox-662577", "@Larinet2015");
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
        digitalWrite(LED, HIGH);
        delay(2000);
        ESP.deepSleep(0);
      }
      else
      {
        Serial.print("Fehler: ");
        Serial.println(httpCode);
      }
      https.end();
  }
}


