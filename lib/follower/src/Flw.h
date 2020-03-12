#ifndef Flw_h
#define Flw_h

#include "Arduino.h"

class Flw
{
public:
    Flw(byte l1, byte l2, byte l3, byte l4, byte l5, byte s);

    uint16_t getValue(byte sensor);
    void setValue(byte sensor, uint16_t value);

private:
    
};

#endif
