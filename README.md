# 🚪 Smart RFID Access Control System (Türscanner)

![PlatformIO](https://img.shields.io/badge/PlatformIO-Compatible-orange?style=for-the-badge&logo=platformio)
![Arduino](https://img.shields.io/badge/Arduino-C%2B%2B-00979D?style=for-the-badge&logo=arduino)
![Hardware](https://img.shields.io/badge/Hardware-MFRC522%20%7C%20Servo-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

Eine automatisierte Zutrittskontrolle auf Basis eines **Arduino** und des **RFID-RC522-Moduls**. Das System liest RFID-Transponder (Karten/Chips) über den SPI-Bus aus, validiert die hinterlegten UIDs und steuert bei Berechtigung einen Servomotor als elektronische Türverriegelung an.

---

## 📺 Demonstration & Video-Erklärung

Das Projekt inklusive Schaltungsaufbau und Funktionsweise im Video:

[![Video ansehen](https://img.shields.io/badge/YouTube-Video_Erkl%C3%A4rung-red?style=for-the-badge&logo=youtube)](https://youtu.be/aIOdKdzlT2U)

---

## ⚡ Schaltungsaufbau & Pin-Belegung

Das RFID-RC522-Modul kommuniziert über den **SPI-Bus** mit dem Mikrocontroller.

<p align="center">
  <img src="https://github.com/user-attachments/assets/2e914126-824b-46f2-97f9-7b962a260d95" alt="RC522 Pinbelegung Arduino" width="600" />
</p>

### Anschlussbelegung (Arduino ➔ MFRC522)

| RC522 Pin | Signal | Arduino Pin | Beschreibung / Funktion |
| :--- | :--- | :--- | :--- |
| **SDA** | SS (Slave Select) | **D10** | SPI Chip-Select |
| **SCK** | SPI Clock | **D13** | SPI Taktleitung |
| **MOSI** | Master Out Slave In | **D11** | SPI Datenübertragung |
| **MISO** | Master In Slave Out | **D12** | SPI Datenempfang |
| **IRQ** | Interrupt | *nicht belegt* | Optionaler Interrupt |
| **GND** | Masse | **GND** | Gemeinsames Massepotenzial |
| **RST** | Reset | **D9** | Reset-Leitung |
| **3.3V** | Versorgungsspannung | **3.3V** | ⚠️ **Achtung: Nur mit 3.3V versorgen (nicht 5V)!** |

*Hinweis zum Servo:* Das Steuersignal des Servomotors wird an einen PWM-fähigen Digital-Pin angeschlossen (z. B. D3 oder D5), mit 5V Betriebsspannung und gemeinsamer Masse (GND).

---

## 🛠️ Verwendete Hardware & Komponenten

* **Mikrocontroller:** Arduino (Nano / Uno)
* **RFID-Lesegerät:** RC522 (13.56 MHz RFID Reader / Writer)
* **Transponder:** 13.56 MHz Mifare Tags / S50 Karten
* **Aktor:** Micro-Servomotor (z. B. SG90) zur Schlossbetätigung
* **Verkabelung:** Breadboard & Jumper-Kabel

---

## 💻 Software & Bibliotheken

Entwickelt mit **PlatformIO** in C++.

* `<SPI.h>` – Hardware-SPI-Kommunikation
* `<MFRC522.h>` – Ansteuerung des RFID-Transceiver-ICs
* `<Servo.h>` – PWM-Generierung für den Servomotor

---

## 🚀 Setup & Ausführung (PlatformIO)

1. **Voraussetzung:** Installiere [Visual Studio Code](https://code.visualstudio.com/) mit der **PlatformIO IDE Extension**.
2. **Repository klonen:**
   ```bash
   git clone https://github.com/Ibrahim383-ul/arduino-rfid-access-control.git
