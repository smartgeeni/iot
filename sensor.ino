#include <DHT.h>
#define DHTPIN 2
// DHT11 data pin
#define DHTTYPE DHT11
#define BUZZER_PIN 8
// Active buzzer pin (HIGH = ON)
// Temperature range
const float TEMP_MIN = 25.0; // °C
const float TEMP_MAX = 30.0; // °C
// Timing settings
const unsigned long BUZZ_MS = 1000;
// 1 second buzz
const unsigned long READ_INTERVAL_MS = 2000; // DHT11: read no faster than ~1-2s
const unsigned long COOLDOWN_MS = 5000; // minimum time between beeps
DHT dht(DHTPIN, DHTTYPE);
// State
bool buzzerOn = false;
unsigned long buzzStartMs = 0;
unsigned long lastReadMs = 0;
unsigned long lastTriggerMs = 0;
void setup() {
Serial.begin(115200);
dht.begin();
pinMode(BUZZER_PIN, OUTPUT);
digitalWrite(BUZZER_PIN, LOW);
Serial.println(F("DHT11 range buzzer ready."));
}
void loop() {
unsigned long now = millis();
// Time-gated sensor read
if (now - lastReadMs >= READ_INTERVAL_MS) {
lastReadMs = now;
float t = dht.readTemperature(); // Celsius
if (isnan(t)) {
Serial.println(F("DHT read failed"));
} else {
Serial.print(F("Temp: "));
Serial.print(t);
Serial.println(F(" °C"));// Check if temp is within the range and cooldown is over
if (t >= TEMP_MIN && t <= TEMP_MAX && (now - lastTriggerMs >= COOLDOWN_MS))
{
turnBuzzerOn();
buzzStartMs = now;
lastTriggerMs = now;
}
}
}
// Handle buzzer duration without delay()
if (buzzerOn && (now - buzzStartMs >= BUZZ_MS)) {
turnBuzzerOff();
}
}
void turnBuzzerOn() {
buzzerOn = true;
digitalWrite(BUZZER_PIN, HIGH);
Serial.println(F("BUZZER ON"));
}
void turnBuzzerOff() {
buzzerOn = false;
digitalWrite(BUZZER_PIN, LOW);
Serial.println(F("BUZZER OFF"));
}
