const int trigPin = 2;   
const int echoPin = 4;   
long duration;  
int distance;  

void setup() {  
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
   distance= duration*0.034/2;  

   // Prints the distance on the Serial Monitor  
   Serial.print("Distance: ");  
   Serial.println(distance);  
   delay(100);  
 }  

