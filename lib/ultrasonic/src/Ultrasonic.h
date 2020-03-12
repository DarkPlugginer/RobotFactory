#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"

class Ultrasonic
{
public:
       Ultrasonic(byte trig, byte echo, byte trig1, byte echo1, byte trig2, byte echo2);

       float getDistance(byte sensor);
       float getMedianFilterDistance(byte sensor);
private:
       float _oneCentimetreRoundTripTime;
       uint8_t _timeOutMin;
       uint16_t _timeOutMax;

       uint16_t calcSoundSpeed(int16_t temperature);
       float calcOneCentimetreRoundTripTime(uint16_t soundSpeed);
       uint16_t calcEchoTimeout(uint16_t distance);
       inline uint16_t getEchoPulseLength(byte sensor);
       inline float calcDistance(uint16_t pulseLength);
};

#endif
