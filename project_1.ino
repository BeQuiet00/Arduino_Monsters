#define NOTE_B0  31                //....7
#define NOTE_C1  33                //...1
#define NOTE_CS1 35
#define NOTE_D1  37                //...2
#define NOTE_DS1 39
#define NOTE_E1  41                //...3
#define NOTE_F1  44                //...4
#define NOTE_FS1 46               
#define NOTE_G1  49                //...5
#define NOTE_GS1 52
#define NOTE_A1  55                //...6
#define NOTE_AS1 58               
#define NOTE_B1  62                //...7
#define NOTE_C2  65                //..1
#define NOTE_CS2 69
#define NOTE_D2  73                //..2
#define NOTE_DS2 78
#define NOTE_E2  82                //..3
#define NOTE_F2  87                //..4
#define NOTE_FS2 93
#define NOTE_G2  98                //..5
#define NOTE_GS2 104
#define NOTE_A2  110                //..6
#define NOTE_AS2 117
#define NOTE_B2  123                //..7
#define NOTE_C3  131                //.1
#define NOTE_CS3 139
#define NOTE_D3  147                //.2
#define NOTE_DS3 156
#define NOTE_E3  165                //.3
#define NOTE_F3  175                //.4
#define NOTE_FS3 185
#define NOTE_G3  196                //.5
#define NOTE_GS3 208
#define NOTE_A3  220                //.6
#define NOTE_AS3 233
#define NOTE_B3  247                //.7
#define NOTE_C4  262                //1
#define NOTE_CS4 277
#define NOTE_D4  294                //2
#define NOTE_DS4 311
#define NOTE_E4  330                //3
#define NOTE_F4  349                //4
#define NOTE_FS4 370
#define NOTE_G4  392                //5
#define NOTE_GS4 415
#define NOTE_A4  440                //6
#define NOTE_AS4 466
#define NOTE_B4  494                //7
#define NOTE_C5  523                //1.
#define NOTE_CS5 554
#define NOTE_D5  587                //2.
#define NOTE_DS5 622
#define NOTE_E5  659                //3.
#define NOTE_F5  698                //4.
#define NOTE_FS5 740
#define NOTE_G5  784                //5.
#define NOTE_GS5 831
#define NOTE_A5  880                //6.
#define NOTE_AS5 932
#define NOTE_B5  988                //7.
#define NOTE_C6  1047                //1..
#define NOTE_CS6 1109
#define NOTE_D6  1175                //2..
#define NOTE_DS6 1245
#define NOTE_E6  1319                //3..
#define NOTE_F6  1397                //4..
#define NOTE_FS6 1480
#define NOTE_G6  1568                //5..
#define NOTE_GS6 1661
#define NOTE_A6  1760                //6..
#define NOTE_AS6 1865
#define NOTE_B6  1976                //7..
#define NOTE_C7  2093                //1...
#define NOTE_CS7 2217       
#define NOTE_D7  2349                //2...
#define NOTE_DS7 2489
#define NOTE_E7  2637                //3...
#define NOTE_F7  2794                //4...
#define NOTE_FS7 2960
#define NOTE_G7  3136                //5...
#define NOTE_GS7 3322
#define NOTE_A7  3520                //6...
#define NOTE_AS7 3729
#define NOTE_B7  3951                //7...
#define NOTE_C8  4186                //1....
#define NOTE_CS8 4435
#define NOTE_D8  4699                //2....
#define NOTE_DS8 4978

int capval;

void setup(){
  
}

int melody[]={NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,
NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,NOTE_A4,
NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4,NOTE_B4,
NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5};
int noteDurations[] = {2,4,4,2,4,4,2,4,4,2,4,4,
2,4,4,2,4,4,2,4,4,2,4,4,
2,4,4,2,4,4,2,4,4,2,4,4,
2,4,4,2,4,4,2,4,4,2,4,4};

void playm(){
  for (int i=0; i<48; i++){
      int noteDuration=1000/noteDurations[i];
      tone(8,melody[i],noteDuration);
      int pauseBetweenNotes=noteDuration*1.30;
      delay(pauseBetweenNotes);
  }
}

void loop (){
  capval = readCapacitivePin(7);
  //Serial.println(capval, DEC);
  if (capval > 2) { 
    playm();
    delay(10);
  } 
}

uint8_t readCapacitivePin(int pinToMeasure) { // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  // Arduino pin number to the AVR PORT, PIN, DDR,
  // and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr |= bitmask;
  delay(1);
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
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

  // Discharge the pin again by setting it low and output
  // It's important to leave the pins low if you want to 
  // be able to touch more than 1 sensor at a time - if
  // the sensor is left pulled high, when you touch
  // two sensors, your body will transfer the charge between
  // sensors.
  *port &= ~(bitmask);
  *ddr |= bitmask;

  return cycles;
}
