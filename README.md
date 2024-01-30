# LoRa-emergency-button
emergency button using LoRa to communicate between each buttons and the gateway

## How does it work?
![block Diagram](/images/lora-emergency-button.jpg)
there are some emergency buttons placed in each room, the emergency button consists of ESP8266, LoRa-02 sx1278, LED, and the button. everytime the button is pressed, it will send signal through LoRa Frequency to the gateway.
there are 2 different gateway, one is responsible to turn on the buzzer and show which button is pressed in LCD I2C. and another gateway is responsible for telegram notification to inform the someone outside the locations.

## Parts needed
### Parts for Emergency Button
  - ESP8266
  - LoRa-02 SX1278
  - LED
  - Switch Button (not pushbutton or self-reset button)
    
![LoRa Emergency Button](/images/emerge-button-1.png)

### Parts for Buzzer
  - ESP8266
  - LoRa-02 SX1278
  - Relay 5V
  - 12v Buzzer
  - LCD I2C 16x2
    
![LoRa Warning Buzzer](/images/emerge-button-3.png)

### Parts for Internet Gateway
  - ESP8266
  - LoRa-02 SX1278

![LoRa Telegram Gateway](/images/emerge-button-2.png)

## Documentation
![Lora Internet Gateway](/images/LoRa-gateway.jpg)
![10 LoRa Emergency Button](/images/LoRa-node.jpg)
![LoRa Emergency Button with Case](/images/LoRa-node-cover.jpg)
## Credits
  - Mr. Untung Suprihadi
  - Kevin Setya Nugraha (me)
  - Arizky Rahman
  - All of the Arduino Community
  - All of Internet Users
