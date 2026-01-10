#ifndef KLEVEBRAND_MAXJET_DRONE_H
#define KLEVEBRAND_MAXJET_DRONE_H

#include <Arduino.h>
#include "base_gyro_drone.h"
#include "./components/airplane_vtail_pid/airplane_vtail_pid.h"

class KlevebrandMaxJetDrone : public BaseGyroDrone<AirplaneVtailPid>
{
public:
    KlevebrandMaxJetDrone(uint8_t (&motor_pin_numbers)[16]) : BaseGyroDrone<AirplaneVtailPid>(motor_pin_numbers) {}
    void setup() override;
    void run() override;
    void runMotors(float gyro_roll, float gyro_pitch, float gyro_yaw) override;

    Servo motor() const { return motors[0]; };
    Servo aileron_left() const { return motors[1]; };
    Servo aileron_right() const { return motors[2]; };
    Servo rudder_left() const { return motors[3]; };
    Servo rudder_right() const { return motors[4]; };
    Servo flap_left() const { return motors[5]; };
    Servo flap_right() const { return motors[6]; };
};

#endif // KLEVEBRAND_MAXJET_DRONE_H