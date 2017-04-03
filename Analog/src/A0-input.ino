
int Adata=0;

void setup() {
   Serial.begin(9600);
}

void loop() {
   Adata = analogRead(A0);
   Serial.println(Adata);
   delay(250);
}
