#ifndef SERVO_DRONE_MOTOR_H
#define SERVO_DRONE_MOTOR_H

#include "Arduino.h"
#include "base_drone_motor.h"
#include <Servo.h>

class ServoDroneMotor : public BaseDroneMotor
{
public:
    ServoDroneMotor() : BaseDroneMotor() {}

    void setup(int pin)
    {
        _motor.attach(pin);
    }

    void setSpeed(float percentage) override
    {
        int microseconds = map(percentage, 0, 100, 10, 170);

        microseconds = constrain(microseconds, 0, 180);

        _motor.write(microseconds);
    }
private:
    Servo _motor;
};

#endif // SERVO_DRONE_MOTOR_H