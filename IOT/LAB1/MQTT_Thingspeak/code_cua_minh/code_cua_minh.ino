#include "mqtt_secrets.h"   
#include <DHT.h>
#include <ESP_Mail_Client.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ==== Config DHT & Relay ====
#define DHTPIN 4            // GPIO4 = D2 trên NodeMCU ESP32
#define DHTTYPE DHT11       // hoặc DHT22
#define RELAY 5             // GPIO5 (chân D5) nối vào IN rơ-le

// ==== ThingSpeak ====
String apiKey = "OPTJ52J8VPUB9X24";   // Write API Key
const char* server = "api.thingspeak.com";

// ==== Config SMTP Gmail ====
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL   "n22dccn053@student.ptithcm.edu.vn"     
#define AUTHOR_PASSWORD "tvlw fxxd vgeq yhxb"  // App Password Gmail
#define RECIPIENT_EMAIL "n22dccn018@student.ptithcm.edu.vn"      

// ==== Global Objects ====
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
SMTPSession smtp;
Session_Config config;

ESP8266WebServer webServer(80);
float alertTemperature = 30.0;  // nhiệt độ cảnh báo mặc định

// ==== Hàm gửi Email ====
void sendEmail(String subject, String content) {
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.login.user_domain = "";

  if (!smtp.connect(&config)) {
    Serial.println("❌ Kết nối SMTP thất bại!");
    return;
  }

  SMTP_Message message;
  message.sender.name = "ESP32 Alert";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = subject;
  message.addRecipient("Người nhận", RECIPIENT_EMAIL);
  message.text.content = content;

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("❌ Gửi mail thất bại: " + smtp.errorReason());
  } else {
    Serial.println("✅ Email đã được gửi thành công!");
  }
}

// ==== Web UI ====
String htmlPage() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 Temp Control</title></head><body>";
  html += "<h1>ESP32 Temperature Alert</h1>";
  html += "<p>Temperature dangerous: " + String(alertTemperature) + " °C</p>";
  html += "<form action=\"/set\" method=\"GET\">";
  html += "<input type=\"range\" name=\"temp\" min=\"10\" max=\"50\" step=\"0.5\" value=\"" + String(alertTemperature) + "\">";
  html += "<input type=\"submit\" value=\"Set\">";
  html += "</form>";
  html += "</body></html>";
  return html;
}

void handleRoot() {
  webServer.send(200, "text/html", htmlPage());
}

void handleSet() {
  if (webServer.hasArg("temp")) {
    alertTemperature = webServer.arg("temp").toFloat();
    Serial.println("⚙️ Alert Temperature set to: " + String(alertTemperature));
  }
  webServer.sendHeader("Location", "/");
  webServer.send(303);
}

// ==== Setup ====
void setup() {
  Serial.begin(115200);

  // Kết nối WiFi
  WiFi.begin(SECRET_WIFI_NAME, SECRET_WIFI_PASSWORD);
  Serial.print("🔌 Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");
  Serial.print("📡 IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  dht.begin();

  // Khởi động Web server
  webServer.on("/", handleRoot);
  webServer.on("/set", handleSet);
  webServer.begin();
  Serial.println("🌐 Web server started");
}

// ==== Loop ====
void loop() {
  webServer.handleClient(); // xử lý request web

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("⚠️ Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  // --- Gửi dữ liệu lên ThingSpeak ---
  if (client.connect(server, 80)) {
    String postStr = "field1=" + String(temperature) 
                   + "&field2=" + String(humidity);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + apiKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(postStr.length());
    client.println();
    client.println(postStr);

    Serial.println("📤 Data sent to ThingSpeak!");
  }
  client.stop();

  // --- In ra serial monitor ---
  Serial.print("🌡️ Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, 💧 Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // --- Điều khiển relay và gửi email ---
  if (temperature >= alertTemperature) {
    digitalWrite(RELAY, HIGH);  // còi hú
    Serial.println("🚨 Relay ON - Cảnh báo nhiệt độ cao!");
    sendEmail("⚠️ Cảnh báo nhiệt độ", "Nhiệt độ hiện tại: " + String(temperature) + " °C\nĐộ ẩm: " + String(humidity) + " %");
    delay(1000); // còi hú 1 giây
    digitalWrite(RELAY, LOW); // tắt relay sau 1s
  } else {
    digitalWrite(RELAY, LOW);   // tắt relay
    Serial.println("✅ Nhiệt độ an toàn, relay OFF.");
  }

  delay(20000); // tránh giới hạn ThingSpeak (>=15s)
}
