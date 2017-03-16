#include <MIDI.h>

enum COLOR{
  COLOR_RED,
  COLOR_YELLOW,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_VIOLET,
  COLOR_WHITE
};

const int ledPin = 13;

// Effect (1-4) controlling pins
const int eff0Pin = 18;
const int eff1Pin = 19;
const int effectPinLED_RED = 3;
const int effectPinLED_BLUE = 4;
const int effectPinLED_GREEN = 5;

// Preset (1-2) controlling pins
const int presetPin = 20;
const int presetPinLED_RED = 23;
const int presetPinLED_BLUE = 22;
const int presetPinLED_GREEN = 21;

const int channel = 2; // Channel B on Disaster Area controllers

// The setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pins as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(eff0Pin, OUTPUT);
  pinMode(eff1Pin, OUTPUT);
  pinMode(effectPinLED_RED, OUTPUT);
  pinMode(effectPinLED_BLUE, OUTPUT);
  pinMode(effectPinLED_GREEN, OUTPUT);
  
  pinMode(presetPin, OUTPUT);
  pinMode(presetPinLED_RED, OUTPUT);
  pinMode(presetPinLED_BLUE, OUTPUT);
  pinMode(presetPinLED_GREEN, OUTPUT);
  
  MIDI.begin(channel);
  Serial.begin(57600);
}

// the loop() method runs over and over again,
// as long as the board has power

void loop() {
   if (MIDI.read()) {
    byte type = MIDI.getType();
    switch (type) {
      // Program changes should be modulo'd by 8 since neunaber only has 8 presets
      case ProgramChange:{
        // Flash LED on incoming read
        digitalWrite(ledPin, HIGH);
        delay(50);
        digitalWrite(ledPin, LOW);

        // Set effect (1-4)
        int pcNum = MIDI.getData1() % 8;

        if (pcNum == 0){
          digitalWrite(eff0Pin, HIGH);
          digitalWrite(eff1Pin, HIGH);
          analogWrite(presetPin, 0);

          setColor(COLOR_WHITE, effectPinLED_RED, effectPinLED_GREEN, effectPinLED_BLUE);
          setColor(COLOR_YELLOW, presetPinLED_RED, presetPinLED_GREEN, presetPinLED_BLUE);
        }
        else if (pcNum == 1){
          digitalWrite(eff0Pin, HIGH);
          digitalWrite(eff1Pin, HIGH);
          analogWrite(presetPin, 255);

          setColor(COLOR_WHITE, effectPinLED_RED, effectPinLED_GREEN, effectPinLED_BLUE);
          setColor(COLOR_VIOLET, presetPinLED_RED, presetPinLED_GREEN, presetPinLED_BLUE);
        }
        else if (pcNum == 2){
          digitalWrite(eff0Pin, LOW);
          digitalWrite(eff1Pin, HIGH);
          analogWrite(presetPin, 0);

          setColor(COLOR_BLUE, effectPinLED_RED, effectPinLED_GREEN, effectPinLED_BLUE);
          setColor(COLOR_YELLOW, presetPinLED_RED, presetPinLED_GREEN, presetPinLED_BLUE);
        }
        else if (pcNum == 3){
          digitalWrite(eff0Pin, LOW);
          digitalWrite(eff1Pin, HIGH);
          analogWrite(presetPin, 255);

          setColor(COLOR_BLUE, effectPinLED_RED, effectPinLED_GREEN, effectPinLED_BLUE);
          setColor(COLOR_VIOLET, presetPinLED_RED, presetPinLED_GREEN, presetPinLED_BLUE);
        }
        else if (pcNum == 4){
          digitalWrite(eff0Pin, HIGH);
          digitalWrite(eff1Pin, LOW);
          analogWrite(presetPin, 0);

          setColor(COLOR_GREEN, effectPinLED_RED, effectPinLED_GREEN, effectPinLED_BLUE);
          setColor(COLOR_YELLOW, presetPinLED_RED, presetPinLED_GREEN, presetPinLED_BLUE);
        }
        else if (pcNum == 5){
          digitalWrite(eff0Pin, HIGH);
          digitalWrite(eff1Pin, LOW);
          analogWrite(presetPin, 255);

          setColor(COLOR_GREEN, effectPinLED_RED, effectPinLED_GREEN, effectPinLED_BLUE);
          setColor(COLOR_VIOLET, presetPinLED_RED, presetPinLED_GREEN, presetPinLED_BLUE);
        }
        else if (pcNum == 6){
          digitalWrite(eff0Pin, LOW);
          digitalWrite(eff1Pin, LOW);
          analogWrite(presetPin, 0);

          setColor(COLOR_RED, effectPinLED_RED, effectPinLED_GREEN, effectPinLED_BLUE);
          setColor(COLOR_YELLOW, presetPinLED_RED, presetPinLED_GREEN, presetPinLED_BLUE);
        }
        else{
          digitalWrite(eff0Pin, LOW);
          digitalWrite(eff1Pin, LOW);
          analogWrite(presetPin, 255);

          setColor(COLOR_RED, effectPinLED_RED, effectPinLED_GREEN, effectPinLED_BLUE);
          setColor(COLOR_VIOLET, presetPinLED_RED, presetPinLED_GREEN, presetPinLED_BLUE);
        }
        
        break;
      }
        
      // Controls preset morph and expression inputs
      case ControlChange:{
        int CC_Number = MIDI.getData1();
        if(CC_Number == 48){
          int CC_Value = MIDI.getData2();
          analogWrite(presetPin, CC_Value * 2);

          analogWrite(presetPinLED_RED, 255 + (CC_Value * -1.22));
          analogWrite(presetPinLED_GREEN, 170 + (CC_Value * -1.3385));
          analogWrite(presetPinLED_BLUE, CC_Value * 2);

          digitalWrite(ledPin, HIGH);
          digitalWrite(ledPin, LOW);
        }
        break;
      }
    }
   }
}

void setColor(COLOR color, int redPin, int greenPin, int bluePin){
  switch (color){
    case (COLOR_RED):{
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      break;
    }
    case (COLOR_YELLOW):{
      analogWrite(redPin, 255);
      analogWrite(greenPin, 170);
      analogWrite(bluePin, 0);
      break;
    }
    case (COLOR_GREEN):{
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
      break;
    }
    case (COLOR_BLUE):{
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
      break;
    }
    case (COLOR_VIOLET):{
      analogWrite(redPin, 100);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
      break;
    }
    case (COLOR_WHITE):{
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 255);
      break;
    }
  }
}

