#include "klevebrand_maxjet_drone.h"

void KlevebrandMaxJetDrone::setup()
{
    _processor.setup();

    _processor.print("STARTING DRONE...");

    _gyro.setup();

    setupMotors();

    static auto none_flight_mode = BaseControlMode();
    activateControlMode(&none_flight_mode);

    processor->print("DRONE STARTED!");
}

static unsigned long last_run_start_microseconds_timestamp = 0;
static unsigned long last_gyro_fetch_duration = 0;

bool KlevebrandMaxJetDrone::run()
{
    if (delayToKeepFeedbackLoopHz(last_run_start_microseconds_timestamp - last_gyro_fetch_duration) > 0)
    {
        return false;
    }

    const unsigned long current_time = timestampMicroseconds();
    const unsigned long delta_time = current_time - last_run_start_microseconds_timestamp;
    const float delta_time_seconds = delta_time / 1000000.0f;
    last_run_start_microseconds_timestamp = current_time;

    // Get the latest data from the gyroscope
    updateGyro();

    // Increment the integral part of the PID loop
    if (getThrottle() > PID_THROTTLE_THRESHOLD)
    {
        runPidOptimizer(processor->millisecondsTimestamp());
        calculatePidIntegral(_gyro.roll(), _gyro.pitch(), _gyro.yaw());
    }
    else
    {
        resetPid();
    }

    // To debug stuff
    // print();
    // printConstants();
    // printThrottle();
    // printGyro();

    // Run the motors with the calculated PID throttle
    runMotors(_gyro.roll(), _gyro.pitch(), _gyro.yaw(), delta_time_seconds);

    savePidErrors(_gyro.roll(), _gyro.pitch(), _gyro.yaw());

    return true;
}

void KlevebrandMaxJetDrone::runMotors(float gyro_roll, float gyro_pitch, float gyro_yaw, float delta_time_seconds)
{
    // Not implemented
}
