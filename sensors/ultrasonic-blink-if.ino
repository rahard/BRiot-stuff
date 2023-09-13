// refer to board's GPIO PIN number Mapping
const int trigPin = D5;   
const int echoPin = D6;   
long duration;  
int distance;  

void setup() {  
   // define LED PIN
   pinMode(LED_BUILTIN, OUTPUT);
   // init trigger & echo pin
   pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT); 
   Serial.begin(9600); // 
} 

void loop() {  
   digitalWrite(trigPin, LOW);  
   delayMicroseconds(2);  
   // Sets the trigPin on HIGH state for 10 micro seconds  
   digitalWrite(trigPin, HIGH);  
   delayMicroseconds(10);  
   digitalWrite(trigPin, LOW);  

   // Reads the echoPin, returns the sound wave travel time in microseconds  
   duration = pulseIn(echoPin, HIGH);  
   // Calculating the distance  
   distance = duration*0.034/2;  

   // if distance is greater than, set LED ON
   if (distance <= 25) {
        digitalWrite(LED_BUILTIN, LOW);
   } else {
        digitalWrite(LED_BUILTIN, HIGH);
   }

   // Prints the distance on the Serial Monitor  
   Serial.print("Distance: ");  
   Serial.println(distance);  
   delay(100);  
 }  
