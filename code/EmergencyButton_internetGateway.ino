/*
  LIBRARY
  1.  UniversalTelegramBot ver. 1.3.0
  2.  ArduinoJSON ver. 6.15.2 by benoit b.
  3.  Blynk ver. 1.3.2
  4.  LoRa latest version
*/

#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>  // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>
#define BOTtoken "6984806604:AAHyPx7JZbDbxLh3AxXU5_EJsS7g5COphGM"
#define idGroup "-4018937484"
#define idChannel "-1001980273176"

// #define BOTtoken "6822962941:AAEsQx8T7wfA3_1vZ7k7_VFP8DF5fzRjbKE"
// #define idGroup "-1002028990824"
// #define idChannel "-1002008317724"

#ifdef ESP8266
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

#define BLYNK_PRINT Serial
// #define BLYNK_TEMPLATE_ID "TMPL6uEwmfZxX"
// #define BLYNK_TEMPLATE_NAME "SIP DARIS"
// #define BLYNK_AUTH_TOKEN "d2DIjxZ1152ImsztJQDtZNNZ50XHlgV0"

#define BLYNK_TEMPLATE_ID "TMPL6rV-NqNCr"
#define BLYNK_TEMPLATE_NAME "TEstER"
#define BLYNK_AUTH_TOKEN "ZaKnJQiMBvVZuAkzTEYEwvoQjEBircTA"
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SIP_DARIS";
char password[] = "SIPDARIS2023";
// char ssid[] = "JGUMEDIA";
// char password[] = "MEDIAJGU";

#include <SPI.h>
#include <LoRa.h>
#define ss 5
#define rst 0
#define dio0 4
#define relayBuzz D0

unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
const long interval = 86401000;
const long interval2 = 1000;

bool actionTelegram;
byte messageSent = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  pinMode(relayBuzz, OUTPUT);
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  Serial.println("LoRa init succeeded.");
  LoRa.setSyncWord(0xF3);
  // lora init ends

  Serial.println("Memulai Bot Telegram..");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  //  myBot.wifiConnect(ssid, password);
#ifdef ESP8266
  configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
  client.setTrustAnchors(&cert);     // Add root certificate for api.telegram.org
#endif
  Blynk.begin(auth, ssid, password);
#ifdef ESP32
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org
#endif
  bot.sendMessage(idGroup, "System is Ready", "");
  digitalWrite(LED_BUILTIN, HIGH);
}

BLYNK_WRITE(V2) {  // GET DATA
  int pinValue = param.asInt();
  digitalWrite(relayBuzz, pinValue);
  //  Serial.println(pinValue);
  // if (pinValue == 1) {
  //   sendMessage("1alarm");
  // } else {
  //   sendMessage("0alarm");
  // }
}

void handleNewMessages(int numNewMessages) {
  // Serial.println("handleNewMessages");
  // Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    // Chat id of the requester
    // String chat_id = String(bot.messages[i].chat_id);
    // if (chat_id != CHAT_ID) {
    //   bot.sendMessage(chat_id, "Unauthorized user", "");
    //   continue;
    // }

    // Print the received message
    String text = bot.messages[i].text;
    // Serial.println(text);

    // String from_name = bot.messages[i].from_name;

    if (text == "/alarm_off") {
      bot.sendMessage(idGroup, "OK, Alarm dimatikan!", "");
      digitalWrite(relayBuzz, LOW);
      Blynk.virtualWrite(V2, 1);
    }

    if (text == "/alarm_on") {
      bot.sendMessage(idGroup, "OK, Alarm dinyalakan!", "");
      digitalWrite(relayBuzz, HIGH);
      Blynk.virtualWrite(V2, 0);
    }

    // if (text == "/state") {
    //   if (digitalRead(ledPin)) {
    //     bot.sendMessage(chat_id, "LED is ON", "");
    //   } else {
    //     bot.sendMessage(chat_id, "LED is OFF", "");
    //   }
    // }
  }
}

void loop() {
  currentMillis = millis();

  if (currentMillis > previousMillis2 + interval2) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      // Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    previousMillis2 = currentMillis;
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    bot.sendMessage(idGroup, "System Check \nStatus : Standby OK \nUp Time : " + String(currentMillis / 3600000) + " Hour(s)", "");
  }

  if (messageSent == 1) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#01", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 1");
    Blynk.virtualWrite(V4, 1);
    sendMessage("ok1");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  } else if (messageSent == 2) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#02", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 2");
    Blynk.virtualWrite(V5, 1);
    sendMessage("ok2");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  } else if (messageSent == 3) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#03", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 3");
    Blynk.virtualWrite(V6, 1);
    sendMessage("ok3");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  } else if (messageSent == 4) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#04", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 4");
    Blynk.virtualWrite(V7, 1);
    sendMessage("ok4");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  } else if (messageSent == 5) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#05", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 5");
    Blynk.virtualWrite(V8, 1);
    sendMessage("ok5");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  } else if (messageSent == 6) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#06", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 6");
    Blynk.virtualWrite(V9, 1);
    sendMessage("ok6");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  } else if (messageSent == 7) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#07", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 7");
    Blynk.virtualWrite(V10, 1);
    sendMessage("ok7");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  } else if (messageSent == 8) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#08", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 8");
    Blynk.virtualWrite(V11, 1);
    sendMessage("ok8");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  } else if (messageSent == 9) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#09", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 9");
    Blynk.virtualWrite(V12, 1);
    sendMessage("ok9");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  } else if (messageSent == 10) {
    //    bot.sendMessage(idChannel, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis", "");
    bot.sendMessage(idGroup, "ALARM EMERGENCY \nKAMAR : UB 74 \nWBP : Agus Karsono Dawoed \nStatus : Butuh Pertolongan Medis \n#10", "");
    Blynk.virtualWrite(V2, 1);
    Blynk.virtualWrite(V3, "Ruang 10");
    Blynk.virtualWrite(V13, 1);
    sendMessage("ok10");
    digitalWrite(relayBuzz, HIGH);
    messageSent = 0;
  }

  onReceive(LoRa.parsePacket());
  Blynk.run();
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();    // start packet
  LoRa.print(outgoing);  // add payload
  LoRa.endPacket();      // finish packet and send it
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;
  String incoming = "";
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  Serial.println("Message: " + incoming);

  if (incoming == "0101tb1") {
    messageSent = 1;
  } else if (incoming == "0202tb2") {
    messageSent = 2;
  } else if (incoming == "0303tb3") {
    messageSent = 3;
  } else if (incoming == "0404tb4") {
    messageSent = 4;
  } else if (incoming == "0505tb5") {
    messageSent = 5;
  } else if (incoming == "0606tb6") {
    messageSent = 6;
  } else if (incoming == "0707tb7") {
    messageSent = 7;
  } else if (incoming == "0808tb8") {
    messageSent = 8;
  } else if (incoming == "0909tb9") {
    messageSent = 9;
  } else if (incoming == "1010tb10") {
    messageSent = 10;
  }
}
