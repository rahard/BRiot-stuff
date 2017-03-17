/* blinking LED for NodeMCU
   Budi Rahardjo @rahard
*/
#define LED_BUILTIN D0

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}
