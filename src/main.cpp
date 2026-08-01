#include <receivers/pwm_receiver_controller.h>

#include "klevebrand_maxjet_drone.h"

static constexpr int GPIO_1 = 5;
static constexpr int GPIO_2 = 8;
static constexpr int GPIO_3 = 9;
static constexpr int GPIO_4 = 10;
static constexpr int GPIO_5 = 11;
static constexpr int GPIO_6 = 12;
static constexpr int GPIO_7 = 46;
static constexpr int GPIO_8 = 45;

static auto receiver = PwmReceiverController(1, 4, 3, 2, 7);

static ServoDroneMotor motors[7];
static constexpr int motor_pins[7] = {GPIO_1, GPIO_8, GPIO_7, GPIO_6, GPIO_5, GPIO_4, GPIO_3};

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
