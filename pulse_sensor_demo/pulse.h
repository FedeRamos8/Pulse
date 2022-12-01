#ifndef _PULSE_SENSOR_H
#define _PULSE_SENSOR_H

#include <Arduino.h>

#define BMP_VALUE_HI  2400
#define BMP_VALUE_LO  2100

 
class PulseSensor  
{
public:
	 
	PulseSensor(int analogPin);
	void begin();
    int read_beat();

private:
    void init() ;
    int _analogPin; 
    int state;
    int beat;
    unsigned long t1,t2;
};

#endif  
