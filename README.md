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

---

## Planned Features

- FreeRTOS implementation
- actuator control
- notification system
- automatic climate control
- cloud monitoring
- physical device prototype

---

## Simulation

The project is currently tested using:

Wokwi ESP32 Simulator

---

## Project Status

The project is still under development.

Latest updates:

- MQTT telemetry implemented
- Node-RED integration added
- InfluxDB data storage added
- Grafana visualization added



