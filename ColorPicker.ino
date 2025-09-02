//Example By ArduinoAll.com
#include "AdafruitIO_WiFi.h"

// กำหนดขา LED ที่ต่อกับ NodeMCU
#define RED_PIN   D5
#define GREEN_PIN D6
#define BLUE_PIN  D7

// ตั้งค่า key ของ Adafruit IO
#define IO_USERNAME "แก้ไข_username"
#define IO_KEY "แก้ไข_key"

// ตั้งค่าชื่อ wifi
#define WIFI_SSID "แก้ไขชื่อ_wifi"
#define WIFI_PASS "แก้ไขรหัสผ่าน_wifi"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS); // สร้างออปเจกชื่อ io สำหรับติดต่อ Adafruit IO
AdafruitIO_Feed *color = io.feed("color"); // สร้างออปเจกสำหรับติดต่อ feed ชื่อ vr
bool current = false;

void setup() {
  Serial.begin(115200);
  while (! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect(); // เริ่มเชื่อมต่อ Adafruit IO

  while (io.status() < AIO_CONNECTED) { //เช็คว่าเชื่อมต่อสำเร็จ
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText()); //แสดงข้อความสถานะการเชื่อมต่อกับ Adafruit IO

  color->onMessage(handleMessage); // เมื่อมีค่าสีส่งเข้ามาจาก Adafruit IO
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  io.run(); // เริ่มทำงานร่วมกับ Adafruit IO
  delay(1000);
}

void handleMessage(AdafruitIO_Data *data) {
  // แสดงค่า R G B ที่ได้รับเข้ามาจาก Adafruit IO
  Serial.println("Received:");
  Serial.print("  - R: ");
  Serial.println(data->toRed());
  Serial.print("  - G: ");
  Serial.println(data->toGreen());
  Serial.print("  - B: ");
  Serial.println(data->toBlue());
  Serial.print("  - HEX: ");
  Serial.println(data->value());

  analogWrite(RED_PIN, map( data->toRed(), 0, 255, 0, 1024));
  analogWrite(GREEN_PIN, map(data->toGreen(), 0, 255, 0, 1024));
  analogWrite(BLUE_PIN, map( data->toBlue(), 0, 255, 0, 1024));
}