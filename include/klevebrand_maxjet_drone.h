#pragma once

#include "template_drone.h"
#include "drone_components/airplane_vtail_pid.h"
#include "bno08x_drone_gyro.h"
#include "hardware_processor_arduino.h"
#include "drone_components/servo_drone_motor.h"

class KlevebrandMaxJetDrone : public TemplateDrone<AirplaneVtailPid>
{
    static constexpr int motor_pin_count = 7;
    int _motor_pins[motor_pin_count]{};
    Bno08xDroneGyro _gyro;
    HardwareProcessorArduino _processor;
    ServoDroneMotor* _motors;
    BaseDronePosition _position;

public:
    KlevebrandMaxJetDrone(ServoDroneMotor* motors, const int motor_pins[motor_pin_count])
        : TemplateDrone(500, 200, &_processor, &_gyro, &_position), _gyro(10), _motors(motors)
    {
        for (int i = 0; i < motor_pin_count; i++)
        {
            _motor_pins[i] = motor_pins[i];
        }
    }

    void setup() override;
    void setupMotors() override {};
    bool run() override;
    void runMotors(float gyro_roll, float gyro_pitch, float gyro_yaw, float delta_time_seconds) override;
    void stopMotors() override {};

    ServoDroneMotor &motor() const { return _motors[0]; };
    ServoDroneMotor &aileron_left() const { return _motors[1]; };
    ServoDroneMotor &aileron_right() const { return _motors[2]; };
    ServoDroneMotor &rudder_left() const { return _motors[3]; };
    ServoDroneMotor &rudder_right() const { return _motors[4]; };
    ServoDroneMotor &flap_left() const { return _motors[5]; };
    ServoDroneMotor &flap_right() const { return _motors[6]; };
};
