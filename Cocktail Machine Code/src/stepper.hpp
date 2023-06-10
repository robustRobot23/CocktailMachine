#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>
#include "pinDefinitions.hpp"
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200
#define RPM 120
#define REVOLUTIONS_PER_SHOT 2
#define DEGREES_IN_REVOLUTION 360
#define DEGREES_PER_SHOT REVOLUTIONS_PER_SHOT * DEGREES_IN_REVOLUTION


// 1=full step, 2=half step etc
// make this match the PCB hardware MICROSTEP selected
#define MICROSTEPS 1

// // 2-wire basic config, microstepping is hardwired on the driver
void stepperInit();
void stepperRun(int shots);


#endif