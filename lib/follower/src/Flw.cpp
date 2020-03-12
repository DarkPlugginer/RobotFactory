#include "Flw.h"

struct Ldr
{
    byte pin;
    uint16_t offset = 0;
    uint16_t value = 0;
};

Ldr ldrs[5];

Flw::Flw(byte l1, byte l2, byte l3, byte l4, byte l5, byte s)
{
    ldrs[0].pin = l1;
    ldrs[1].pin = l2;
    ldrs[2].pin = l3;
    ldrs[3].pin = l4;
    ldrs[4].pin = l5;

    for(byte i = 0; i < 5; i++)
    {
        pinMode(ldrs[i].pin, INPUT);
    }

    pinMode(s, OUTPUT);
    digitalWrite(s, HIGH);
}

uint16_t Flw::getValue(byte sensor)
{
    return analogRead(ldrs[sensor].pin);
}

void Flw::setValue(byte sensor, uint16_t value)
{
    ldrs[sensor].value = value;
}