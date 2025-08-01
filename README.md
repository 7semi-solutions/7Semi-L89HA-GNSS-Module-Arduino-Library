# 7Semi-L89HA-GNSS-Module-Arduino-Library

This Arduino library provides support for the **7Semi L89HA GNSS Module** over UART. It allows reading standard NMEA sentences like GGA, RMC, and GSV, enabling you to obtain GPS coordinates, date/time, and satellite data easily from Arduino-compatible boards.

![Arduino](https://img.shields.io/badge/platform-arduino-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Status](https://img.shields.io/badge/status-active-brightgreen.svg)

---

## Hardware Required

- 7Semi L89HA GNSS Module  
- Arduino-compatible board  
- UART connection (HardwareSerial or SoftwareSerial)  

---

## Getting Started
 
  ### 1. Library Installation
 
      - Download or clone the repository.

      - Copy the files `L89HA.cpp` and `L89HA.h` into a folder named `7semi_L89HA` under your Arduino `libraries/` directory.

      - Restart the Arduino IDE.
---

### 2. Wiring

| L89HA Pin | Arduino Pin      |
|-----------|------------------|
| TX        | RX (D10 if using SoftwareSerial) |
| RX        | TX (D11 if using SoftwareSerial) |
| GND       | GND              |
| VCC       | 3.3V or 5V (as per module spec) |
