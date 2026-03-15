#include "DHT.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float temperature;
float humidity;
int gasValue;
int lux;

WiFiClientSecure espClient;
PubSubClient client(espClient);



const char* mqtt_server = "your-broker-url";
const int mqtt_port = 8883;

const char* mqtt_user = "your-username";
const char* mqtt_pass = "your-password";

unsigned long lastPublish = 0;
const unsigned long publishInterval = 5000;

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");

    if (client.connect("ESP32_Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 sec");
      delay(3000);
    }
  }
}
 
 
 
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

 
 float tmpSTOP1 = 1.9;
 float tmpSTOP2 = 4.1;
 float humidSTOP1 = 90;
 float humidSTOP2 = 95;
 float luxSTOP=4000;
 float gasSTOP = 3700;

enum SystemMode {
  NORMAL,
  EMERGENCY
};
SystemMode systemMode;


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

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin("Wokwi-GUEST", "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println(" Connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
}





void startVentilation(){
  Serial.println("Запущена вентиляция");
}
void startCooling(){
  Serial.println("Запущено охлаждение");
}
void startHeating(){
  Serial.println("Запущено обогрев");
}
void startHumidifier(){
Serial.println("Запущено увлажнение");
}
void startDehumidifier(){
  Serial.println("Запущено осушение");
}

void updateStates() {
  checkTemp();
  checkHumid();
  checkGas();
  checkLux();
  updateMode();
}

void publishData() {

  String payload = "{";
  payload += "\"temperature\":" + String(temperature) + ",";
  payload += "\"humidity\":" + String(humidity) + ",";
  payload += "\"gas\":" + String(gasValue) + ",";
  payload += "\"lux\":" + String(lux) + ",";
  payload += "\"mode\":\"";
  payload += (systemMode == EMERGENCY ? "EMERGENCY" : "NORMAL");
  payload += "\"}";

  client.publish("potato/telemetry", payload.c_str());
Serial.println("MQTT data published");
}



void controlLogic(){
if (systemMode == EMERGENCY) {
    Serial.println("EMERGENCY MODE");
    startVentilation();
  } 
  else if (systemMode == NORMAL) {
    Serial.println("NORMAL MODE");
  }
  if (tempstate == TEMP_HIGH){
    Serial.println("Высокая температура");
    startCooling();
  }else if (tempstate == TEMP_LOW){
    Serial.println("Низкая температура");
    startHeating();
  }else {
    Serial.println("Температура в норме");
  }

  if (humidstate == HUMID_LOW) {
    Serial.println("Низкая влажность");
    startHumidifier();
  }else if (humidstate == HUMID_HIGH){
    Serial.println("Высокая влажность");
    startDehumidifier();
  }else{
    Serial.println("Влажность в норме");
  }
  
  if (luxstate == LUX_CRITICAL){
    Serial.println("СИГНАЛИЗЭЙШН");
  }else {
    Serial.println("Яркость в норме");
  }
}




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
  Serial.print("Connecting to WiFi");
  WiFi.begin("Wokwi-GUEST", "" );
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  
   espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
}





  
void loop() {
   readSensors();

  checkGas();
  checkTemp();
  checkHumid();
  checkLux();

  reconnectMQTT();
  publishData();
  delay(1000);



  if (millis() - lastPublish >= publishInterval) {

    lastPublish = millis();
  }
}




  





