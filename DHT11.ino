#include "DHT.h"
#include "AdafruitIO_WiFi.h"


// ตั้งค่า key ของ Adafruit IO
#define IO_USERNAME "แก้ไข_username"
#define IO_KEY "แก้ไข_key"

// ตั้งค่าชื่อ wifi
#define WIFI_SSID "แก้ไขชื่อ_wifi"
#define WIFI_PASS "แก้ไขรหัสผ่าน_wifi"

#define DHTPIN D2 // DHT ต่อกับขา 2
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS); // สร้างออปเจกชื่อ io สำหรับติดต่อ Adafruit IO
AdafruitIO_Feed *temp = io.feed("temp"); // สร้างออปเจกสำหรับติดต่อ feed ชื่อ temp
AdafruitIO_Feed *humidity = io.feed("humidity"); // สร้างออปเจกสำหรับติดต่อ feed ชื่อ humidity

DHT dht(DHTPIN, DHTTYPE);

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

  dht.begin();
}

void loop() {
  // หน่วงเวลา 4 วินาทีเพื่อให้เซนเซอร์ทำงาน
  delay(4000);
  float h = dht.readHumidity(); // อ่านค่าความชื้น
  float t = dht.readTemperature(); // อ่านค่าอุณหภูมิ

  humidity->save(h); // ส่งค่าไปที่ feed ชื่อ humidity
  temp->save(t);// ส่งค่าไปที่ feed ชื่อ temp

  Serial.print("Temp : ");
  Serial.print(t);
  Serial.print(" C Humidity : ");
  Serial.println(h);
}