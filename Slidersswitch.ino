//Example By ArduinoAll.com
#include "AdafruitIO_WiFi.h"


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
}

void loop() {
  io.run(); // เริ่มทำงานร่วมกับ Adafruit IO
  int val = analogRead(A0); // อ่านค่า analog จากขา A0
  analog->save(val); // ส่งค่าไปที่ feed ชื่อ vr
  Serial.println(val);
  delay(3000); // Adafruit IO เวอร์ชั่นฟรี ส่งค่าได้เร็วสุด 2 วินาที/ค่า
}
