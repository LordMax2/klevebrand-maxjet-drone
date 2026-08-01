#include "receivers/pwm_control_modes/pwm_receiver_control_mode_acro.h"

#include "receivers/pwm_receiver_controller.h"

#include <Arduino.h>

constexpr int PWM_DEADZONE = 20;

constexpr float ACRO_EXPONENTIAL_INCREASE_RATE = 0.5f;

ControlMode_t PwmReceiverControlModeAcro::controlModeType() const
{
    return acro;
}

void PwmReceiverControlModeAcro::applyThrottleRudderAileron(KlevebrandMaxJetDrone* drone, const int throttle_pwm,
                                                           const int yaw_pwm, const int pitch_pwm,
                                                           const int roll_pwm) const
{
    const float throttle_value_normalized = map(throttle_pwm, 1000, 2000, AirplaneVtailPid::THROTTLE_MINIMUM,
                                                AirplaneVtailPid::THROTTLE_MAXIMUM);
    drone->motor().setSpeed(throttle_value_normalized);

    float desired_yaw_angle = map(yaw_pwm, 1000, 2000, 20, 80);

    if (desired_yaw_angle < 3) desired_yaw_angle = 0;

    float desired_pitch_angle_right = map(pitch_pwm, 1000, 2000, 90, 10);
    float desired_pitch_angle_left = map(pitch_pwm, 1000, 2000, 10, 90);

    float desired_roll_angle_right = map(roll_pwm, 1000, 2000, 90, 10);
    float desired_roll_angle_left = map(roll_pwm, 1000, 2000, 90, 10);

    float desired_aileron_right = map(desired_roll_angle_right + desired_pitch_angle_right, 0, 180, 10, 90);
    float desired_aileron_left = map(desired_roll_angle_left + desired_pitch_angle_left, 0, 180, 10, 90);

    drone->aileronLeft().setSpeed(desired_aileron_left);
    drone->aileronRight().setSpeed(desired_aileron_right);

    drone->rudderRight().setSpeed(desired_yaw_angle);
    drone->rudderLeft().setSpeed(desired_yaw_angle);

    const int flap_pwm = PwmReceiverController::getChannelValue(6);
    float desired_flap_right = map(flap_pwm, 1000, 2000, 50, 100);
    float desired_flap_left = map(flap_pwm, 1000, 2000, 50, 0);

    drone->flapRight().setSpeed(desired_flap_right);
    drone->flapLeft().setSpeed(desired_flap_left);
}

float PwmReceiverControlModeAcro::normalizePwm(const int pwm_microseconds)
{
    const int centered = pwm_microseconds - 1500;

    if (abs(centered) < PWM_DEADZONE)
    {
        return 0.0f;
    }

    return constrain(centered / 500.0f, -1.0f, 1.0f);
}

float PwmReceiverControlModeAcro::applyExpo(const float input, const float expo)
{
    const float sign = (input >= 0.0f) ? 1.0f : -1.0f;
    const float abs_input = abs(input);

    return sign * (abs_input * abs_input * abs_input * expo + abs_input * (1.0f - expo));
}
