#include "drone_pwm_receiver.h"

void DronePwmReceiver::setThrottle(KlevebrandMaxJetDrone *drone)
{
    float throttle_value = receiver.getChannelValue(throttle_receiver_channel_number);
    drone->setThrottle(throttle_value);
}

void DronePwmReceiver::setRudderAileron(KlevebrandMaxJetDrone *drone)
{
    // Not implemented for this drone type
    float desired_yaw_angle = map(receiver.getChannelValue(yaw_receiver_channel_number), 1000, 2000, 0, 100);
    if (desired_yaw_angle < 5 && desired_yaw_angle > -5)
    {
        desired_yaw_angle = 0;
    }

    float desired_pitch_angle_right = map(receiver.getChannelValue(pitch_receiver_channel_number), 1000, 2000, 90, 0);
    float desired_pitch_angle_left = map(receiver.getChannelValue(pitch_receiver_channel_number), 1000, 2000, 0, 90);

    float desired_roll_angle_right = map(receiver.getChannelValue(roll_receiver_channel_number), 1000, 2000, 90, 0);
    float desired_roll_angle_left = map(receiver.getChannelValue(roll_receiver_channel_number), 1000, 2000, 0, 90);

    float desired_aileron_right = map(desired_roll_angle_right + desired_pitch_angle_right, 0, 180, 0, 90);
    float desired_aileron_left = map(desired_roll_angle_left + desired_pitch_angle_left, 0, 180, 0, 90);

    drone->aileron_left().setSpeed(desired_aileron_left);
    drone->aileron_right().setSpeed(desired_aileron_right);

    drone->rudder_left().setSpeed(desired_yaw_angle);
    drone->rudder_right().setSpeed(-desired_yaw_angle);

    float desired_flap_right = map(receiver.getChannelValue(6), 1000, 2000, 50, 100);
    float desired_flap_left = map(receiver.getChannelValue(6), 1000, 2000, 50, 0);

    drone->flap_right().setSpeed(desired_flap_right);
    drone->flap_left().setSpeed(desired_flap_left);
}

void DronePwmReceiver::setup()
{
    receiver.setup();
}
