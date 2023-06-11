#include "stepper.hpp"

BasicStepperDriver stepper(MOTOR_STEPS, STEPPER_DIR, STEPPER_STEP, STEPPER_SLEEP);


void stepperInit() {
    stepper.begin(RPM, MICROSTEPS);
    Serial.print("Stepper Initialised to: ");
    switch(MICROSTEPS) {
        case 1:
            Serial.println("full step");
            break;
        case 2:
            Serial.println("half step");
            break;
        case 3:
            Serial.println("3");
            break;
        case 4:
            Serial.println("4");
            break;
    }
}

void stepperRun(int shots) {
  for (int i = 0; i < shots; i++)
  {
    stepper.rotate(DEGREES_PER_SHOT);

    // would like to remove the delay function if possible
    delay(500);
    stepper.rotate(-DEGREES_PER_SHOT);
    delay(100);
  }
  
}