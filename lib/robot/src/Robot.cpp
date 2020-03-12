/**
   Copyright (©)

   Projeto desenvolvido por Miguel Rodrigues

   Não remova este quote

   Modificado em: 01/05/2019
*/

#include "Robot.h"

/*
   Direções
   0 - frente
   1 - trás
   2 - esquerda
   3 - direita
*/

/*
   Encoders
   0 - esquerdo
   1 - direito
*/

/*
   Motores
   0 - esquerdo
   1 - direito
*/

/*
   Estrutura de dados dos motores
*/
struct Motor
{
  byte in1;
  byte in2;
};

Encoder encoders[2];

/**
   * Declaração de arrays para armazedar dados dos motores e dos encoders
*/
Motor motors[2];

/**
   * Instancia da classe 'Ultrasonic'
*/
Ultrasonic ultrasonic(4, 7, 8, 11, 12, 13);

Flw follower(A1, A2, A3, A4, A5, A0);

/**
   Construtor da classe 'Robot'
   @param in1 In1 da ponte h
   @param in2 In2 da ponte h
   @param in3 In3 da ponte h
   @param in4 In4 da ponte h
*/
Robot::Robot(byte in1, byte in2, byte in3, byte in4)
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  motors[0].in1 = in1;
  motors[0].in2 = in2;

  motors[1].in1 = in3;
  motors[1].in2 = in4;

  encoders[0].setOrdenation(false);
  encoders[1].setOrdenation(true);
}

/**
   Método usado para andar para frente ou para trás, com ou sem uma distância determinada
   @param direction direção a se locomover
   @param speed velocidade a ser aplicada nos motores
   @param distance distância a ser percorrida caso maior que 0
   @param zero opção de zerar o encoder ou não
*/
void Robot::walk(byte direction, byte speed, float distance)
{
  switch (direction)
  {
  case 0:

    if (distance == 0)
    {
      getEncoder(0).setDirection(true);
      getEncoder(1).setDirection(true);

      setup_motors(speed, 0, 0, speed);
    }
    else
    {
      if (distance < 0)
        return;

      getEncoder(0).setDirection(true);
      getEncoder(1).setDirection(true);

      while (dis_encoder(0) < distance && dis_encoder(1) < distance)
      {
        setup_motors(speed, 0, 0, speed);
      }

      /*if (zero)
      {
        getEncoder(0).setPos(0);
        getEncoder(1).setPos(0);
      }*/
    }
    break;
  case 1:

    if (distance == 0)
    {
      getEncoder(0).setDirection(false);
      getEncoder(1).setDirection(false);

      setup_motors(0, speed, speed, 0);
    }
    else
    {
      if (distance < 0)
        return;

      getEncoder(0).setDirection(false);
      getEncoder(1).setDirection(false);

      while (dis_encoder(0) > -distance && dis_encoder(1) > -distance)
      {
        setup_motors(0, speed, speed, 0);
      }

      /*if (zero)
      {
        getEncoder(0).setPos(0);
        getEncoder(1).setPos(0);
      }*/
    }
    break;
  default:
    break;
  }
}

/**
   Método usado para andar com todas as velocidades parametrizadas e opção de distância
   @param in1 velocidade a ser aplicada em In1
   @param in2 velocidade a ser aplicada em In2
   @param in3 velocidade a ser aplicada em In3
   @param in4 velocidade a ser aplicada em In4
   @param distance distância a ser percorrida
*/
void Robot::walk(byte in1, byte in2, byte in3, byte in4, float distance)
{
  if (distance < 0)
    return;

  if (distance == 0)
  {
    setup_motors(in1, in2, in3, in4);

    getEncoder(0).setDirection(true);
    getEncoder(1).setDirection(true);
  }
  else
  {
    if (in1 != 0 && in4 != 0)
    {
      while (dis_encoder(0) < distance && dis_encoder(1) < distance)
      {
        setup_motors(in1, in2, in3, in4);
      }
    }
    else if (in1 != 0 && in4 == 0)
    {
      while (dis_encoder(1) < distance)
      {
        setup_motors(in1, in2, in3, in4);
      }
    }
    else if (in1 == 0 && in4 != 0)
    {
      while (dis_encoder(0) < distance)
      {
        setup_motors(in1, in2, in3, in4);
      }
    }
  }
}

