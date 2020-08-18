#include <ESP8266WiFi.h>
void setup() 
{ 
    Serial.begin(115200);
    
    WiFi.begin("EasyBox-662577", "@Larinet2015");
    
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print("Ich verbinde ...");
    }
}

void loop() 
{ 
           
}

