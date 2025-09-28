#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <FirebaseESP32.h>
#include <UniversalTelegramBot.h>
#include <PubSubClient.h>
#include "esp_camera.h"
#include "secrets.h"   // file chứa WiFi, API key

/******************** WIFI ********************/
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

/******************** FIREBASE ********************/
#define FIREBASE_HOST "your-project-id.firebaseio.com"
#define FIREBASE_AUTH "YOUR_FIREBASE_DATABASE_SECRET"
FirebaseData fbdo;

/******************** TELEGRAM ********************/
#define BOT_TOKEN "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID   "YOUR_TELEGRAM_CHAT_ID"
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long lastTelegramCheck = 0;

/******************** MQTT ********************/
const char* mqtt_server = "test.mosquitto.org";
WiFiClient espClient;
PubSubClient client(espClient);

/******************** CAMERA PINOUT (AI-Thinker) ********************/
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    0
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27

#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      21
#define Y4_GPIO_NUM      19
#define Y3_GPIO_NUM      18
#define Y2_GPIO_NUM      5
#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22

/******************** INIT ********************/
void startCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_SVGA;
  config.jpeg_quality = 10;
  config.fb_count = 2;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

/******************** MQTT CALLBACK ********************/
void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.printf("MQTT message: %s\n", msg.c_str());

  if (msg == "capture") {
    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      return;
    }
    // Upload ảnh lên Firebase
    String path = "/esp32cam/latest.jpg";
    Firebase.setBinary(fbdo, path, fb->buf, fb->len);
    esp_camera_fb_return(fb);
  }
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32CAMClient")) {
      Serial.println("connected");
      client.subscribe("esp32/cam");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

/******************** SETUP ********************/
void setup() {
  Serial.begin(115200);
  delay(1000);

  // WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.println(WiFi.localIP());

  // Camera
  startCamera();

  // Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Telegram
  secured_client.setInsecure();  // bỏ qua SSL check
  bot.sendMessage(CHAT_ID, "ESP32-CAM is online!", "");

  // MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

/******************** LOOP ********************/
void loop() {
  if (!client.connected()) reconnectMQTT();
  client.loop();

  // Kiểm tra tin nhắn Telegram mỗi 2 giây
  if (millis() - lastTelegramCheck > 2000) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("Got Telegram message");
      String text = bot.messages[0].text;
      if (text == "/capture") {
        camera_fb_t* fb = esp_camera_fb_get();
        if (!fb) {
          bot.sendMessage(CHAT_ID, "Capture failed!", "");
        } else {
          bot.sendMessage(CHAT_ID, "Captured image and uploaded to Firebase!", "");
          Firebase.setBinary(fbdo, "/esp32cam/latest.jpg", fb->buf, fb->len);
          esp_camera_fb_return(fb);
        }
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTelegramCheck = millis();
  }
}
