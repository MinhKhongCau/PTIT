#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h> // Thư viện cho màn hình IPS LCD 240x240 ST7789
#include "images.h"           // Tệp chứa 5 mảng ảnh của bạn

// ================= ST7789 TFT (240x240) =================
#define TFT_CS    25  // Đã đổi theo sơ đồ mới
#define TFT_RST   32  // Đã đổi theo sơ đồ mới
#define TFT_DC    33  // Đã đổi theo sơ đồ mới

// Giữ GPIO18 & GPIO23 vì GPIO34/35 là chân Input-Only không xuất tín hiệu SPI được
#define TFT_MOSI  27  // SDA (MOSI)
#define TFT_MISO  -1
#define TFT_SCK   14  // SCL (CLK)

#define TFT_BL    15  // Đèn nền màn hình

// ================ Button & Buzzer ===============
#define BUTTON_PIN 26 // Đã đổi theo sơ đồ mới
#define BUZZER_PIN 12 // Đã đổi theo sơ đồ mới

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// PWM Backlight Config
const int BL_FREQ = 5000;
const int BL_RESOLUTION = 8;

// Biến quản lý chuyển slide ảnh
int currentImageIndex = 0;

// Định nghĩa mảng con trỏ chứa 5 ảnh nền duy nhất tại file .ino
const uint8_t* const bg_images[5] PROGMEM = {
  img1_map,
  img2_map,
  img3_map,
  img4_map,
  img5_map
};

//----------------------------------------

void setBacklight(uint8_t duty) {
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(TFT_BL, duty);
#else
  ledcWrite(0, duty);
#endif
}

void beep(int freq, int duration) {
  Serial.printf("[BUZZER] Phát âm thanh: %d Hz (%d ms)\n", freq, duration);
  tone(BUZZER_PIN, freq);
  delay(duration);
  noTone(BUZZER_PIN);
}

void fadeInBacklight() {
  Serial.println("[TFT] Bật đèn nền (Fade in)...");
  for (int i = 0; i <= 255; i += 15) {
    setBacklight(i);
    delay(20);
  }
  setBacklight(255);
}

// Vẽ 1 tấm hình trong mảng 5 hình lên toàn màn hình (240x240)
void drawBackgroundImage(int index) {
  Serial.printf("[TFT] Hiển thị background ảnh thứ %d/5\n", index + 1);
  // Dùng pgmspace draw bitmap trực tiếp từ flash memory
  tft.drawRGBBitmap(0, 0, (const uint16_t*)pgm_read_ptr(&(bg_images[index])), 240, 240);
}

void showCenteredNumber(int number) {
  // Vẽ background ảnh hiện tại trước
  drawBackgroundImage(currentImageIndex);

  // Đổi nền chữ hoặc dùng màu nổi bật để đè lên ảnh
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(9); // Size 9 vừa vặn với chiều cao 240px

  String txt = String(number);

  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(txt, 0, 0, &x1, &y1, &w, &h);

  // Căn giữa chính xác trục X và Y cho màn hình 240x240
  int x = (240 - (int)w) / 2 - x1;
  int y = (240 - (int)h) / 2 - y1;

  tft.setCursor(x, y);
  tft.print(txt);
  
  Serial.printf("[TFT] Hiển thị số đếm ngược: %d\n", number);

  // Chuyển sang ảnh kế tiếp cho lần hiển thị sau
  currentImageIndex = (currentImageIndex + 1) % 5;
}

void countdown() {
  Serial.println("[SYSTEM] Bắt đầu đếm ngược (Mỗi số chính xác 1 giây)...");
  for (int i = 3; i >= 1; i--) {
    showCenteredNumber(i);
    beep(1200, 150);
    
    // Đảm bảo tổng thời gian hiển thị số chuẩn 1000ms (1s)
    delay(850); 
  }
}

void showBirthdayScreen() {
  Serial.println("[TFT] Hiển thị màn hình \"HAPPY BIRTHDAY!\"");
  
  // Hiển thị background ảnh tiếp theo trong chuỗi 5 ảnh
  drawBackgroundImage(currentImageIndex);
  currentImageIndex = (currentImageIndex + 1) % 5;

  tft.setTextColor(ST77XX_MAGENTA);
  tft.setTextSize(3); // Giảm xuống Size 3 cho vừa khung màn hình 240x240

  int16_t x1, y1;
  uint16_t w1, h1, w2, h2;

  // Tính toán vị trí chuẩn căn giữa cho dòng 1 ("HAPPY")
  tft.getTextBounds("HAPPY", 0, 0, &x1, &y1, &w1, &h1);
  int x_happy = (240 - (int)w1) / 2 - x1;

  // Tính toán vị trí chuẩn căn giữa cho dòng 2 ("BIRTHDAY!")
  tft.getTextBounds("BIRTHDAY!", 0, 0, &x1, &y1, &w2, &h2);
  int x_bday = (240 - (int)w2) / 2 - x1;

  // Căn chỉnh khoảng cách 2 dòng đều đặn ở giữa màn hình
  tft.setCursor(x_happy, 70);
  tft.println("HAPPY");

  tft.setCursor(x_bday, 130);
  tft.println("BIRTHDAY!");
}

void playHappyBirthday() {
  Serial.println("[BUZZER] Bắt đầu phát nhạc Happy Birthday...");

  int melody[] = {
    262,262,294,262,349,330,
    262,262,294,262,392,349,
    262,262,523,440,349,330,294,
    466,466,440,349,392,349
  };

  int duration[] = {
    250,250,500,500,500,1000,
    250,250,500,500,500,1000,
    250,250,500,500,500,500,1000,
    250,250,500,500,500,1000
  };

  int total = sizeof(melody) / sizeof(int);

  for (int i = 0; i < total; i++) {
    tone(BUZZER_PIN, melody[i]);
    delay(duration[i]);
    noTone(BUZZER_PIN);
    
    // Đảm bảo sau mỗi nốt nhạc, đèn nền được "bồi" lại độ sáng 
    // tránh việc bộ PWM bị tụt áp hoặc mất xung
    setBacklight(255); 
    
    delay(50);
  }
  Serial.println("[BUZZER] Hoàn tất bài nhạc.");
}

void runBirthdayShow() {
  Serial.println("\n==========================================");
  Serial.println("[SYSTEM] KÍCH HOẠT CHƯƠNG TRÌNH BIRTHDAY SHOW");
  Serial.println("==========================================");

  setBacklight(0);
  beep(1800, 200);

  fadeInBacklight();
  countdown();
  showBirthdayScreen();
  playHappyBirthday();

  Serial.println("[SYSTEM] Kết thúc chương trình.\n");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("[SYSTEM] Khởi tạo hệ thống ESP32...");

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  // Khởi tạo SPI và màn hình ST7789 240x240
  SPI.begin(TFT_SCK, TFT_MISO, TFT_MOSI, TFT_CS);
  tft.init(240, 240); // Màn hình ST7789 vuông 240x240
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);
  Serial.println("[TFT] Màn hình ST7789 IPS 240x240 khởi tạo thành công");

  // PWM Backlight
#if defined(ESP_ARDUINO_VERSION_MAJOR) && ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(TFT_BL, BL_FREQ, BL_RESOLUTION);
#else
  ledcSetup(0, BL_FREQ, BL_RESOLUTION);
  ledcAttachPin(TFT_BL, 0);
#endif
  setBacklight(0);

  Serial.println("[SYSTEM] Sẵn sàng. Nhấn nút để bắt đầu!");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(20);

    if (digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("[BUTTON] Đã nhấn nút!");

      runBirthdayShow();

      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10);
      }
      delay(500);
    }
  }
}