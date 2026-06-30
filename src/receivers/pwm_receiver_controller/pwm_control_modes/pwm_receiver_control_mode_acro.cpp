#include "receivers/pwm_control_modes/pwm_receiver_control_mode_acro.h"

#include <Arduino.h>

ControlMode_t PwmReceiverControlModeAcro::controlModeType() const
{
    return acro;
}

void PwmReceiverControlModeAcro::applyThrottleRudderAileron(KlevebrandMaxJetDrone* drone, const int throttle_pwm,
                                                           const int yaw_pwm, const int pitch_pwm, const int roll_pwm,
                                                           const int flap_pwm) const
{
    const float throttle_value_normalized = map(throttle_pwm, 1000, 2000, THROTTLE_MINIMUM, THROTTLE_MAXIMUM);
    drone->motor().setSpeed(throttle_value_normalized);

    float desired_yaw_angle_right = map(yaw_pwm, 1000, 2000, 90, 0);
    float desired_yaw_angle_left = map(yaw_pwm, 1000, 2000, 0, 90);

    if (desired_yaw_angle_left < 3) desired_yaw_angle_left = 0;
    if (desired_yaw_angle_right < 3) desired_yaw_angle_right = 0;

    float desired_pitch_angle_right = map(pitch_pwm, 1000, 2000, 90, 0);
    float desired_pitch_angle_left = map(pitch_pwm, 1000, 2000, 0, 90);

    float desired_roll_angle_right = map(roll_pwm, 1000, 2000, 0, 90);
    float desired_roll_angle_left = map(roll_pwm, 1000, 2000, 0, 90);

    float desired_aileron_right = map(desired_roll_angle_right + desired_pitch_angle_right, 0, 180, 0, 90);
    float desired_aileron_left = map(desired_roll_angle_left + desired_pitch_angle_left, 0, 180, 0, 90);

    drone->aileron_left().setSpeed(desired_aileron_left);
    drone->aileron_right().setSpeed(desired_aileron_right);

    drone->rudder_right().setSpeed(desired_yaw_angle_right);
    drone->rudder_left().setSpeed(desired_yaw_angle_left);

    float desired_flap_right = map(flap_pwm, 1000, 2000, 50, 0);
    float desired_flap_left = map(flap_pwm, 1000, 2000, 50, 100);

    drone->flap_right().setSpeed(desired_flap_right);
    drone->flap_left().setSpeed(desired_flap_left);
}
