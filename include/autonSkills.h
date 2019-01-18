sdl::Timer tiltTimer;
tilter = -100;
launcher1 = 127;
launcher2 = 127;
while (!launchButton.get_value()) {

}
launcher1.move_velocity(0);
launcher2.move_velocity(0);
launcher1.set_brake_mode(MOTOR_BRAKE_HOLD);
launcher2.set_brake_mode(MOTOR_BRAKE_HOLD);
while (tiltTimer.getTime() < 500) {

}
calibrateTilter();
tiltMid();
intake = -127;
go(2.0);
go(-1.2);
turnDegrees(-90);
pros::delay(250);
intake = 127;
go(1.5);
intake = -127;
go(-1.25);
turnDegrees(-90);
go(1.0);
goTime(0.5, 127);
go(-0.4);
turnDegrees(90);
if (getLoadCount() == 1) {
  punch();
} else if (getLoadCount() == 2) {
  punch();
  tiltTop();
  turnDegrees(-6);
  punch();
  turnDegrees(6);
}
tiltMid();
turnDegrees(-13);
go(2.0);
goTime(0.5, 127);
go(-1.1);
turnDegrees(90);
goTime(0.5, -127);
go(2.0);
turnDegrees(-90);
if (getLoadCount() > 0) {
  go(-0.8);
  turnDegrees(15);
  if (getLoadCount() == 1) {
    punch();
  } if (getLoadCount() > 0) {
    punch();
    tiltTop();
    pros::delay(500);
    punch();
    tiltMid();
  }
  turnDegrees(-15);
  go(0.8);
}
intake = -127;
goTime(1.0, 127);
go(-1.2);
intake = 0;
intake = 0;