/**
   Método usado para rodar o robô em torno do próprio eixo. 
   Roda o robô no sentido dos ponteiros se 'degree' for maior que zero,
   caso contrário, roda no sentido contrário dos ponteiros
   @param speed velocidade a ser aplicada nos motores
   @param degree ângulo a ser virado
*/
void Robot::spin(byte speed, short int degree)
{
  if (degree == 0)
    return;

  getEncoder(0).setPos(0);
  getEncoder(1).setPos(0);

  float toWalk = degree == 0 ? 0 : (degree * dg) / 2.0;

  if (degree > 0)
  {
    getEncoder(0).setDirection(true);
    getEncoder(1).setDirection(false);

    while (dis_encoder(0) < toWalk && dis_encoder(1) > -toWalk)
    {
      setup_motors(0, speed, 0, speed);
    }
  }
  else
  {
    getEncoder(0).setDirection(false);
    getEncoder(1).setDirection(true);

    while (dis_encoder(0) > toWalk && dis_encoder(1) < -toWalk)
    {
      setup_motors(speed, 0, speed, 0);
    }
  }
}

/**
   Método usado para virar para a esquerda ou direita, com ou sem uma angulação determinada
   @param direction direção a se locomover
   @param speed velocidade a ser aplicada nos motores
   @param degree ângulo a ser virado
*/
void Robot::turn(byte direction, byte speed, short int degree)
{
  float toWalk = degree == 0 ? 0 : (degree * dg) / 180.0;

  getEncoder(0).setPos(0);
  getEncoder(1).setPos(0);

  switch (direction)
  {
  case 2:
    if (degree == 0)
    {
      setup_motors(speed, 0, 0, 0);

      getEncoder(0).setDirection(true);
    }
    else
    {
      if (degree > 0)
      {
        getEncoder(1).setDirection(true);

        while (dis_encoder(1) < toWalk)
        {
          setup_motors(speed, 0, 0, 0);
        }

        getEncoder(1).setPos(0);
      }
      else
      {
        getEncoder(1).setDirection(false);

        while (dis_encoder(1) > toWalk)
        {
          setup_motors(0, speed, 0, 0);
        }

        getEncoder(1).setPos(0);
      }
    }
    break;

  case 3:
    if (degree == 0)
    {
      setup_motors(0, 0, 0, speed);

      getEncoder(0).setDirection(true);
    }
    else
    {
      if (degree > 0)
      {
        getEncoder(0).setDirection(true);

        while (dis_encoder(0) < toWalk)
        {
          setup_motors(0, 0, 0, speed);
        }

        getEncoder(0).setPos(0);
      }
      else
      {
        getEncoder(0).setDirection(false);

        while (dis_encoder(0) > toWalk)
        {
          setup_motors(0, 0, speed, 0);
        }

        getEncoder(0).setPos(0);
      }
    }
    break;

  default:
    break;
  }
}

/**
   * Método usado para parar o robô
*/
void Robot::stop()
{
  setup_motors(0, 0, 0, 0);
}

/**
   Método usado para locomoção
   @param var1 velocidade a ser aplicada em In1
   @param var2 velocidade a ser aplicada em In2
   @param var3 velocidade a ser aplicada em In3
   @param var4 velocidade a ser aplicada em In4
*/
void Robot::setup_motors(byte var1, byte var2, byte var3, byte var4)
{
  setup_motor(0, var1, var2);
  setup_motor(1, var3, var4);
}

/**
   Método usado para locomoção
   @param motor_index motor a ser aplicada a velocidade
   @param var1 velocidade a ser aplicada
   @param var2 velocidade a ser aplicada
*/
void Robot::setup_motor(byte motor_index, byte var1, byte var2)
{
  analogWrite(motors[motor_index].in1, var1);
  analogWrite(motors[motor_index].in2, var2);
}

/**
  Método usado para calcular a distância percorrida utilizando encoders
  @param encoder_index encoder a ter a distância calculada
*/
float Robot::dis_encoder(byte encoder_index)
{
  Encoder enc = getEncoder(encoder_index);

  if (enc.getDirection() == false)
  {
    enc.setTurns((enc.getPos() - 65535) / 20.0);
  }
  else
  {
    enc.setTurns(enc.getPos() / 20.0);
  }

  float result = 2 * PI * 3.4 * enc.getTurns();
  if (result == -70000.66)
    result = 0;

  return result;
}

/*
  Método que retorna a distância aferida no sensor de ultrassom parametrizado
  @param sens sensor a aferir a distância
*/
float Robot::dis_ultrasonic(byte sens)
{
  return ultrasonic.getDistance(sens);
}

uint16_t Robot::ldrValue(byte sens)
{
  return follower.getValue(sens);
}

void Robot::setLdrValue(byte sens, uint16_t value)
{
  follower.setValue(sens, value);
}

/*
  Método que retorna ao objeto encoder
  @param index encoder a retornar
*/
Encoder Robot::getEncoder(byte index)
{
  if (index == 0 || index == 1)
  {
    return encoders[index];
  }
  return encoders[0];
}

uint16_t Robot::CMtoSteps(float cm)
{
  float circunference = (3.4 * PI) / 10;
  float cm_step = circunference / 20;

  float f_result = cm / cm_step;
  return (uint16_t)f_result;
}