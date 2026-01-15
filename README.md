# stm32f1-hal-cubemx-dht11-huaweicloud

This repository provides a complete STM32F1-based embedded application developed using STM32CubeMX and the STM32 HAL library.  
The project demonstrates temperature and humidity data acquisition from a DHT11 sensor and wireless data transmission to Huawei Cloud using an ESP8266 WiFi module.

This project is intended as a reference design and learning example for STM32 HAL development, sensor interfacing, UART communication, and basic cloud connectivity.

---

## Features

- STM32F1 series microcontroller
- Project generated and configured using STM32CubeMX
- HAL-based peripheral drivers
- DHT11 temperature and humidity sensor interface
- ESP8266 WiFi module using AT commands
- Sensor data upload to Huawei Cloud
- UART debug output
- LED status indication
---

## Hardware Requirements

- MCU: STM32F1 series (e.g. STM32F103C8T6)
- Sensor: DHT11
- WiFi module: ESP8266 (ESP-01S / ESP-12, etc.)
- USB to UART converter (for debugging)
- LEDs and basic passive components
---

## Hardware Connections

| STM32 Peripheral | Module / Function | STM32 Pin |
|----------------|-------------------|-----------|
| USART1 (TX/RX) | USB-to-UART (Debug output) | PA9 / PA10 |
| USART2 (TX/RX) | ESP-01S WiFi module | PA2 / PA3 |
| GPIO           | DHT11 Data        | PA6 |
| GPIO           | Status LED        | PB5 |

> Note: Pin definitions can be modified in STM32CubeMX and `main.h`.

---

## Software Environment

- STM32CubeMX
- STM32 HAL Library
- Keil MDK / STM32CubeIDE
- ARM GCC / ARMCC toolchain

---

## Project Structure

```text
stm32f1-hal-cubemx-dht11-huaweicloud/
├── Core/
│   ├── Inc/
│   │   ├── main.h
│   │   ├── dht11.h
│   │   └── esp8266.h
│   └── Src/
│       ├── main.c
│       ├── dht11.c
│       └── esp8266.c
├── Drivers/
│   └── STM32F1xx_HAL_Driver/
├── LICENSE
├── README.md
└── .gitignore
