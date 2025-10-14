// Arduino Blink Example
// Blinks the built-in LED on pin 13
#define LED_PIN 13 // On most Arduino boards, pin 13 has a built-in LED
void setup() {
pinMode(LED_PIN, OUTPUT); // Set LED pin as output
}
void loop() {
digitalWrite(LED_PIN, HIGH); // Turn LED ON
delay(1000);
// Wait 1 second
digitalWrite(LED_PIN, LOW); // Turn LED OFF
delay(1000);
// Wait 1 second
}
