/******************
* ESP8266 + DHT11 + Buzzer + ThingSpeak MQTT
* Professional Serial Logs
******************/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// -------- WiFi Credentials ----------

const char* ssid = "impraveena";
const char* password = "abcdefgh";

// -------- ThingSpeak MQTT Credentials ----------

const char* mqttServer = "mqtt3.thingspeak.com";
const int mqttPort = 1883;//DEFAULT PORTNUMBER
const char* mqttUserName = "DBIuHwImOiYaFDoYKTYJDBw";
const char* mqttClientID = "DBIuHwImOiYaFDoYKTYJDBw";
const char* mqttPass = "tEctIczoKZz4/Fzp0pgheRIu";
const long channelID = 2806532;


#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastPublish = 0;


void connectWiFi() {
Serial.print("Connecting to WiFi");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(400);
Serial.print(".");
}
Serial.println("\nWiFi connected");
}


void reconnectMQTT() {
while (!client.connected()) {
Serial.print("Connecting to MQTT...");
if (client.connect(mqttClientID, mqttUserName, mqttPass)) {
Serial.println("MQTT connected");
} else {
Serial.print("Failed (rc=");
Serial.print(client.state());
Serial.println("). Retrying...");
delay(2000);
}
}
}


bool readDHT(float &temperature, float &humidity) {
const int maxAttempts = 5;
for (int i = 0; i < maxAttempts; i++) {
humidity = dht.readHumidity();
temperature = dht.readTemperature();
if (!isnan(humidity) && !isnan(temperature)) {
return true; 
}
delay(200); 
}
return false;
}

=
void setup() {
Serial.begin(115200);
dht.begin();
connectWiFi();
client.setServer(mqttServer, mqttPort);
reconnectMQTT();
}


void loop() {
if (WiFi.status() != WL_CONNECTED) {
Serial.println("WiFi disconnected. Reconnecting...");
connectWiFi();
}
if (!client.connected()) {
Serial.println("MQTT disconnected. Reconnecting...");
reconnectMQTT();
}
client.loop();
unsigned long now = millis();
if (now - lastPublish > 20000) { 
lastPublish = now;
float t, h;
if (!readDHT(t, h)) {
Serial.println("Sensor failed");
return;
}


Serial.print("Sensor values : T = ");
Serial.print(t,1);
Serial.print(" °C, H = ");
Serial.print(h,1);
Serial.println(" %");

