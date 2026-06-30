#pragma once

#include "klevebrand_maxjet_drone.h"

class BasePwmReceiverControlMode
{
public:
    virtual ~BasePwmReceiverControlMode() = default;

    virtual ControlMode_t controlModeType() const = 0;

    virtual void applyThrottleRudderAileron(KlevebrandMaxJetDrone* drone, int throttle_pwm, int yaw_pwm, int pitch_pwm,
                                           int roll_pwm, int flap_pwm) const = 0;
};
