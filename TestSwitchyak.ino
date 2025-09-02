//Example By ArduinoAll.com
#include "AdafruitIO_WiFi.h"

// ตั้งค่า key ของ Adafruit IO
#define IO_USERNAME  "username ของตัวเอง"
#define IO_KEY       "key ของตัวเอง"

// ตั้งค่าชื่อ wifi
#define WIFI_SSID "ชื่อไวไฟล์"
#define WIFI_PASS "รหัสไวไฟล์"

#define SW D6 // สวิตช์ ต่อกับขา D6

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS); // สร้างออปเจกชื่อ io สำหรับติดต่อ Adafruit IO
AdafruitIO_Feed *digital = io.feed("button"); // สร้างออปเจกสำหรับติดต่อ feed ชื่อ button

bool current = false;
void setup() {

  pinMode(SW, INPUT_PULLUP);
  Serial.begin(115200);
  while (! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect(); // เริ่มเชื่อมต่อ Adafruit IO


  while (io.status() < AIO_CONNECTED) { //เช็คว่าเชื่อมต่อสำเร็จ
    Serial.print(".");
    delay(500);
  }
  digital->save(current);
  Serial.println();
  Serial.println(io.statusText()); //แสดงข้อความสถานะการเชื่อมต่อกับ Adafruit IO

}

void loop() {
  io.run(); // เริ่มทำงานร่วมกับ Adafruit IO
  if (digitalRead(SW) == 0) { // ถ้ากดปุ่มเข้ามา
    current = !current;
    digital->save(current); // ส่งค่าไปที่ feed ชื่อ button
    delay(500);
  }
}