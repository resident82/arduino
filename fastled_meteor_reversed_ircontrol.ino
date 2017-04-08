//================================================
#include "FastLED.h"
#include <IRremote.h>
#define LED_COUNT 32
#define LED_PIN 3
#define RECV_PIN 11
//================================================

struct CRGB leds[LED_COUNT];
uint8_t hue = 20;
uint8_t hue2 = 20;
uint8_t bright = 30;
int del = 60; // скорость
bool isOn = true;
uint32_t val; // код нажатой кнопки (для обработки залипания)

// meteor values
byte idex = 255;
byte meteorLength = 30;

// dots values
uint8_t count; // Count up to 255 and then reverts to 0
long currentMillis = 0;
long previousMillis = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  // delay(2000);
  LEDS.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
  LEDS.setBrightness(bright);

  Serial.begin(9600);
  irrecv.enableIRIn();
}

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {  meteorShower, fillColor, meteorShowerColored, meteorShower3, meteorShower4, dots, sinelon };
uint8_t gCurrentPatternNumber = 0;

void loop(){
  if ( irrecv.decode( &results ) )
  {
    irControll();
  }
  if ( irrecv.isIdle() )
  {
     gPatterns[gCurrentPatternNumber]();
  }
}

void nextPattern()
{
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void prevPattern()
{
  gCurrentPatternNumber = (gCurrentPatternNumber - 1) % ARRAY_SIZE( gPatterns);
}

void irControll() {
    // Serial.println(results.value, HEX);

    if (results.value != 0xFFFFFFFF) {
      val = results.value;
    }
    
    // вкл/выкл
    if (results.value == 0xF7C03F || results.value == 0xCE1972FD)
    {
      if(isOn == true) {
        bright = 0;
        isOn = false;
        LEDS.setBrightness(bright);
      } else {
        bright = 60;
        isOn = true;
        LEDS.setBrightness(bright);
      }
    }

    // 
    if (results.value == 0xF740BF || results.value == 0xD4DD0381)
    {
      
    }

    // регулировка яркости
    if (val == 0xF700FF || val == 0x8503705D)
    {
      if (bright < 250) bright += 5;
      LEDS.setBrightness(bright);
    }

    if (val == 0xF7807F || val == 0xDEB0C861)
    {
      if (bright >= 10) bright -= 5;
      LEDS.setBrightness(bright);
    }
    if (val == 0xF720DF || val == 0xE85952E1)
    {
      sinelon();
    }

    if (val == 0xF7A05F || val == 0x78CDA4DD)
    {
      
    }

    // регулировка скорости
    if (val == 0xF7C837 || val == 0xB9C07541)
    {
      if (del >= 2) del -= 2;
    }

    if (val == 0xF7E817 || val == 0xA7315F7D)
    {
      if (del < 2000) del += 2;
    }

    // следующий эффект
    if (results.value == 0xF7D02F || results.value == 0xDCC45BE1)
    {
      nextPattern();
    }
    // предыдущий эффект
    if (results.value == 0xF7F00F || results.value == 0x374E8B9D)
    {
      prevPattern();
    }
    
    // смена оттенка
    if (val == 0xF7E01F || val == 0x9BA392C1)
    {
      hue += 5;
    }
    if (val == 0xF7609F || val == 0xA2672345)
    {
      hue2 += 5;
    }


    // выбор одного цвета
    if (val == 0xF720DF || val == 0xE85952E1)
    {
     
    }
    if (val == 0xF7A05F || val == 0x78CDA4DD)
    {
      
    }
    if (val == 0xF7609F || val == 0xA2672345)
    {
      
    }
    irrecv.resume();
}

void meteorShower(){
  memmove8( &leds[0], &leds[1], (LED_COUNT - 1) * 3 );
  idex++;
  if ( idex > meteorLength ) {
    idex = 0;
  }
  
  switch ( idex ) {
  case 0:
    leds[LED_COUNT-1] = CHSV((hue2), 255, 220);
    break;
  case 1:
    leds[LED_COUNT-1] = CHSV((hue - 20), 250, 210); 
    break;
  case 2:
    leds[LED_COUNT-1] = CHSV((hue - 22), 245, 200); 
    break;
  case 3:
    leds[LED_COUNT-1] = CHSV((hue - 23), 235, 190); 
    break;
  case 4:
    leds[LED_COUNT-1] = CHSV((hue - 24), 225, 180); 
    break;
  case 5:
    leds[LED_COUNT-1] = CHSV((hue - 25), 215, 170); 
    break;
  case 6:
    leds[LED_COUNT-1] = CHSV((hue - 26), 205, 160); 
    break;
  case 7:
    leds[LED_COUNT-1] = CHSV((hue - 27), 195, 150); 
    break;
  case 8:
    leds[LED_COUNT-1] = CHSV((hue - 28), 185, 140); 
    break;
  case 9:
    leds[LED_COUNT-1] = CHSV((hue - 29), 175, 130); 
    break;
  case 10:
    leds[LED_COUNT-1] = CHSV((hue - 29), 165, 120); 
    break;
  case 11:
    leds[LED_COUNT-1] = CHSV((hue - 29), 155, 110); 
    break;
  case 12:
    leds[LED_COUNT-1] = CHSV((hue - 29), 145, 100); 
    break;
  case 13:
    leds[LED_COUNT-1] = CHSV((hue - 29), 135, 90); 
    break;
  case 14:
    leds[LED_COUNT-1] = CHSV((hue - 29), 125, 80); 
    break;
  case 15:
    leds[LED_COUNT-1] = CHSV((hue - 29), 115, 70); 
    break;
  case 16:
    leds[LED_COUNT-1] = CHSV((hue - 29), 105, 60); 
    break;
  case 17:
    leds[LED_COUNT-1] = CHSV((hue - 29), 95, 50); 
    break;
  case 18:
    leds[LED_COUNT-1] = CHSV((hue - 29), 85, 40); 
    break;
  case 19:
    leds[LED_COUNT-1] = CHSV((hue - 29), 75, 30); 
    break;
  case 20:
    leds[LED_COUNT-1] = CHSV((hue - 29), 65, 20); 
    break;
  case 21:
    leds[LED_COUNT-1] = CHSV((hue - 29), 55, 10); 
    break;
  default:
    leds[LED_COUNT-1] = CRGB::Black; 
  }

  FastLED.show();
  delay(del);
}

void meteorShower3(){
  memmove8( &leds[0], &leds[1], (LED_COUNT - 1) * 3 );
  idex++;
  if ( idex > meteorLength ) {
    idex = 0;
  }
  
  switch ( idex ) {
  case 0:
    leds[LED_COUNT-1] = CHSV((hue), 255, 210);
    break;
  case 1:
    leds[LED_COUNT-1] = CHSV((hue - 20), 255, 180); 
    break;
  case 2:
    leds[LED_COUNT-1] = CHSV((hue - 40), 255, 110); 
    break;
  case 3:
    leds[LED_COUNT-1] = CHSV((hue - 60), 255, 50); 
    break;

  case 10:
    leds[LED_COUNT-1] = CHSV((hue), 255, 210);
    break;
  case 11:
    leds[LED_COUNT-1] = CHSV((hue - 20), 255, 180); 
    break;
  case 12:
    leds[LED_COUNT-1] = CHSV((hue - 40), 255, 110); 
    break;
  case 13:
    leds[LED_COUNT-1] = CHSV((hue - 60), 255, 50); 
    break;

  case 20:
    leds[LED_COUNT-1] = CHSV((hue), 255, 210);
    break;
  case 21:
    leds[LED_COUNT-1] = CHSV((hue - 20), 255, 180); 
    break;
  case 22:
    leds[LED_COUNT-1] = CHSV((hue - 40), 255, 110); 
    break;
  case 23:
    leds[LED_COUNT-1] = CHSV((hue - 60), 255, 50); 
    break;
  
  default:
    leds[LED_COUNT-1] = CRGB::Black; 
  }

  FastLED.show();
  delay(del);
}

void meteorShower4(){
  memmove8( &leds[0], &leds[1], (LED_COUNT - 1) * 3 );
  idex++;
  if ( idex > meteorLength ) {
    idex = 0;
  }
  
 switch ( idex ) {
  case 0:
    leds[LED_COUNT-1] = CHSV((hue), 255, bright);
    break;
  case 1:
    leds[LED_COUNT-1] = CHSV((hue+10), 255, bright+20); 
    break;
  case 2:
    leds[LED_COUNT-1] = CHSV((hue+20), 255, bright+40); 
    break;

  case 8:
    leds[LED_COUNT-1] = CHSV((hue), 255, bright);
    break;
  case 9:
    leds[LED_COUNT-1] = CHSV((hue+10), 255, bright+20); 
    break;
  case 10:
    leds[LED_COUNT-1] = CHSV((hue+20), 255, bright+40); 
    break;

  case 16:
    leds[LED_COUNT-1] = CHSV((hue), 255, bright);
    break;
  case 17:
    leds[LED_COUNT-1] = CHSV((hue+10), 255, bright+20); 
    break;
  case 18:
    leds[LED_COUNT-1] = CHSV((hue+20), 255, bright+40); 
    break;

  case 23:
    leds[LED_COUNT-1] = CHSV((hue), 255, bright);
    break;
  case 24:
    leds[LED_COUNT-1] = CHSV((hue+10), 255, bright+20); 
    break;
  case 25:
    leds[LED_COUNT-1] = CHSV((hue+20), 255, bright+40); 
    break;
  
  default:
    leds[LED_COUNT-1] = CRGB::Black;
  }

  FastLED.show();
  delay(del);
}


void meteorShowerColored(){
  memmove8( &leds[0], &leds[1], (LED_COUNT - 1) * 3 );
  idex++;
  if ( idex > meteorLength ) {
    idex = 0;
  }
  
  switch ( idex ) {
  case 0:
    leds[LED_COUNT-1] = CHSV((hue), 255, 210);
    break;
  case 1:
    leds[LED_COUNT-1] = CHSV((hue - 8), 255, 210); 
    break;
  case 2:
    leds[LED_COUNT-1] = CHSV((hue - 16), 255, 200); 
    break;
  case 3:
    leds[LED_COUNT-1] = CHSV((hue - 24), 255, 190); 
    break;
  case 4:
    leds[LED_COUNT-1] = CHSV((hue - 33), 255, 180); 
    break;
  case 5:
    leds[LED_COUNT-1] = CHSV((hue - 41), 255, 170); 
    break;
  case 6:
    leds[LED_COUNT-1] = CHSV((hue - 50), 220, 160); 
    break;
  case 7:
    leds[LED_COUNT-1] = CHSV((hue - 58), 210, 150); 
    break;
  case 8:
    leds[LED_COUNT-1] = CHSV((hue - 67), 200, 140); 
    break;
  case 9:
    leds[LED_COUNT-1] = CHSV((hue - 75), 190, 130); 
    break;
  case 10:
    leds[LED_COUNT-1] = CHSV((hue - 84), 180, 120); 
    break;
  case 11:
    leds[LED_COUNT-1] = CHSV((hue - 92), 170, 110); 
    break;
  case 12:
    leds[LED_COUNT-1] = CHSV((hue - 100), 150, 100); 
    break;
  case 13:
    leds[LED_COUNT-1] = CHSV((hue - 108), 130, 90); 
    break;
  case 14:
    leds[LED_COUNT-1] = CHSV((hue - 115), 110, 80); 
    break;
  case 15:
    leds[LED_COUNT-1] = CHSV((hue - 120), 100, 70); 
    break;
  default:
    leds[LED_COUNT-1] = CHSV((hue2), 200, bright);
  }

  FastLED.show();
  delay(del);
}

void dots() {
currentMillis = millis();
  if(currentMillis - previousMillis > del) {

  uint8_t middle = 0;
  uint8_t side = 0;
  uint8_t other = 0;
  count++;                                                     // overflowing a byte => 0

  byte x = quadwave8(count);

  other = map(x, 0, 255, LED_COUNT/4, LED_COUNT/4*3);            // 1/4 to 3/4 of strip
  side = map(x, 0, 255, 0, LED_COUNT-1);                        // full length of strip
  middle = map(x, 0, 255, LED_COUNT/3, LED_COUNT/3*2);           // 1/3 to 2/3 of strip


  leds[middle] = CHSV((hue - 115), 200, 180);
  leds[side] = CHSV((hue - 90), 200, 160);
  leds[other] = CHSV((hue - 70), 200, 140);

  LEDS.show();

  for ( byte i = 0; i < LED_COUNT; i++) {
    leds[i].fadeToBlackBy(32);
//    leds[i].nscale8(180);
  }

  FastLED.show();
  delay(del);
  
  previousMillis = currentMillis;
  }
}

void sinelon()
{
  fadeToBlackBy( leds, LED_COUNT, 20);
  int pos = beatsin16(13,0,LED_COUNT);
  leds[pos] += CHSV( hue, 255, 192);
  FastLED.show();
  delay(del);
}

// Fill the dots one after the other with a color
void fillColor() {
  for(int i = 0; i < LED_COUNT-1; i++) {
    leds[i] = CHSV(hue, 255, 210);
  }
  FastLED.show();
}
