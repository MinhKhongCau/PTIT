#include <DHT.h>
#include <DHT_U.h>

#include <ESP8266WiFi.h>
#include "mqtt_secrets.h"

#define DHTPIN D2
#define DHTTYPE DHT11
#define RELAY D0

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

String apiKey = SECRET_MQTT_USERNAME;  // ThingSpeak Write API Key
const char* server = "api.thingspeak.com";  // Cloud server

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  // Connect to WiFi
  WiFi.begin(SECRET_MQTT_WIFI_NAME, SECRET_MQTT_WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // độ C

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C, Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  // Kết nối đến ThingSpeak và gửi dữ liệu
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.println("Data sent to ThingSpeak!");
  }

  client.stop();

  // Ví dụ: bật relay nếu nhiệt độ > 30
  if (t > 30) {
    digitalWrite(RELAY, HIGH);
  } else {
    digitalWrite(RELAY, LOW);
  }

  delay(20000); // ThingSpeak yêu cầu >=15s giữa các lần ghi
}
