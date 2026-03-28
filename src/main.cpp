#include "klevebrand_maxjet_drone.h"
#include "pwm_receiver.h"
#include "drone_pwm_receiver.h"

ServoDroneMotor motors[7];

KlevebrandMaxJetDrone drone = KlevebrandMaxJetDrone(motors);
DronePwmReceiver receiver = DronePwmReceiver(1, 4, 3, 2, 7);

void setup()
{
  motors[0].setup(3);
  motors[1].setup(45);
  motors[2].setup(46);
  motors[3].setup(11);
  motors[4].setup(12);
  motors[5].setup(10);
  motors[6].setup(9);

  // Startup the gyroscope and motors
  drone.setup();

  // Startup the reciever
  receiver.setup();
}

void loop()
{
  // Set drone flight values from the receiver
  //receiver.setThrottle(&drone);

  receiver.setRudderAileron(&drone);

  //drone.rudder_left().setSpeed(50);
  //drone.rudder_right().setSpeed(50);
  //drone.aileron_left().setSpeed(50);
  //drone.aileron_right().setSpeed(50);
  //drone.flap_left().setSpeed(50);
  //drone.flap_right().setSpeed(50);

  // Run the drone feedback-loop
  drone.run();
}
