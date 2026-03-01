#include "drone_pwm_receiver.h"

void DronePwmReceiver::setThrottle(KlevebrandMaxJetDrone *drone)
{
    float throttle_value = receiver.getChannelValue(throttle_receiver_channel_number);
    drone->setThrottle(throttle_value);
}

void DronePwmReceiver::setRudderAileron(KlevebrandMaxJetDrone *drone)
{
    // Not implemented for this drone type
    float desired_yaw_angle = map(receiver.getChannelValue(yaw_receiver_channel_number), 1000, 2000, 45, -45);
    if (desired_yaw_angle < 5 && desired_yaw_angle > -5)
    {
        desired_yaw_angle = 0;
    }

    float desired_pitch_angle = map(receiver.getChannelValue(pitch_receiver_channel_number), 1000, 2000, -45, 45);
    if (desired_pitch_angle < 5 && desired_pitch_angle > -5)
    {
        desired_pitch_angle = 0;
    }

    float desired_roll_angle = map(receiver.getChannelValue(roll_receiver_channel_number), 1000, 2000, -45, 45);
    if (desired_roll_angle < 5 && desired_roll_angle > -5)
    {
        desired_roll_angle = 0;
    }

    drone->aileron_left().setSpeed(desired_pitch_angle + desired_roll_angle);
    drone->aileron_right().setSpeed(desired_pitch_angle - desired_roll_angle);

    drone->rudder_left().setSpeed(desired_yaw_angle);
    drone->rudder_right().setSpeed(-desired_yaw_angle);
}

void DronePwmReceiver::setup()
{
    receiver.setup();
}
