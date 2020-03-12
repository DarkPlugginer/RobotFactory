#include "Encoder.h"

struct Data
{
    unsigned int _pos = 0;
    unsigned int _oldPos = 0.f;
    float _turns = 0.f;
    unsigned int _rpm = 0;
    unsigned long _timeOld = 0.l;

    bool _dir;
};

Data data[2];

Encoder::Encoder()
{
}

unsigned int Encoder::getPos()
{
    return getOrdenation() ? data[1]._pos : data[0]._pos;
}

unsigned int Encoder::getOldPos()
{
    return getOrdenation() ? data[1]._oldPos : data[0]._oldPos;
}

float Encoder::getTurns()
{
    return getOrdenation() ? data[1]._turns : data[0]._turns;
}

unsigned int Encoder::getRpm()
{
    return getOrdenation() ? data[1]._rpm : data[0]._rpm;
}

unsigned long Encoder::getTimeOld()
{
    return getOrdenation() ? data[1]._timeOld : data[0]._timeOld;
}

void Encoder::setPos(unsigned int pos)
{
    data[getOrdenation() ? 1 : 0]._pos = pos;
}

void Encoder::setOldPos(unsigned int npos)
{
    data[getOrdenation() ? 1 : 0]._oldPos = npos;
}

void Encoder::setTurns(float turns)
{
    data[getOrdenation() ? 1 : 0]._turns = turns;
}

void Encoder::setRpm(unsigned int rpm)
{
    data[getOrdenation() ? 1 : 0]._rpm = rpm;
}

void Encoder::setTimeOld(unsigned long timeOld)
{
    data[getOrdenation() ? 1 : 0]._timeOld = timeOld;
}

void Encoder::setDirection(bool dir)
{
    data[getOrdenation() ? 1 : 0]._dir = dir;
}

void Encoder::setOrdenation(bool ord)
{
    ordenation = ord;
}

bool Encoder::getOrdenation()
{
    return ordenation;
}

bool Encoder::getDirection()
{
    return data[getOrdenation() ? 1 : 0]._dir;
}

void Encoder::updatePos()
{
    if (getDirection() == false)
    {
        setPos(getPos() - 1);
    }
    else
    {
        setPos(getPos() + 1);
    }
}