// настройка датчика
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
// Переменные для хранения датчиков
float temperature;
float humidity;
int gasValue;
int lux;

// Чтение датчиков
 void readSensors() {
 temperature = dht.readTemperature();
humidity = dht.readHumidity();
gasValue = analogRead(34);
int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(36);
  }
  lux = sum / 10;
 }

 // Пороговые значения
 float tmpSTOP1 = 1.9;
 float tmpSTOP2 = 4.1;
 float humidSTOP1 = 90;
 float humidSTOP2 = 95;
 float luxSTOP=10;
 float gasSTOP = 1500;
// Состояние систем
enum SystemMode {
  NORMAL,
  EMERGENCY
};
SystemMode systemMode;

// Варианты, для легкого определения состояния, которые выдаются датчиками
enum Gasstates {
GAS_OK,
GAS_CRITICAL
};
Gasstates gasstate;


enum Tempstates {
TEMP_LOW,
TEMP_HIGH,
TEMP_OK,
};
Tempstates tempstate;

enum Humidstates {
HUMID_LOW,
HUMID_HIGH,
HUMID_OK
};
Humidstates humidstate;

enum Luxstates {
LUX_CRITICAL,
LUX_OK
};
Luxstates luxstate;

// Обновление режима системы
void updateMode () {
  if (gasstate == GAS_CRITICAL) {
 systemMode = EMERGENCY;
  }else {
    systemMode = NORMAL;
  }
}

void checkGas() {
if (gasValue >= gasSTOP) {
  gasstate = GAS_CRITICAL;
} else {
  gasstate = GAS_OK;
}
}

void checkTemp () {
if (temperature <= tmpSTOP1){
tempstate = TEMP_LOW;
} else if (temperature >= tmpSTOP2){
tempstate = TEMP_HIGH;
}else {
  tempstate = TEMP_OK;
}
}

void checkHumid () {
  if (humidity < humidSTOP1){
 humidstate = HUMID_LOW;
  } else if (humidity > humidSTOP2){
 humidstate = HUMID_HIGH;
  } else {
    humidstate = HUMID_OK;
  }
}

void checkLux () {
if (lux > luxSTOP){
  luxstate = LUX_CRITICAL;
} else {
  luxstate = LUX_OK;
}

}
// Логика системы и оутпут
void controlLogic(){
if (systemMode == EMERGENCY) {
    Serial.println("EMERGENCY MODE");
    Serial.println("Включается выдув воздуха");
    Serial.println("Включается подача свежего воздуха");
  } 
  else if (systemMode == NORMAL) {
    Serial.println("NORMAL MODE");
  }
  if (tempstate == TEMP_HIGH){
    Serial.println("Высокая температура");
    Serial.println("Включается кондиционер");
  }else if (tempstate == TEMP_LOW){
    Serial.println("Низкая температура");
    Serial.println("Включается обогрев");
  }else {
    Serial.println("Температура в норме");
  }

  if (humidstate == HUMID_LOW) {
    Serial.println("Низкая влажность");
    Serial.println("Включачется увлажнитель");
  }else if (humidstate == HUMID_HIGH){
    Serial.println("Высокая влажность");
    Serial.println("Включается осушение");
  }else{
    Serial.println("Влажность в норме");
  }
  
  if (luxstate == LUX_CRITICAL){
    Serial.println("СИГНАЛИЗЭЙШН");
  }else {
    Serial.println("Яркость в норме);
  }
}

// Для проверки работоспособности датчиков
void printTempState() {

  if (tempstate == TEMP_LOW) {
    Serial.println("TEMP LOW");
  }

  if (tempstate == TEMP_HIGH) {
    Serial.println("TEMP HIGH");
  }

  if (tempstate == TEMP_OK) {
    Serial.println("TEMP OK");
  }
}


void setup() {
  Serial.begin(115200);
  dht.begin();
}



void loop() {
  readSensors();

  checkGas();
  checkTemp();
  checkHumid();
  checkLux();
 
 // updateMode ();
  //controlLogic();
Serial.print("GAS: ");
Serial.println(gasValue);
Serial.print("LUX: ");
Serial.println(lux);
delay(1000);

}



