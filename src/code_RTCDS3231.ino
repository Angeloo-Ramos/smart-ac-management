#include <Wire.h>
#include <RTClib.h>
#include "Menu.h"

RTC_DS3231 rtc;
Menu menu;

#define led_verde 8
#define led_r 9
#define led_g 10
#define led_b 11

void setup() {
  pinMode(led_verde, OUTPUT);
  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_b, OUTPUT);

  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("Nao foi possivel encontrar o RTC.");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC perdeu energia!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  menu.mostrarMenu();
}

char daysOfTheWeek[7][15] = {
  "Domingo",
  "Segunda-feira",
  "Terca-feira",
  "Quarta-feira",
  "Quinta-feira",
  "Sexta-feira",
  "Sabado"
};

void loop() {
  digitalWrite(led_verde, HIGH);

  if (Serial.available()) {

    int option = Serial.parseInt();

    menu.execOpcao(option);

    Serial.println();
    menu.mostrarMenu();
  }

}