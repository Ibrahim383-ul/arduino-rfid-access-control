/**
 * @file       main.cpp
 * @brief      Smarte RFID-Zutrittskontrolle (Türscanner) mit Servo & Signalisierung
 * @author     Ibrahim AL SAEED
 * @date       2026-01-03
 * @version    1.1
 * @license    MIT
 * 
 * Hardware:   Arduino Nano (ATmega328P), RFID-RC522 (SPI), SG90 Servo, Status-LEDs, Piezo
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// ================= Pin-Definitionen =================
constexpr uint8_t PIN_SS       = 10;   // SPI Slave Select (SDA)
constexpr uint8_t PIN_RST      = 9;    // RC522 Reset
constexpr uint8_t PIN_SERVO    = 7;    // PWM-Steuersignal für Servomotor
constexpr uint8_t PIN_LED_RED  = 6;    // Rote Status-LED (Zugriff verweigert)
constexpr uint8_t PIN_PIEZO    = 6;    // Piezo-Summer (Warnton)
constexpr uint8_t PIN_LED_GRN  = 5;    // Grüne Status-LED (Zugriff erlaubt)

// ================= Globale Instanzen =================
MFRC522 rfid(PIN_SS, PIN_RST);
Servo doorServo;

// Autorisierte RFID-Transponder-UID (z. B. Mifare Classic)
const byte ALLOWED_UID[4] = {0x33, 0xDF, 0x6D, 0xE2};

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  doorServo.attach(PIN_SERVO);
  doorServo.write(0); // Tür verriegelt (0 Grad)

  pinMode(PIN_LED_GRN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  Serial.println(F("========================================"));
  Serial.println(F(" Smart RFID Access Control bereit...   "));
  Serial.println(F("========================================"));
}

void loop()
{
  // Warten, bis ein RFID-Tag vor das Lesegerät gehalten wird
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print(F("Karte erkannt. UID: "));
  bool accessGranted = true;

  // Eingelesene UID mit autorisierter UID vergleichen
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    if (rfid.uid.uidByte[i] < 0x10) Serial.print(F("0"));
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(F(" "));

    if (rfid.uid.uidByte[i] != ALLOWED_UID[i])
    {
      accessGranted = false;
    }
  }
  Serial.println();

  // Zutrittsauswertung
  if (accessGranted)
  {
    Serial.println(F(">> ZUGRIFF ERLAUBT: Tür wird entriegelt."));
    digitalWrite(PIN_LED_GRN, HIGH);
    digitalWrite(PIN_LED_RED, LOW);
    doorServo.write(90); // Schloss öffnen (90 Grad)
  }
  else
  {
    Serial.println(F(">> ZUGRIFF VERWEIGERT: Ungültige UID!"));
    digitalWrite(PIN_LED_GRN, LOW);
    digitalWrite(PIN_LED_RED, HIGH);
    tone(PIN_PIEZO, 400, 200); // 400 Hz Alarmton für 200 ms
  }

  // Tag in den Ruhezustand versetzen
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  // Schließverzögerung: Tür bleibt 1.5 Sekunden offen
  delay(1500);

  // Status zurücksetzen & Tür wieder verriegeln
  doorServo.write(0);
  digitalWrite(PIN_LED_GRN, LOW);
  digitalWrite(PIN_LED_RED, LOW);
}
