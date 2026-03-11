#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// WiFi credentials
const char* ssid = "Vickline";
const char* password = "1234567890";

// Telegram bot info
#define BOTtoken "8203603958:AAF0Q1odNk5apWQ9aYbCAmofMFEgo7Ab3J8"
#define CHAT_ID "6357020492"

// Pins
#define WATER_SENSOR A0
#define GREEN_LED 2
#define RED_LED 5
#define BUZZER 4

int threshold = 200;
String locationName = "Storage Tank Pipe";

// States
bool leakDetected = false;
bool lastLeakState = false;

// Timing
unsigned long buzzerStart = 0;
bool buzzerActive = false;

unsigned long lastReminder = 0;
const unsigned long reminderInterval = 60000; // 1 minute

// WiFi check
unsigned long lastWiFiCheck = 0;
const unsigned long wifiCheckInterval = 5000;

// Telegram client
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Message queue for reliable Telegram messages
String pendingMessage = "";
bool messagePending = false;
unsigned long lastMessageTime = 0;
const unsigned long messageCooldown = 1000; // 1s between messages


// Telegram send function
void sendTelegram(String message) {
  bot.sendMessage(CHAT_ID, message, "");
  Serial.println("Telegram sent: " + message);
}


void setup() {
  Serial.begin(115200);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  client.setInsecure();
  client.setTimeout(15000);
}

// Main loop
void loop() {
  unsigned long now = millis();

  // WiFi reconnect every 5s if really lost
  if(now - lastWiFiCheck >= wifiCheckInterval) {
    lastWiFiCheck = now;
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi lost. Reconnecting...");
      WiFi.begin(ssid, password);
    }
  }

  // Read sensor
  int sensorValue = analogRead(WATER_SENSOR);
  leakDetected = (sensorValue > threshold);

  Serial.print("Sensor: "); Serial.print(sensorValue);
  Serial.print(" | Leak: "); Serial.println(leakDetected);

  // Detect state change
  if (leakDetected != lastLeakState) {
    if (leakDetected) {
      pendingMessage = "Water Leak Detected!\n Location: " + locationName;

      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);

      digitalWrite(BUZZER, HIGH);
      buzzerStart = now;
      buzzerActive = true;

      lastReminder = now;
    } else {
      pendingMessage = "Leak Cleared\n Location: " + locationName;

      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);

      digitalWrite(BUZZER, LOW);
      buzzerActive = false;
    }
    messagePending = true;
    lastLeakState = leakDetected; // Update state after preparing message
  }

  // Send pending Telegram message if cooldown passed
  if (messagePending && now - lastMessageTime >= messageCooldown) {
    sendTelegram(pendingMessage);
    lastMessageTime = now;
    messagePending = false;
  }

  // Reminder if leak persists
  if (leakDetected && (now - lastReminder >= reminderInterval)) {
    pendingMessage = "Reminder: Leak still active\n Location: " + locationName;
    messagePending = true;
    lastReminder = now;
  }

  // Buzzer off after 10 seconds
  if (buzzerActive && (now - buzzerStart >= 10000)) {
    digitalWrite(BUZZER, LOW);
    buzzerActive = false;
  }
}
