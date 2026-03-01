#include "klevebrand_maxjet_drone.h"
#include "pwm_receiver.h"
#include "drone_pwm_receiver.h"

ServoDroneMotor motors[6];

KlevebrandMaxJetDrone drone = KlevebrandMaxJetDrone(motors);
DronePwmReceiver receiver = DronePwmReceiver(1, 4, 3, 2, 7);

void setup()
{
  motors[0].setup(3);
  motors[1].setup(2);
  motors[2].setup(7);
  motors[3].setup(6);
  motors[3].setup(6);
  motors[3].setup(6);
  motors[3].setup(6);

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
