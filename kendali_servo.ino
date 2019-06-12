#include <Wire.h>
#include "RTClib.h"
#include <Servo.h>

Servo myservo;
RTC_DS3231 rtc;
/*
 * konfigurasi waktu mulai
*/
int menit = 39;
int jam = 23;
/***************************/
int srv = 5; //jumlah servo on
int a;

char t[20];
int waktusekarang;
int waktumulai;
void setup() {
  Serial.begin(9600);
  rtc.begin();
  myservo.attach(9);
  myservo.write(0);

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  tampilWaktu();
  kendaliServo();

}


void tampilWaktu() {
  DateTime now = rtc.now();

  sprintf(t, "%02d/%02d/%02d    %02d:%02d:%02d", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());
  Serial.println(t);
  delay(1000);
}

void servo() {
  for (a = 1; a <= srv; a++) {
    Serial.println("Servo ON!!");
    myservo.write(90);
    delay(1000);
    myservo.write(0);
    delay(1000);
  }
}


void kendaliServo() {
  DateTime now = rtc.now();

  waktusekarang = ((now.hour() * 3600) + (now.minute() * 60) + now.second());
  waktumulai = ( (jam * 3600) + (menit * 60));

  if (waktusekarang >= waktumulai) {
    if (waktusekarang <= waktumulai + 10) {
      servo();
      delay(10000);   
    }
  }

}
