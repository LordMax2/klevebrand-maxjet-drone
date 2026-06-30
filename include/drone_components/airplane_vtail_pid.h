#pragma once

#include "gyro_pid.h"
#include <Arduino.h>

class AirplaneVtailPid : public GyroPid
{
public:
    static constexpr uint16_t PID_THROTTLE_THRESHOLD = 11;
    static constexpr uint16_t PID_MAX = 40;

    static constexpr uint16_t THROTTLE_MINIMUM = 0;
    static constexpr uint16_t THROTTLE_MAXIMUM = 100;

    AirplaneVtailPid(float yaw_kp, float yaw_ki, float yaw_kd, bool yaw_compass_mode, float pitch_kp, float pitch_ki,
                     float pitch_kd, float roll_kp, float roll_ki, float roll_kd, float,
                     const int feedback_loop_hz) : GyroPid(yaw_kp, yaw_ki, yaw_kd, yaw_compass_mode, pitch_kp, pitch_ki,
                                                           pitch_kd, roll_kp, roll_ki, roll_kd, PID_MAX,
                                                           feedback_loop_hz)
    {
    };

    float pidServoAileronLF(float gyro_roll, float roll_desired_angle, float gyro_pitch, float pitch_desired_angle,
                            float gyro_yaw, float yaw_desired_angle, bool yaw_compass_mode);
    float pidServoAileronRF(float gyro_roll, float roll_desired_angle, float gyro_pitch, float pitch_desired_angle,
                            float gyro_yaw, float yaw_desired_angle, bool yaw_compass_mode);
    float pidServoTailLB(float gyro_roll, float roll_desired_angle, float gyro_pitch, float pitch_desired_angle,
                         float gyro_yaw, float yaw_desired_angle, bool yaw_compass_mode);
    float pidServoTailRB(float gyro_roll, float roll_desired_angle, float gyro_pitch, float pitch_desired_angle,
                         float gyro_yaw, float yaw_desired_angle, bool yaw_compass_mode);
};
