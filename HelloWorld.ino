#define LED D4            
void setup() 
{ 
     pinMode(LED, OUTPUT);    
} 
  
void loop() 
{ 
    digitalWrite(LED, HIGH); 
    delay(3000);             
    digitalWrite(LED, LOW);  
    delay(1000);             
}

