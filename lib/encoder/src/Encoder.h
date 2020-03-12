#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

class Encoder
{
public:
    Encoder();

    unsigned int getPos();
    unsigned int getOldPos();
    float getTurns();
    unsigned int getRpm();
    unsigned long getTimeOld();

    void setPos(unsigned int pos);
    void setOldPos(unsigned int npos);
    void setTurns(float turns);
    void setRpm(unsigned int rpm);
    void setTimeOld(unsigned long timeOld);

    void setDirection(bool dir);
    bool getDirection();

    void updatePos();

    void setOrdenation(bool ord);
    bool getOrdenation();

private:
    bool ordenation;
};

#endif
