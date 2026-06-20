#include <Arduino.h>
#include <RTClib.h>
#include "Menu.h"

// Estas variáveis foram definidas no .ino
extern RTC_DS3231 rtc;
extern char daysOfTheWeek[7][15];

void Menu::mostrarMenu() {

  Serial.println();
  Serial.println("========== MENU ==========");
  Serial.println("1. Mostrar hora");
  Serial.println("2. Mostrar data");
  Serial.println("3. Ajustar hora");
  Serial.println("4. Ajustar data");
  Serial.println("==========================");
}

void Menu::execOpcao(int option) {

  DateTime now = rtc.now();

  switch (option) {

    case 1:
      mostrarHora();
      break;

    case 2:

      Serial.print("Data: ");

      Serial.print(now.day(), DEC);
      Serial.print('/');

      Serial.print(now.month(), DEC);
      Serial.print('/');

      Serial.print(now.year(), DEC);

      Serial.print(" (");

      Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);

      Serial.println(")");

      break;

    case 3:
      ajustarHora();
      break;

    case 4:
      ajustarData();
      break;

    default:

      Serial.println("Opcao invalida.");

      break;
  }
}

void Menu::mostrarHora(){  //case 1
  DateTime agora = rtc.now();

  Serial.print("Hora gravada: ");

  if (agora.hour() < 10) Serial.print('0');
  Serial.print(agora.hour());

  Serial.print(':');

  if (agora.minute() < 10) Serial.print('0');
  Serial.print(agora.minute());

  Serial.print(':');

  if (agora.second() < 10) Serial.print('0');
  Serial.println(agora.second());
}

int Menu::lerInteiro(const char* mensagem){
  Serial.println(mensagem);

  while(!Serial.available()){}

  int valor = Serial.parseInt();

  while(Serial.available()){
    Serial.read();
  }

  return valor;
}

void Menu::ajustarData(){
  while(!Serial){}

  Serial.println();
  Serial.println("===== SISTEMAS RTC =====");

  if(!rtc.begin()){
    Serial.println("Nao foi possivel encontrar o RTC.");
    while(1);
  }

  int novoAno;
  int novoMes;
  int novoDia;

  int mesComum[7] = {1, 3, 5, 7, 8, 10, 12};
  int mesComercial[4] = {4, 6, 9, 11};
  int fevereiro = 2;

  Serial.println();
  Serial.println("===== AJUSTE DE DATA =====");

  novoAno = lerInteiro("Digite o ano:");
  novoMes = lerInteiro("Digite o numero do mes:");
  novoDia = lerInteiro("Digite o numero do dia:");

  if(novoAno < 1960 || novoAno > 2026){
    Serial.println("Valores inválidos.");
  } else if((novoAno % 4 != 0 && novoMes == fevereiro) && (novoDia < 1 || novoDia > 28)){
    Serial.println("Valores inválidos.");
  }

  for(int i = 0; i < 4; i++){
    if(novoMes == mesComercial[i] && (novoDia < 1 || novoDia > 30)){
      Serial.println("Valores inválidos.");
    }
  }

  for(int i = 0; i < 7; i++){
    if(novoMes == mesComum[i] && (novoDia < 1 || novoDia > 31)){
      Serial.println("Valores inválidos.");
    }
  }

  DateTime agora = rtc.now();

  rtc.adjust(DateTime(
    novoAno,
    novoMes,
    novoDia,
    agora.hour(),
    agora.minute(),
    agora.second()
  ));

  Serial.println();
  Serial.println("RTC ajustado com sucesso!");
}

void Menu::ajustarHora(){  //case 3
  while (!Serial) {}

  Serial.println();
  Serial.println("===== SISTEMA RTC =====");

  if (!rtc.begin()) {
    Serial.println("Nao foi possivel encontrar o RTC.");
    while (1);
  }

  int novaHora;
  int novoMin;
  int novoSeg;

  Serial.println();
  Serial.println("===== AJUSTE DE HORA =====");

  novaHora = lerInteiro("Digite a hora (0-23):");
  novoMin  = lerInteiro("Digite os minutos (0-59):");
  novoSeg  = lerInteiro("Digite os segundos (0-59):");

  if (novaHora < 0 || novaHora > 23 ||
      novoMin  < 0 || novoMin  > 59 ||
      novoSeg  < 0 || novoSeg  > 59) {

    Serial.println("Valores invalidos.");
    return;
  }

  DateTime agora = rtc.now();

  rtc.adjust(DateTime(
    agora.year(),
    agora.month(),
    agora.day(),
    novaHora,
    novoMin,
    novoSeg
  ));

  Serial.println();
  Serial.println("RTC ajustado com sucesso!");
}