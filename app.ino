#include <BluetoothSerial.h>
#include <ESP32Servo.h>

BluetoothSerial SerialBT;
Servo myServo;

String receivedData = "";
String password = "1234";

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT"); // Bluetooth device name
  myServo.setPeriodHertz(50); // Standard 50Hz servo
  myServo.attach(13);          // Attach servo to GPIO 13
  myServo.write(0);            // Start at 0°
  Serial.println("Waiting for password via Bluetooth...");
}

void loop() {
  static int c = 0;
  while (SerialBT.available()) {
    c += 1;
    Serial.println("Connected");
    char incomingChar = SerialBT.read();
    Serial.print("Incoming Char: ");
    Serial.println(incomingChar);
    receivedData += incomingChar;

    if (c == 4) {
      // Password check
      if (receivedData == password) {
        Serial.println(receivedData);
        Serial.println("Correct Password");
        myServo.write(90);    // Rotate from 0° to 90°
        delay(5000);          // Wait 5 seconds
        myServo.write(0);     // Rotate back from 90° to 0°
      } else {
        Serial.println(receivedData);
        Serial.println("Incorrect Password");
      }
      receivedData = ""; // Reset for next input
      c = 0;
    }
  }
}
