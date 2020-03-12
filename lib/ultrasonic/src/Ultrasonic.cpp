#include "Ultrasonic.h"

struct Sensor
{
  byte trig;
  byte echo;
};

Sensor sensors[3];

Ultrasonic::Ultrasonic(byte trig, byte echo, byte trig1, byte echo1, byte trig2, byte echo2)
{
  sensors[0].trig = trig;
  sensors[0].echo = echo;

  sensors[1].trig = trig1;
  sensors[1].echo = echo1;

  sensors[2].trig = trig2;
  sensors[2].echo = echo2;

  for (int i = 0; i < 3; i++)
  {
    pinMode(sensors[i].trig, OUTPUT);
    digitalWrite(sensors[i].trig, LOW);

    pinMode(sensors[i].echo, INPUT);
  }

  _oneCentimetreRoundTripTime = calcOneCentimetreRoundTripTime(calcSoundSpeed(25));
  _timeOutMin = calcEchoTimeout(4);
  _timeOutMax = calcEchoTimeout(300);

  if (_timeOutMax > 38000)
    _timeOutMax = 38000;
}

float Ultrasonic::getMedianFilterDistance(byte sensor)
{
  uint16_t data[3] = {0, 0, 0};
  uint16_t middle = 0;

  for (int8_t i = 0; i < 3; i++)
  {
    data[i] = getEchoPulseLength(sensor);

    if ((data[0] <= data[1]) && (data[0] <= data[2]))
    {
      middle = (data[1] <= data[2]) ? data[1] : data[2];
    }
    else if ((data[1] <= data[0]) && (data[1] <= data[2]))
    {
      middle = (data[0] <= data[2]) ? data[0] : data[2];
    }
    else
    {
      middle = (data[0] <= data[1]) ? data[0] : data[1];
    }

    return calcDistance(middle);
  }

  return 0.f;
}

uint16_t Ultrasonic::calcSoundSpeed(int16_t temperature)
{
  return (33130) + 60 * temperature;
}

float Ultrasonic::calcOneCentimetreRoundTripTime(uint16_t soundSpeed)
{
  return (float)2000000 / soundSpeed;
}

uint16_t Ultrasonic::calcEchoTimeout(uint16_t distance)
{
  if (distance > 500)
  {
    distance = 500;
  }
  else if (distance < 4)
  {
    distance = 4;
  }

  return distance * (uint16_t)_oneCentimetreRoundTripTime;
}

uint16_t Ultrasonic::getEchoPulseLength(byte sensor)
{
  uint16_t pLength = 0;

  digitalWrite(sensors[sensor].trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensors[sensor].trig, LOW);

  pLength = pulseIn(sensors[sensor].echo, HIGH, _timeOutMax);

  if ((pLength == 0) || (pLength <= _timeOutMin) || (pLength >= _timeOutMax))
    return 38000;
  return pLength;
}

float Ultrasonic::calcDistance(uint16_t pulseLength)
{
  if (pulseLength != 38000)
    return (float)pulseLength / _oneCentimetreRoundTripTime;
  return 38000;
}

float Ultrasonic::getDistance(byte sensor)
{
  return calcDistance(getEchoPulseLength(sensor));
}