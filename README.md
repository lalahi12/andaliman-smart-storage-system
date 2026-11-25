\# Andaliman Smart Storage System



\## Project Overview



A microcontroller-based smart storage prototype designed to monitor and control temperature and humidity during the post-harvest storage of Andaliman (\*Zanthoxylum acanthopodium\*).



The system uses an ESP32 microcontroller to collect environmental data and control actuators automatically based on programmed conditions.



\## Project Objectives



\- Monitor storage temperature and humidity.

\- Control storage environmental conditions automatically.

\- Display sensor readings through a local display.

\- Help maintain more stable post-harvest storage conditions for Andaliman.



\## Hardware Components



\- ESP32 Microcontroller

\- DS18B20 Temperature Sensor

\- SHT31 Temperature and Humidity Sensor

\- Peltier TEC1-12706

\- DC Fans

\- Relay Module

\- LCD/OLED Display



\## System Features



\- Real-time temperature monitoring.

\- Real-time humidity monitoring.

\- Automatic actuator control based on programmed thresholds.

\- Local sensor data display.

\- Temperature and humidity testing.



\## Technologies



\- C/C++

\- Arduino IDE

\- ESP32

\- Embedded Systems

\- Sensor Integration

\- Microcontroller-Based Automation



\## Project Results



Based on the project presentation:



\- DS18B20 average measurement error: approximately 0.2°C.

\- SHT31 average humidity error: approximately 2% RH.

\- LCD readings were consistent with sensor measurements.

\- Automatic actuator control operated according to programmed thresholds.

\- The cooling system reduced storage temperature to approximately 20°C.



Further optimization was identified as necessary to reach the target temperature range of 15–18°C.



\## Project Type



Academic Team Project



\*\*Institution:\*\* Institut Teknologi Del  

\*\*Program:\*\* D-III Computer Technology



\## Repository Structure



```text

andaliman-smart-storage-system/

├── README.md

└── source-code/

&#x20;   └── andaliman\_smart\_storage.ino

```



\## Disclaimer



This repository documents an academic prototype project. Some results and performance values are based on the team's project testing and presentation.



