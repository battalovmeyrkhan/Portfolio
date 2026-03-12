#IoT Environmental Monitoring System (ESP32)

This project is my first experience working with the ESP32 microcontroller. The idea for the project appeared after analyzing problems in the agricultural industry related to food storage.
Several key issues were identified:
Difficulty maintaining proper storage standards and environmental conditions.
Lack of fully automated monitoring systems for storage facilities.
Loss of agricultural products due to spoilage and disease.
As a solution, an automated embedded monitoring and control system was proposed for potato storage facilities, since potatoes are one of the most widely consumed agricultural products.
The project is designed as a prototype IoT system for real-world storage monitoring and environmental control.

Sensors:                                
- DHT22 (temperature & humidity)
- MQ gas sensor
- Photoresistor (light level)

Controller:
- ESP32

Communication:
- WiFi
- MQTT (HiveMQ Cloud)


Technologies Used

- C++
- ESP32
- Arduino Framework
- MQTT
- WiFi
- HiveMQ Cloud
- Wokwi simulation

- System Architecture

Sensors
  ↓
ESP32 Controller
  ↓
Decision Logic
  ↓
Control Actions
  ↓
MQTT Telemetry
  ↓
Cloud Monitoring



- Project Status

Current features:
✔ sensor monitoring  
✔ priority-based system logic  
✔ WiFi connectivity  
✔ MQTT telemetry  

Planned features:
- RTOS implementation
- cloud dashboard
- data logging
- alert notifications

Logic: Priority-based environmental monitoring Gas → Temperature → Humidity → Light



Проект рассматривается как прототип IoT-системы для реального рынка.

This project is still under development.

update: Added telemetry, WiFi connectivity, and MQTT communication. Sensor states are transmitted to a cloud console via MQTT.


<img width="892" height="610" alt="image" src="https://github.com/user-attachments/assets/62b5eddf-ee85-452b-8849-79ab43ae8fde" />


<img width="1009" height="912" alt="image" src="https://github.com/user-attachments/assets/30bd48f2-a568-423d-a96f-aef05e774fe9" />

<img width="806" height="277" alt="image" src="https://github.com/user-attachments/assets/5822982d-bc84-4538-bf9b-b93598ae6fe6" />





