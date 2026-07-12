#include <receivers/pwm_receiver_controller.h>

#include "klevebrand_maxjet_drone.h"

static auto receiver = PwmReceiverController(1, 4, 3, 2, 7);

static ServoDroneMotor motors[7];
static constexpr int motor_pins[7] = {5, 45, 46, 12, 11, 10, 9};

static KlevebrandMaxJetDrone drone(motors, motor_pins);

void setup()
{
    drone.setup();
    PwmReceiverController::setup();
}

void loop()
{
    receiver.apply(&drone);
    drone.run();
}
