#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// ESP Pins
#define D0 16
#define D5 14
#define D6 12
#define D7 13

//#define BEECEPTOR
#define THINGSPEAK
// #define THINGTWEET

int button = D7;
int status= 1;
String APIkey_ThingTweet = "II4IHBJPOU20TAW8";	// durch Ihren Thingtweet-API-Key ersetzen
String APIkey_ThingSpeak = "2S7PDUM33WCSLJAM";	// durch Ihren Thingtweet-API-Key ersetzen
HTTPClient https;

void setup() { 
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);    
	digitalWrite(LED_BUILTIN, HIGH);      
	pinMode(D7, INPUT);    
	digitalWrite(D7, HIGH);      
	WiFi.begin("FRITZ!Box 6490 Cable", "88462590539281722797");
	delay(1000);
	Serial.println("");
	Serial.print("Connecting...");
	while (WiFi.status() != WL_CONNECTED)
	{
		digitalWrite(LED_BUILTIN, LOW);      
		delay(500);
		digitalWrite(LED_BUILTIN, HIGH);      
		delay(500);
		Serial.print(".");
	}
	Serial.println(" Done!");
} 

void loop() {
	String payload, tweet, button_value;
	if (WiFi.status() == WL_CONNECTED) {     
		status = digitalRead(button);
		if (status == LOW) {
			BearSSL::WiFiClientSecure client;
			client.setInsecure();
			Serial.println("Button betätigt!");
			digitalWrite(LED_BUILTIN, LOW);     

#ifdef BEECEPTOR
			// Abschnitt mit URL zum Testen per Beeceptor
			https.begin(client, "https://keyboardpartner.free.beeceptor.com");
#endif

#ifdef THINGSPEAK
			// Abschnitt für Visualisierung von Thingspeak
			button_value = "1";
			https.begin(client, "https://api.thingspeak.com/update?api_key=" 
				+  APIkey_ThingSpeak + "&field1=" + button_value); 
#endif

#ifdef THINGTWEET
			// Abschnitt für Twitter-API von Thingspeak
			tweet = "Der+Button+wurde+betätigt"; 
			https.begin(client, "https://api.thingspeak.com/apps/thingtweet/1/statuses/update?api_key=" 
				+  APIkey_ThingTweet + "&status=" + tweet); 
#endif

			Serial.println("Antwort des Dienstes:");
			int httpCode = https.GET();
			if (httpCode == 200) {
				payload = https.getString();
				Serial.println("Event:" + payload);
			} else {
				Serial.print("Fehler: ");
				Serial.println(httpCode);
			}
			https.end();

			// Warten, bis Taste wieder losgelassen. LED blinkt schnell
			while (digitalRead(button) == LOW) {
				digitalWrite(LED_BUILTIN, LOW);      
				delay(150);
				digitalWrite(LED_BUILTIN, HIGH);      
				delay(150);
			}

			digitalWrite(LED_BUILTIN, HIGH);
		}      
	}
}
