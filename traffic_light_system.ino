#include <Wire.h>
#include "RTClib.h"
#include <ESP8266WiFi.h>  // WiFi library for ESP8266

#define RED_PIN    D6  // GPIO12
#define GREEN_PIN  D8  // GPIO15
#define YELLOW_PIN D7  // GPIO13

RTC_DS3231 rtc;

// WiFi credentials
const char* ssid = "Galaxy A06";
const char* password = "12345678";

void setup() {
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Wire.begin(); // Initialize I2C for RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
}

void loop() {
  DateTime now = rtc.now();

  int hour = now.hour();
  int minute = now.minute();

  Serial.print("Time: ");
  Serial.print(hour);
  Serial.print(":");
  Serial.println(minute);

  if (hour >= 6 && hour <= 15) {
    if (minute >= 0 && minute < 59) {
      // Turn on RED
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      delay(2000);

      // Turn on YELLOW
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      delay(3000);

      // Turn on GREEN
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(YELLOW_PIN, LOW);
      delay(2000);

      // Turn on YELLOW
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(YELLOW_PIN, HIGH);
      delay(1000);

      // Turn on RED
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      delay(2000);
    } else {
      lightColor("OFF");
    }
  } else {
    lightColor("OFF");
  }

  delay(100);
}

void lightColor(String color) {
  if (color == "RED") {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
  } else if (color == "GREEN") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
  } else if (color == "YELLOW") {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);
  } else {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
  }
}
