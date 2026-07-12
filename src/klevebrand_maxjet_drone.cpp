#include "klevebrand_maxjet_drone.h"

#include "drone_components/flight_mode_none_local.h"

KlevebrandMaxJetDrone::KlevebrandMaxJetDrone(ServoDroneMotor* motors, const int motor_pins[motor_pin_count])
    : MaxJetDroneBase(500, 200, gyro_reset_pin), _motors(motors)
{
    for (int i = 0; i < motor_pin_count; i++)
    {
        _motor_pins[i] = motor_pins[i];
    }
}

void KlevebrandMaxJetDrone::setup()
{
    processor.setup();

    processor.print("STARTING DRONE...");

    position.setup();

    gyro.setup();

    setupMotors();

    static auto none_flight_mode = FlightModeNoneLocal();
    activateControlMode(&none_flight_mode);

    processor.print("DRONE STARTED!");
}

static unsigned long last_run_start_microseconds_timestamp = 0;
static unsigned long last_gyro_fetch_duration = 0;

bool KlevebrandMaxJetDrone::run()
{
    if (delayToKeepFeedbackLoopHz(last_run_start_microseconds_timestamp - last_gyro_fetch_duration) > 0)
    {
        position.run(false);

        return false;
    }

    const unsigned long current_time = timestampMicroseconds();
    const unsigned long delta_time = current_time - last_run_start_microseconds_timestamp;
    const float delta_time_seconds = delta_time / 1000000.0f;
    last_run_start_microseconds_timestamp = current_time;

    (void)updateGyro();

    last_gyro_fetch_duration = timestampMicroseconds() - current_time;

    position.run(true);

    const float gyro_roll = getRoll();
    const float gyro_pitch = getPitch();
    const float gyro_yaw = getYaw();

    if (getThrottle() > AirplaneVtailPid::PID_THROTTLE_THRESHOLD)
    {
        runPidOptimizer(processor.millisecondsTimestamp());
        calculatePidIntegral(gyro_roll, gyro_pitch, gyro_yaw, delta_time_seconds);
    }
    else
    {
        resetPid();
    }

    runMotors(gyro_roll, gyro_pitch, gyro_yaw, delta_time_seconds);

    savePidErrors(gyro_roll, gyro_pitch, gyro_yaw);

    return true;
}

void KlevebrandMaxJetDrone::setupMotors()
{
    for (int i = 0; i < motor_pin_count; i++)
    {
        if (_motor_pins[i] != -1)
        {
            _motors[i].setup(_motor_pins[i]);
        }
    }

    stopMotors();

    delay(1000);
}

void KlevebrandMaxJetDrone::stopMotors()
{
    motor().setSpeed(0);
    aileronLeft().setSpeed(0);
    aileronRight().setSpeed(0);
    rudderLeft().setSpeed(0);
    rudderRight().setSpeed(0);
    flapLeft().setSpeed(0);
    flapRight().setSpeed(0);
}

void KlevebrandMaxJetDrone::runMotors(const float gyro_roll, const float gyro_pitch, const float gyro_yaw,
                                      const float delta_time_seconds)
{
    (void)gyro_roll;
    (void)gyro_pitch;
    (void)gyro_yaw;
    (void)delta_time_seconds;
}

void KlevebrandMaxJetDrone::attachMotors() const
{
    motor().attach();
    aileronLeft().attach();
    aileronRight().attach();
    rudderLeft().attach();
    rudderRight().attach();
    flapLeft().attach();
    flapRight().attach();
}

void KlevebrandMaxJetDrone::detachMotors() const
{
    motor().detach();
    aileronLeft().detach();
    aileronRight().detach();
    rudderLeft().detach();
    rudderRight().detach();
    flapLeft().detach();
    flapRight().detach();
}

void KlevebrandMaxJetDrone::enableMotors()
{
    attachMotors();
    MaxJetDroneBase::enableMotors();
}

void KlevebrandMaxJetDrone::disableMotors()
{
    Serial.println("DISABLING MOTORS");
    setThrottle(0);
    stopMotors();
    resetPid();
    MaxJetDroneBase::disableMotors();
    detachMotors();
}
