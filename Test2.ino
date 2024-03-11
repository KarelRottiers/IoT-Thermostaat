#define BLYNK_TEMPLATE_ID "user12"
#define BLYNK_TEMPLATE_NAME "user12@server.wyns.it"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "4ZxxWy2LjJtcwxGcdLOgwiAGvxkyYAwW";
char ssid[] = "embed";
char pass[] = "weareincontrol";

int lm35Pin = 32;      // Analog pin connected to LM35 sensor
int lm35Value;         // Variable to store LM35 sensor value
int gezetteWaarde = 0; // Initialize the gezetteWaarde

const int increaseButtonPin = 34; // Pin for the increase button
const int decreaseButtonPin = 35; // Pin for the decrease button

void setup() {
  pinMode(lm35Pin, INPUT);      // Set LM35 pin as input
  pinMode(LED_BUILTIN, OUTPUT); // Set built-in LED pin as output
  pinMode(increaseButtonPin, INPUT_PULLUP); // Set increase button pin as input with internal pull-up resistor
  pinMode(decreaseButtonPin, INPUT_PULLUP); // Set decrease button pin as input with internal pull-up resistor

  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);
}

void loop() {
  Blynk.run();

  // Read LM35 sensor value
  lm35Value = analogRead(lm35Pin);

  // Send LM35 value to Blynk app
  Blynk.virtualWrite(V1, lm35Value);

  Blynk.virtualWrite(V3, gezetteWaarde);

  // Print LM35 value to Serial monitor
  Serial.print("LM35: ");
  Serial.println(lm35Value);

  // Check if LM35 value is above 27 degrees
  if (lm35Value > 27) {
    digitalWrite(LED_BUILTIN, HIGH); // Turn on LED
  } else {
    digitalWrite(LED_BUILTIN, LOW); // Turn off LED
  }

  // Check if increase button is pressed
  if (digitalRead(increaseButtonPin) == 1) {
    gezetteWaarde++;
    delay(250); // Add a small delay to debounce the button
  }

  // Check if decrease button is pressed
  if (digitalRead(decreaseButtonPin) == 1) {
    gezetteWaarde--;
    delay(250); // Add a small delay to debounce the button
  }




  delay(200);  // Adjust delay as needed
}