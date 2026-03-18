# IoT Environmental Monitoring System (ESP32)

## Project Overview

This project is my first experience working with the ESP32 microcontroller and developing a prototype IoT environmental monitoring system.

The idea for this project came after analyzing problems in the agricultural industry related to food storage, especially potato storage.

Several key issues were identified:

- difficulty maintaining proper storage conditions
- lack of automated monitoring systems
- product losses caused by improper storage conditions

As a solution, an embedded environmental monitoring system was developed to automatically track storage conditions.

This project is considered a prototype IoT solution for real-world applications.

---

## Configuration

Before running the project, replace the placeholder credentials in the code:

- `your-broker-url`
- `your-username`
- `your-password`

---

## Hardware

### Sensors

| Sensor | Purpose |
|------|------|
| DHT22 | Temperature and humidity monitoring |
| MQ Gas Sensor | Gas level monitoring |
| Photoresistor | Light intensity monitoring |

### Controller

ESP32 microcontroller

---

## System Architecture

The system is built using the following IoT telemetry pipeline:

Sensors  
↓  
ESP32  
↓  
MQTT (HiveMQ Cloud)  
↓  
Node-RED  
↓  
InfluxDB  
↓  
Grafana Dashboard  

Pictures in the "images" folder

The system was refactored using FreeRTOS to improve modularity, responsiveness, and scalability.

Instead of a single loop-based structure, the system is now divided into independent concurrent tasks:

- taskSensors → reads sensor data  
- taskControl → processes system states and logic  
- taskNetwork → maintains WiFi and MQTT connection  
- taskPublish → sends telemetry data to MQTT  

Data flow between tasks is implemented using a FreeRTOS Queue:

Sensors Task → Queue → Publish Task  

This approach ensures:

- safe data exchange between tasks  
- better system stability  
- non-blocking execution  
- separation of responsibilities  

---


## Data Pipeline

ESP32 → MQTT → Node-RED → InfluxDB → Grafana (Local)

---

## ESP32

The ESP32 reads data from sensors:

- temperature
- humidity
- gas level
- light intensity

The collected data is then formatted into a message and sent through an MQTT broker.

---

## MQTT

MQTT is used as the telemetry communication protocol between the ESP32 and the data processing system.

Broker: HiveMQ Cloud

MQTT provides:

- lightweight telemetry transmission
- asynchronous messaging
- scalable system architecture

---

## Node-RED

Node-RED is used for:

- receiving MQTT messages
- processing incoming data
- preparing data for the database

Node-RED acts as middleware between MQTT and InfluxDB.

---

## InfluxDB

InfluxDB is used as a time-series database for storing sensor data.

Each message is stored as a timestamped record containing:

- temperature
- humidity
- gas
- light

---

## Grafana

Grafana is used for data visualization.

Dashboards display:

- temperature graphs
- humidity levels
- gas concentration
- light levels

Grafana allows monitoring the system in real time.

---

## System Logic

The system uses a priority-based monitoring model.

Priority order:

Gas → Temperature → Humidity → Light

---

## Current Features

- sensor monitoring  
- priority-based system logic  
- WiFi connectivity  
- MQTT telemetry  
- Node-RED integration  
- data storage in InfluxDB  
- visualization in Grafana  
- FreeRTOS task-based architecture  
- inter-task communication using Queue  

---

## Planned Features

- notification system
- physical device prototype
- digital twin integration  

---

## Simulation

The project is currently tested using:

Wokwi ESP32 Simulator

---

## 🧾 Project Conclusion

This project demonstrates the development of a complete IoT monitoring system based on the ESP32 microcontroller.

During the development process, the system evolved from a simple sensor data collection prototype into a structured and scalable embedded system.

The final Version 1 (V1) includes:

- real-time environmental monitoring (temperature, humidity, gas, light)  
- end-to-end data pipeline (ESP32 → MQTT → Node-RED → InfluxDB → Grafana)  
- implementation of system logic and condition analysis  
- transition from a loop-based design to a FreeRTOS-based architecture  
- separation of system responsibilities into independent tasks  
- safe inter-task communication using Queue  

As a result, the system is no longer just a prototype, but a foundation for a real-world industrial IoT solution.

The project also highlights key engineering concepts:

- embedded systems design  
- asynchronous communication (MQTT)  
- time-series data processing  
- real-time monitoring and visualization  
- RTOS-based system architecture  

This project serves as a strong base for further development, including:

- integration of actuators  
- implementation of predictive maintenance  
- development of a digital twin  
- deployment of a physical prototype  

Overall, this work reflects a transition from basic IoT experimentation to a more structured and production-oriented system design.

---





