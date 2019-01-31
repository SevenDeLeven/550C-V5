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
intake = -100;
sdl::Event f_evtList[] = {sdl::Event(slowAfter, sdl::callback_point::DISTANCED, 1.0)};
go(1.75, 127, f_evtList, 1);
intake = -127;
go(-1.75);
goTime(0.5, -127);
go(0.2);
turnDegrees(-85);
punch();
if (getLoadCount() > 0) {

}
go(-0.3);
tiltTop();
sdl::Timer timer;
while (!detectLoaded()) {
  if (timer.getTime() >= 500) {
    turnDegrees(60);
    turnDegrees(-60);
    timer.reset();
  }
}
pros::delay(300);
punch();
tiltMid();
turnDegrees(-8);
go(2.0);
goTime(0.5,127);
go(-2.05);
turnDegrees(45);
intake = 127;
go(sqrt(2)*1.2, 100);
go(-sqrt(2)*0.2);
turnDegrees(-2);
intake = -127;
punch();
tiltTop();
pros::delay(500);
punch();
intake = 0;
