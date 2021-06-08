/* blinking LED for various boards
   Budi Rahardjo @rahard
*/

/* for WeMOS do not define LED_BUILTIN. comment the line */
/* for AI Thinker ESP32 it's 33 */
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
