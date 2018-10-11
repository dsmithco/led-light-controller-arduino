#include <FastLED.h>
#include <stdio.h>
#include <math.h>

#define NUM_LEDS 76
#define LED_PIN 22
#define COLOR_NUM 3

int COLORS[COLOR_NUM][3] = {
  {255,0,0},
  {0,255,0},
  {0,0,255}
};

#define STEP 50
#define DELAY 1500


CRGB led[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, LED_PIN>(led, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(COLORS[0][0],COLORS[0][1],COLORS[0][2]);  
  }
  FastLED.show();
  delay(DELAY);
}


void setColor(int r, int g, int b) {
  // put your setup code here, to run once:

  for (int i = 0; i < NUM_LEDS; i++) {
    led[i] = CRGB(r,g,b);  
  }

  FastLED.show();
}

void fadeColors(int fromRGB[], int toRGB[]) {
     for ( int i = 1; i < 101; i++ ) {
       int FROM_R = fromRGB[0];
       int FROM_G = fromRGB[1];
       int FROM_B = fromRGB[2];

       int TO_R = toRGB[0];
       int TO_G = toRGB[1];
       int TO_B = toRGB[2];
       
       setColor(FROM_R + (i * (TO_R - FROM_R)/100), FROM_G + (i * (TO_G - FROM_G)/100), FROM_B + (i * (TO_B - FROM_B)/100));
       delay(STEP);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int c = 0; c < COLOR_NUM - 1; c++) {
     fadeColors(COLORS[c], COLORS[c+1]); 
  }
  fadeColors(COLORS[COLOR_NUM - 1], COLORS[0]);
}
