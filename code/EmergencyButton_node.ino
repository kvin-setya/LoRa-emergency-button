#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 0
#define dio0 4

#define emrgBtn D4
#define ledNotify D0
byte triggerState;
bool state, blinkLed;
bool sendEmc = false;
bool sendSft = false;
unsigned long previousMillis = 0;
unsigned long currentMillis;
const long interval = 500;

int counter = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);

  //replace the LoRa.begin(---E-) argument with your location's frequency
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  Serial.println("ROOM 1 DEVICES");  // ROOM 1 Emergency Btton
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  pinMode(emrgBtn, INPUT_PULLUP);
  pinMode(ledNotify, OUTPUT);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  currentMillis = millis();
  blinkingLed();
  if (sendEmc == false) {
    sendMessage("0101tb1"); // it means, it is room 1, change it as you need
    Serial.println("Pesan Darurat Terkirim");
    sendEmc = true;
  } // send emergency signal once after the devices is turned on
  digitalWrite(ledNotify, state);
  //  delay(200);
}

void blinkingLed() {
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    state = !state;
  }
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();
  LoRa.print(outgoing);
  LoRa.endPacket();
  //  Serial.println("pesan berhasil terkirim");
}
