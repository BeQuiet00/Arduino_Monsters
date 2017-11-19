#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
#include "SR04.h"
#define TRIG_PIN 2
#define ECHO_PIN 3
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show(); 

  Serial.begin(9600);
  //Serial.println("Touch senser");
  mp3_set_serial (Serial);       
  mp3_set_volume (20);
}

uint8_t readCapacitivePin(int pinToMeasure) { 
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  *port &= ~(bitmask);
  *ddr |= bitmask;
  delay(1);
  *ddr &= ~(bitmask);
  *port |= bitmask;
  uint8_t cycles = 17;
  if (*pin & bitmask) { cycles = 0;}
  else if (*pin & bitmask) { cycles = 1;}
  else if (*pin & bitmask) { cycles = 2;}
  else if (*pin & bitmask) { cycles = 3;}
  else if (*pin & bitmask) { cycles = 4;}
  else if (*pin & bitmask) { cycles = 5;}
  else if (*pin & bitmask) { cycles = 6;}
  else if (*pin & bitmask) { cycles = 7;}
  else if (*pin & bitmask) { cycles = 8;}
  else if (*pin & bitmask) { cycles = 9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}
  *port &= ~(bitmask);
  *ddr |= bitmask;
  return cycles;
}

int capval;

void touchSensor(){
  for (int i=6; i<=12; i++){
    capval = readCapacitivePin(i);
    Serial.println(capval);
    if (capval>3){ 
      mp3_play(i-5);
   } 
  }
}

void lig(int lum){
  uint32_t col=strip.Color(lum, lum, lum);
  for (int i=0; i<8; i++) strip.setPixelColor(i,col);
  strip.show();
}

long dis;

unsigned long p=0;
unsigned long c=millis();

void del(int t){
  while (c-p<=t){
    c=millis();
    //Serial.println(c);
    //Serial.println(p);
    //Serial.println(t);
    touchSensor();
  }
  p=c;
}

int hr;

void loop() {
  dis=sr04.Distance();
  if (dis<=200){
    hr=200/dis;
    if (hr<=0) hr=200;
    //Serial.println(hr);
    lig(30);
    del(1000/hr);
    for (int lum=30; lum>=0; lum-=5){
      lig(lum);
      del(20/hr);
    }
    for (int lum=0; lum<=255; lum+=10){
      lig(lum);
      del(20/hr);
    }
    for (int lum=255; lum>=30; lum-=10){
      lig(lum);
      del(20/hr);
    }
    for (int lum=30; lum<=100; lum+=2){
      lig(lum);
      del(20/hr);
    }
    for (int lum=100; lum>=30; lum-=2){
      lig(lum);
      del(20/hr);
    }
  }
  else lig(0);
}

 

