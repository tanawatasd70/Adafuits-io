//Example By ArduinoAll.com
#include "AdafruitIO_WiFi.h"

// ตั้งค่า key ของ Adafruit IO
#define IO_USERNAME  "username ของตัวเอง"
#define IO_KEY       "key ของตัวเอง"

// ตั้งค่าชื่อ wifi
#define WIFI_SSID "ชื่อไวไฟล์"
#define WIFI_PASS "รหัสไวไฟล์"

#define LED_PIN 2 // LED ต่อกับขา 2
#define SW D6

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS); // สร้างออปเจกชื่อ io สำหรับติดต่อ Adafruit IO
AdafruitIO_Feed *digital = io.feed("button"); // สร้างออปเจกสำหรับติดต่อ feed ชื่อ button
bool current = false;

void setup() {

  pinMode(LED_PIN, OUTPUT);
  pinMode(SW,INPUT_PULLUP);
  Serial.begin(115200);
  while (! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect(); // เริ่มเชื่อมต่อ Adafruit IO

  digital->onMessage(handleMessage);//เมื่อมีข้อความ ให้ทำงานที่ฟังก์ชั่น handleMessage

  while (io.status() < AIO_CONNECTED) { //เช็คว่าเชื่อมต่อสำเร็จ
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText()); //แสดงข้อความสถานะการเชื่อมต่อกับ Adafruit IO
  digital->get(); // อ่านค่าจาก feed ชื่อ button
}

void loop() {
  io.run(); // เริ่มทำงานร่วมกับ Adafruit IO
  if (digitalRead(SW) == 0) { // ถ้ากดปุ่มเข้ามา
    current = !current;
    digital->save(current); // ส่งค่าไปที่ feed ชื่อ button
    delay(500);
  }
}

void handleMessage(AdafruitIO_Data *data) {//เมื่อมีข้อมูลจาก feed ชื่อ button จะทำในฟังก์ชั่นนี้
  if (data->toPinLevel() == HIGH) { // ถ้าค่าเป็น 1
    Serial.println("ON");
    digitalWrite(LED_PIN, 0);
  }
  else {
    Serial.println("OFF");
    digitalWrite(LED_PIN, 1);
  }
}