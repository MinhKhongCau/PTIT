#include "esp_camera.h"
#include <WiFi.h>

// ==== Cấu hình WiFi ====
const char* ssid = "KimHong2";    
const char* password = "09889441722";

// ==== Cấu hình module camera AI Thinker ====
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void startCameraServer();

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  Serial.println("🚀 Khởi động ESP32-CAM...");

  // ==== Cấu hình Camera ====
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // Cấu hình độ phân giải
  if(psramFound()){
    config.frame_size = FRAMESIZE_VGA;  // có thể chọn: FRAMESIZE_QVGA, SVGA, XGA, SXGA, UXGA
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Khởi động camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("❌ Lỗi khởi động camera: 0x%x", err);
    return;
  }

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  Serial.print("🔌 Đang kết nối WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Kết nối thành công!");
  Serial.print("🌐 Địa chỉ IP: ");
  Serial.println(WiFi.localIP());

  // Khởi động server stream
  startCameraServer();

  Serial.println("📸 Mở trình duyệt và truy cập link trên để xem video!");
}

void loop() {
  delay(10000); // không cần xử lý gì trong loop
}

// ==== Hàm khởi động server ====
#include <WebServer.h>
WebServer server(80);

void handle_jpg_stream() {
  WiFiClient client = server.client();
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  server.sendContent(response);

  while (client.connected()) {
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("❌ Không lấy được frame");
      continue;
    }
    server.sendContent("--frame\r\n");
    server.sendContent("Content-Type: image/jpeg\r\n\r\n");
    client.write(fb->buf, fb->len);
    server.sendContent("\r\n");
    esp_camera_fb_return(fb);
    delay(30);  // tốc độ khung hình
  }
}

void handle_root() {
  server.sendHeader("Location", "/stream");
  server.send(302);
}

void startCameraServer() {
  server.on("/", handle_root);
  server.on("/stream", HTTP_GET, handle_jpg_stream);
  server.begin();
  Serial.println("✅ Web server đã khởi động!");
}
