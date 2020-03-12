/**
   Copyright (©)

   Projeto desenvolvido por Miguel Rodrigues

   Não remova este quote

   Modificado em: 01/05/2019
*/

#ifndef Robot_h
#define Robot_h

#include "Encoder.h"
#include "Ultrasonic.h"
#include "Flw.h"

class Robot
{
public:
  Robot(byte in1, byte in2, byte in3, byte in4);

  void walk(byte direction, byte speed, float distance);
  void walk(byte in1, byte in2, byte in3, byte in4, float distance);
  void turn(byte direction, byte speed, short int degree);
  void spin(byte speed, short int degree);
  void stop();

  float dis_encoder(byte encoder_index);
  float dis_ultrasonic(byte sens);

  uint16_t ldrValue(byte sens);
  uint16_t ldrOffset(byte sens);
  void setLdrOffset(byte sens, uint16_t offset);
  void setLdrValue(byte sens, uint16_t value);

  uint16_t CMtoSteps(float cm);

  Encoder getEncoder(byte index);
private:
  const float dg = 0.3073460085555556;

  void setup_motors(byte var1, byte var2, byte var3, byte var4);
  void setup_motor(byte motor_index, byte var1, byte var2);
};

#endif
