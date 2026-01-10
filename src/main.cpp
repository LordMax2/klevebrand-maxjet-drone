#include "klevebrand_maxjet_drone.h"
#include "pwm_receiver.h"
#include "./components/drone_pwm_receiver/drone_pwm_receiver.h"

uint8_t motor_pin_numbers[16] = { 3, 2, 7, 6};

KlevebrandMaxJetDrone drone = KlevebrandMaxJetDrone(motor_pin_numbers);
DronePwmReceiver receiver = DronePwmReceiver(1, 4, 3, 2, 7);

void setup()
{
  // Startup the gyroscope and motors
  drone.setup();

  // Startup the reciever
  receiver.setup();
}

void loop()
{
  // Set drone flight values from the receiver
  receiver.setThrottle(&drone);

  receiver.setRudderAileron(&drone);

  // Run the drone feedback-loop
  drone.run();
}
