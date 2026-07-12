#pragma once

#include "drone_components/servo_drone_motor.h"
#include "template_drone.h"
#include "drone_components/airplane_vtail_pid.h"
#include "bno08x_drone_gyro.h"
#include "hardware_processor_arduino.h"
#include "quadcopter_position.h"

using MaxJetGyro = Bno08xDroneGyro;
using MaxJetProcessor = HardwareProcessorArduino;
using MaxJetPosition = QuadcopterPosition<MaxJetGyro>;
using MaxJetPid = AirplaneVtailPid;
using MaxJetDroneBase = TemplateDrone<MaxJetPid, MaxJetPosition, MaxJetGyro, MaxJetProcessor>;

class KlevebrandMaxJetDrone : public MaxJetDroneBase
{
    ServoDroneMotor* _motors;
    static constexpr int motor_pin_count = 7;
    int _motor_pins[motor_pin_count]{};

    void attachMotors() const;

    void detachMotors() const;

public:
    static constexpr int gyro_reset_pin = 10;

    KlevebrandMaxJetDrone(ServoDroneMotor* motors, const int motor_pins[motor_pin_count]);

    void setup();

    bool run();

    void runMotors(float gyro_roll, float gyro_pitch, float gyro_yaw, float delta_time_seconds);

    void enableMotors();

    void disableMotors();

    void setupMotors();

    void stopMotors();

    ServoDroneMotor& motor() const { return _motors[0]; }

    ServoDroneMotor& aileronLeft() const { return _motors[1]; }

    ServoDroneMotor& aileronRight() const { return _motors[2]; }

    ServoDroneMotor& rudderLeft() const { return _motors[3]; }

    ServoDroneMotor& rudderRight() const { return _motors[4]; }

    ServoDroneMotor& flapLeft() const { return _motors[5]; }

    ServoDroneMotor& flapRight() const { return _motors[6]; }
};
