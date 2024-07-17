#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <NewPing.h>
#include <Servo.h>

// Inisialisasi LCD I2C dengan alamat 0x27 dan ukuran 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inisialisasi RTC DS3231
RTC_DS3231 rtc;

// Pin untuk sensor jarak HC-SR04
const int trigPin = 7;
const int echoPin = 6;
NewPing sonar(trigPin, echoPin, 200); // Object untuk sensor jarak, max 200cm

// Pin untuk servo motor
const int servoPin = 9;
Servo myServo;

void setup() {
  Serial.begin(9600);

  // Inisialisasi LCD
  lcd.begin();
  lcd.backlight();

  // Inisialisasi RTC
  if (!rtc.begin()) {
    lcd.print("RTC tidak ditemukan");
    while (1);
  }

  if (rtc.lostPower()) {
    lcd.print("RTC reset, atur waktu!");
  }

  // Inisialisasi pin untuk sensor jarak dan servo
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);
}

void loop() {
  // Baca waktu dari RTC
  DateTime now = rtc.now();

  // Tampilkan waktu pada LCD
  lcd.setCursor(0, 0);
  lcd.print("Jam: ");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());

  // Baca jarak dari sensor ultrasonik
  int distance = sonar.ping_cm();

  // Tampilkan status pakan pada LCD berdasarkan jarak
  lcd.setCursor(0, 1);
  if (distance == 0 || distance > 200) {
    lcd.print("Pakan: Tidak Ada");
  } else if (distance <= 10) {
    lcd.print("Pakan: Hampir Habis");
  } else {
    lcd.print("Pakan: Tersedia");
  }

  // Cek waktu untuk memberi makan ayam (misalnya setiap pukul 08:00)
  if (now.hour() == 8 && now.minute() == 0 && now.second() == 0) {
    // Buka katup pakan ayam dengan servo
    openFeeder();
  }

  // Delay sebelum pembacaan berikutnya
  delay(1000);
}

void openFeeder() {
  myServo.write(90); // Posisi servo untuk membuka katup pakan
  delay(4000); // Servo membuka selama 4 detik
  myServo.write(0); // Tutup kembali katup setelah 4 detik
}
