#define FASTLED_INTERRUPT_RETRY_COUNT 1 
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_INTERNAL

#include <FastLED.h>
#include <stdio.h>
#include <math.h>

#define LED_PIN_4 4
#define LED_PIN_3 3
#define LED_PIN_2 2
#define LED_PIN_1 1

// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <ArduinoJson.h>

// #include <EEPROM.h>

// ESP8266WebServer server;

// const char* ssid     = "Smithco";
// const char* password = "Rethink134498!";     

// int wifiStatus;q

const int NUM_LEDS PROGMEM = 75;
const int COLOR_NUM PROGMEM = 3;

int COLORS[COLOR_NUM][3] = {
  {155,50,0},
  {200,160,0},
  {155,40,130}
};

int initDelayTime = 100000;
int fadeDelayTime = 200;

#include <stdio.h> 
#include <string.h> 



CRGB led[NUM_LEDS];

void setColor(int r, int g, int b) {
  // put your setup code here, to run once:

  for (int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(r,g,b);  
  }

  FastLED.show();

}


/** Load WLAN credentials from EEPROM */
// void loadColors() {
//   EEPROM.begin(512);
//   EEPROM.get(0, colors);
//   EEPROM.get(1, delayTime);
//   EEPROM.get(2, COLOR_NUM);
//   char ok[3];
//   EEPROM.get(0+sizeof(colors)+sizeof(delayTime)+sizeof(COLOR_NUM), ok);
//   EEPROM.end();
//   if (String(ok) != String("OK")) {
//     COLOR_NUM = 5;
//     delayTime = 500;
//     colors[0][4] = {127,100,0,50};
//   }
//   Serial.println("Recovered credentials:");
//   Serial.println(ssid);
//   Serial.println(strlen(password)>0?"********":"<no password>");
// }

// /** Store WLAN credentials to EEPROM */
// void saveColors() {
//   EEPROM.begin(512);
//   EEPROM.put(0, colors);
//   char ok[3] = "OK";
//   EEPROM.put(0+sizeof(colors)+sizeof(delayTime)+sizeof(COLOR_NUM), ok);

//   EEPROM.commit();
//   EEPROM.end();
// }


void setup() {
  // EEPROM.begin(512);
  FastLED.addLeds<NEOPIXEL, LED_PIN_1>(led, NUM_LEDS).setCorrection (TypicalLEDStrip);
  FastLED.addLeds<NEOPIXEL, LED_PIN_2>(led, NUM_LEDS).setCorrection (TypicalLEDStrip);
  FastLED.addLeds<NEOPIXEL, LED_PIN_3>(led, NUM_LEDS).setCorrection (TypicalLEDStrip);
  FastLED.addLeds<NEOPIXEL, LED_PIN_4>(led, NUM_LEDS).setCorrection (TypicalLEDStrip);

  setColor(0, 0, 0);
  setColor(0, 0, 0);
  setColor(COLORS[0][0], COLORS[0][1], COLORS[0][2]);
  setColor(COLORS[0][0], COLORS[0][1], COLORS[0][2]);

  delay(initDelayTime);
}


void fadeColors(int fromRGB[], int toRGB[]) {
    for ( int i = 1; i < 101; i++ ) {
      // server.handleClient();
      int FROM_R = fromRGB[0];
      int FROM_G = fromRGB[1];
      int FROM_B = fromRGB[2];

      int TO_R = toRGB[0];
      int TO_G = toRGB[1];
      int TO_B = toRGB[2];
      
      setColor(FROM_R + (i * (TO_R - FROM_R)/100), FROM_G + (i * (TO_G - FROM_G)/100), FROM_B + (i * (TO_B - FROM_B)/100));
      setColor(FROM_R + (i * (TO_R - FROM_R)/100), FROM_G + (i * (TO_G - FROM_G)/100), FROM_B + (i * (TO_B - FROM_B)/100));
      delay(fadeDelayTime);
    }
}

void loop() {

  // put your main code here, to run repeatedly:
  for (int c = 0; c < COLOR_NUM - 1; c++) {
    fadeColors(COLORS[c], COLORS[c+1]); 
    delay(100000);
  }
  fadeColors(COLORS[COLOR_NUM - 1], COLORS[0]);
  delay(100000);
}
