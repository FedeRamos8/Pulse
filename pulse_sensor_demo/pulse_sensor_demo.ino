/*=================================================================
# Project : Pulse sensor
#         : 
# Date    : 2021-02-01
# Version : 1.0
#
# Note:
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY : without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE
#
# Board : Raspberry Pi Pico
# IDE   : Arduino IDE
# Library :
#    I2C LCM (PCF8574) - https://github.com/fdebrabander/arduino-liquidcrystal-i2c-library
#   
#=================================================================*/
#include "LiquidCrystal_I2C.h"
#include <Wire.h>
#include "pulse.h" 
 
#define PCF8574  0x27
#define PCF8574A 0x3F

TwoWire Wire_00(i2c0, 8,9); // SDA, SCL
LiquidCrystal_I2C lcd(&Wire_00, PCF8574, 16, 2);

#define BUILT_IN_LED  D25
#define ADC_PIN       A0 

#define PULSE_LED     16
#define BUZZER        17

PulseSensor pulse(ADC_PIN);

unsigned long t1,t2;


// low active
void buzzer_off() 
{
    digitalWrite(BUZZER, HIGH);
}

//============================================================
void setup() 
{
    Serial.begin(115200);
    Wire_00.begin();
    Wire_00.setClock(100000); // 100kHz
    lcd.begin();
    lcd.backlight();
    lcd.print("Pulse sensor");
    
    pinMode(BUILT_IN_LED, OUTPUT);
    digitalWrite(BUILT_IN_LED, HIGH);

    pinMode(PULSE_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    buzzer_off();
    

    pulse.begin();
}
 

//============================================================
void loop() 
{
    char buf[5];
    
    lcd.setCursor(4,1);
     
    int beat = pulse.read_beat();
    if (beat != 0)
    {
        if (beat<100) lcd.print(" ");
        lcd.print(beat);
        lcd.print(" BPM");
        t1 = millis();
        tone(BUZZER, 440);
        digitalWrite(PULSE_LED, HIGH);
    }  
   
      
    t2 = millis();
    // stop buzzer
    if ( (t2-t1) > 20)
    {
        t1 = millis();
        noTone(BUZZER);
        digitalWrite(PULSE_LED, LOW);
    }
    delay(10);
}
