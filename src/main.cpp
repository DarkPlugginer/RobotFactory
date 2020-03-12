//PROGRAMACAO ROBO 6 PILHAS 

#include <Robot.h>

Robot robocop(6, 5, 9, 10);

void interptEncoderLeft();
void interptEncoderRight();

void setup()
{
    attachInterrupt(digitalPinToInterrupt(3), interptEncoderLeft, FALLING);
    attachInterrupt(digitalPinToInterrupt(2), interptEncoderRight, FALLING);
}

byte turns = 0;

void loop()
{
   while (robocop.ldrValue(1) >= 720)
    {
        robocop.turn(3, 67, 1);
    }

    while (robocop.ldrValue(3) >= 720)
    {
        robocop.turn(2, 67, 1);
    }

    if (robocop.ldrValue(0) >= 770)
    {
        if (turns > 0)
            return;

        robocop.spin(67, 90);

        turns++;
    }

    while (robocop.ldrValue(2) >= 720)
    {
        robocop.walk(0, 65, 0);
    }

    while (robocop.ldrValue(1) <= 680 && robocop.ldrValue(2) <= 680 && robocop.ldrValue(3) <= 680 && turns != 0 && millis() >= 38000)
    {
        robocop.turn(2, 80, 5);
        robocop.turn(2, 80, 63);
        robocop.turn(3, 80, 60);

        while (robocop.dis_ultrasonic(0) < 20)
        {
            robocop.turn(3, 100, 45);
        }

        while (robocop.dis_ultrasonic(2) < 20)
        {
            robocop.turn(2, 100, 45);
        }

        if (robocop.dis_ultrasonic(1) <= 15)
        {
            while (robocop.dis_ultrasonic(1) < 20)
            {
                robocop.walk(1, 100, 10);
            }

            if (robocop.dis_ultrasonic(0) > robocop.dis_ultrasonic(2))
            {
                robocop.spin(100, -45);
            }
            else if (robocop.dis_ultrasonic(2) > robocop.dis_ultrasonic(0))
            {
                robocop.spin(100, 45);
            }
            else
            {
                robocop.turn(2, 100, 45);
            }
        }
    }
}

//A0  A1  A2  A3  A4
//0   1   2   3   4

void interptEncoderLeft()
{
    unsigned long lasInterruptLeft = 0;
    unsigned long interruptTimeLeft = millis();

    if (interruptTimeLeft - lasInterruptLeft > 15)
    {
        Encoder encl = robocop.getEncoder(0);
        encl.updatePos();

        if (millis() - encl.getTimeOld() >= 1000)
        {
            noInterrupts();

            encl.setRpm(3000 / (millis() - encl.getTimeOld()) * (encl.getPos() - encl.getOldPos()));
            encl.setTimeOld(millis());
            encl.setOldPos(encl.getPos());

            interrupts();
        }
    }

    lasInterruptLeft = interruptTimeLeft;
}

void interptEncoderRight()
{
    unsigned long lasInterruptRight = 0;
    unsigned long interruptTimeRight = millis();

    if (interruptTimeRight - lasInterruptRight > 15)
    {
        Encoder encr = robocop.getEncoder(1);
        encr.updatePos();

        if (millis() - encr.getTimeOld() >= 1000)
        {
            noInterrupts();

            encr.setRpm(3000 / (millis() - encr.getTimeOld()) * (encr.getPos() - encr.getOldPos()));
            encr.setTimeOld(millis());
            encr.setOldPos(encr.getPos());

            interrupts();
        }
    }

    lasInterruptRight = interruptTimeRight;
}
/*
//PROGRAMACAO ROBO 6 PILHAS

#include <Robot.h>

Robot robocop(6, 5, 9, 10);

void interptEncoderLeft();
void interptEncoderRight();

void setup()
{
    attachInterrupt(digitalPinToInterrupt(3), interptEncoderLeft, FALLING);
    attachInterrupt(digitalPinToInterrupt(2), interptEncoderRight, FALLING);
}

byte turns = 0;

void loop()
{
    while (robocop.ldrValue(1) >= 750)
    {
        robocop.turn(3, 70, 1);
    }

    while (robocop.ldrValue(3) >= 750)
    {
        robocop.turn(2, 70, 1);
    }

    if (robocop.ldrValue(0) >= 820)
    {
        if (turns > 0)
            return;

        robocop.spin(80, 90);

        turns++;
    }

    while (robocop.ldrValue(2) >= 800)
    {
        robocop.walk(0, 70, 0);
    }

    while (robocop.ldrValue(1) <= 700 && robocop.ldrValue(2) <= 700 && robocop.ldrValue(3) <= 700 && turns != 0)
    {
        robocop.turn(2, 80, 60);
        robocop.turn(3, 80, 60);

        while (robocop.dis_ultrasonic(0) < 25)
        {
            robocop.turn(3, 100, 45);
        }

        while (robocop.dis_ultrasonic(2) < 25)
        {
            robocop.turn(2, 100, 45);
        }

        if (robocop.dis_ultrasonic(1) <= 25)
        {
            while (robocop.dis_ultrasonic(1) < 30)
            {
                robocop.walk(1, 100, 10);
            }

            if (robocop.dis_ultrasonic(0) > robocop.dis_ultrasonic(2))
            {
                robocop.spin(100, -45);
            }
            else if (robocop.dis_ultrasonic(2) > robocop.dis_ultrasonic(0))
            {
                robocop.spin(100, 45);
            }
            else if (robocop.dis_ultrasonic(0) < 25 && robocop.dis_ultrasonic(2) < 25)
            {
                robocop.spin(90, 180);
            }
            else
            {
                robocop.turn(2, 100, 45);
            }
        }
    }
}

//A0  A1  A2  A3  A4
//0   1   2   3   4

void interptEncoderLeft()
{
    unsigned long lasInterruptLeft = 0;
    unsigned long interruptTimeLeft = millis();

    if (interruptTimeLeft - lasInterruptLeft > 15)
    {
        Encoder encl = robocop.getEncoder(0);
        encl.updatePos();

        if (millis() - encl.getTimeOld() >= 1000)
        {
            noInterrupts();

            encl.setRpm(3000 / (millis() - encl.getTimeOld()) * (encl.getPos() - encl.getOldPos()));
            encl.setTimeOld(millis());
            encl.setOldPos(encl.getPos());

            interrupts();
        }
    }

    lasInterruptLeft = interruptTimeLeft;
}

void interptEncoderRight()
{
    unsigned long lasInterruptRight = 0;
    unsigned long interruptTimeRight = millis();

    if (interruptTimeRight - lasInterruptRight > 15)
    {
        Encoder encr = robocop.getEncoder(1);
        encr.updatePos();

        if (millis() - encr.getTimeOld() >= 1000)
        {
            noInterrupts();

            encr.setRpm(3000 / (millis() - encr.getTimeOld()) * (encr.getPos() - encr.getOldPos()));
            encr.setTimeOld(millis());
            encr.setOldPos(encr.getPos());

            interrupts();
        }
    }

    lasInterruptRight = interruptTimeRight;
}

*/