#include <receivers/pwm_receiver_controller.h>

#include "klevebrand_maxjet_drone.h"

static auto receiver = PwmReceiverController(1, 4, 3, 2, 7);

static ServoDroneMotor motors[7];
static constexpr int motor_pins[7] = {2, 3, 6, 7, -1, -1, -1};

static KlevebrandMaxJetDrone drone(motors, motor_pins);

void setup()
{
  drone.motor().setup(5);
  motors[1].setup(45);
  motors[2].setup(46);
  motors[3].setup(12);
  motors[4].setup(11);
  motors[5].setup(10);
  motors[6].setup(9);

  drone.motor().setSpeed(0);

  // Startup the gyroscope and motors
  drone.setup();

  // Startup the reciever
  PwmReceiverController::setup();
}

void loop()
{
  // Set drone flight values from the receiver
  receiver.apply(&drone);

  // Run the drone feedback-loop
  drone.run();
}
