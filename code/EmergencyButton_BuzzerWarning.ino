//-----------------------------------------------------------------------------------
//Inisialisasi LCD i2c
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//-----------------------------------------------------------------------------------
#include <LoRa.h>
#define ss 15
#define rst 0
#define dio0 16
//#define buzzer D0
bool buzzState;
bool buzzSound;
#define buzzer2 D4
byte msgCount = 0;

unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
const long interval = 1000;
const long interval2 = 1000;
void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  lcd.backlight();
  lcd.begin();

  Serial.println("LoRa Duplex - Set sync word");
  //  pinMode(buzzer, OUTPUT);
  pinMode(buzzer2, OUTPUT);

  LoRa.setPins(ss, rst, dio0);  // set CS, reset, IRQ pin
  while (!LoRa.begin(433E6)) {  // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
  }
  Serial.println("LoRa init succeeded.");
  LoRa.setSyncWord(0xF3);
}

void loop() {
  currentMillis = millis();
  lcd.setCursor(0, 0);
  lcd.print(" WBP DARURAT ");
  onReceive(LoRa.parsePacket());
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();    // start packet
  LoRa.print(outgoing);  // add payload
  LoRa.endPacket();      // finish packet and send it
  msgCount++;            // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;
  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  Serial.println("Message: " + incoming);

  if (incoming == "0101tb1") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("0101tb1");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "0202tb2") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("0202tb2");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "0303tb3") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("0303tb3");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "0404tb4") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("0404tb4");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "0505tb5") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("0505tb5");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "0606tb6") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("0606tb6");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "0707tb7") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("0707tb7");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "0808tb8") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("0808tb8");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "0909tb9") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("0909tb9");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "1010tb10") {
    digitalWrite(buzzer2, HIGH);
    sendMessage("1010tb10");
    lcd.setCursor(0, 1);
    lcd.print("    UB 74    ");
  } else if (incoming == "1alarm") {
    digitalWrite(buzzer2, HIGH);
  } else if (incoming == "0alarm") {
    digitalWrite(buzzer2, LOW);
  }
}
