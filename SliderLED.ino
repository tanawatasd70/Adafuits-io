//Example By ArduinoAll.com
#include "AdafruitIO_WiFi.h"

#define LED_PIN D6

// ตั้งค่า key ของ Adafruit IO
#define IO_USERNAME "แก้ไข_username"
#define IO_KEY "แก้ไข_key"

// ตั้งค่าชื่อ wifi
#define WIFI_SSID "แก้ไขชื่อ_wifi"
#define WIFI_PASS "แก้ไขรหัสผ่าน_wifi"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS); // สร้างออปเจกชื่อ io สำหรับติดต่อ Adafruit IO
AdafruitIO_Feed *analog = io.feed("vr"); // สร้างออปเจกสำหรับติดต่อ feed ชื่อ vr
bool current = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  while (! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect(); // เริ่มเชื่อมต่อ Adafruit IO

  while (io.status() < AIO_CONNECTED) { //เช็คว่าเชื่อมต่อสำเร็จ
    Serial.print(".");
    delay(500);
  }
  analog->onMessage(handleMessage); // เมื่อมีข้อความจาก Adafruit IO ส่งมาให้ทำที่ฟังก์ชั่น handleMessage
  Serial.println();
  Serial.println(io.statusText()); //แสดงข้อความสถานะการเชื่อมต่อกับ Adafruit IO
  analog->get(); // อ่านค่าจาก Feed ชื่อ vr
}

void loop() {
  io.run(); // เริ่มทำงานร่วมกับ Adafruit IO
}

void handleMessage(AdafruitIO_Data *data) {
  int reading = data->toInt(); // แปลงข้อความให้เป็นตัวเลข
  Serial.print("received <- ");
  Serial.println(reading);
  analogWrite(LED_PIN, reading);//หรี่ไฟ LED
}