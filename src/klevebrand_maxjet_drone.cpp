#include "klevebrand_maxjet_drone.h"

void KlevebrandMaxJetDrone::setup()
{
    _processor.setup();

    _processor.print("STARTING DRONE...");

    _gyro.setup();

    pid_repository->setup();

    setupMotors();

    setFlightModeAcro();

    processor->print("DRONE STARTED!");
}

static long last_run_start_micros_timestamp = 0;

void KlevebrandMaxJetDrone::run()
{
    if (delayToKeepFeedbackLoopHz(last_run_start_micros_timestamp) > 0)
    {
        return;
    }

    last_run_start_micros_timestamp = _processor.microsecondsTimestamp();

    // Get the latest data from the gyroscope
    updateGyro();

    if (hasLostConnection())
    {
        // If connection is dead, stop the drone
        resetPid();
        stopMotors();

        // Serial.println("LOST CONNECTION");
    }
    else if (!isMotorsEnabled())
    {
        // If the motors are diabled, stop the drone
        resetPid();
        stopMotors();

        // Serial.println("MOTORS DISABLED");
    }
    else
    {
        // Increment the integral part of the PID loop
        if (throttle > PID_THROTTLE_THRESHOLD)
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
        runMotors(_gyro.roll(), _gyro.pitch(), _gyro.yaw());

        savePidErrors(_gyro.roll(), _gyro.pitch(), _gyro.yaw());

        persistPidConstants();
    }
}

void KlevebrandMaxJetDrone::runMotors(float gyro_roll, float gyro_pitch, float gyro_yaw)
{
    // Not implemented
}
