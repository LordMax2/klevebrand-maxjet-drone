#ifndef KLEVEBRAND_MAXJET_DRONE_H
#define KLEVEBRAND_MAXJET_DRONE_H

#include <Arduino.h>
#include "template_gyro_drone.h"
#include "airplane_vtail_pid.h"
#include "bno08x_drone_gyro.h"
#include "eeprom_pid_repository.h"
#include "hardware_processor_arduino.h"
#include "servo_drone_motor.h"

class KlevebrandMaxJetDrone : public TemplateGyroDrone<AirplaneVtailPid>
{
private:
    Bno08xDroneGyro _gyro;
    EepromPidRepository _pid_repository;
    HardwareProcessorArduino _processor;
    ServoDroneMotor *_motors;

public:
    KlevebrandMaxJetDrone(ServoDroneMotor *motors) : TemplateGyroDrone<AirplaneVtailPid>(500, 200, 10000, &_processor, &_gyro, &_pid_repository), _gyro(10)
    {
        this->_motors = motors;
    }
    void setup() override;
    void run() override;
    void runMotors(float gyro_roll, float gyro_pitch, float gyro_yaw) override;

    ServoDroneMotor motor() const { return _motors[0]; };
    ServoDroneMotor aileron_left() const { return _motors[1]; };
    ServoDroneMotor aileron_right() const { return _motors[2]; };
    ServoDroneMotor rudder_left() const { return _motors[3]; };
    ServoDroneMotor rudder_right() const { return _motors[4]; };
    ServoDroneMotor flap_left() const { return _motors[5]; };
    ServoDroneMotor flap_right() const { return _motors[6]; };
};

#endif // KLEVEBRAND_MAXJET_DRONE_H