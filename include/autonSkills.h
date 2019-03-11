sdl::Timer tiltTimer;
sdl::Timer timer;

setFlipTurning(false);
tilter = -70;
intake = -127;
sdl::Event evt_arr[] = {sdl::Event(slowAfter, sdl::callback_point::DISTANCED, 1.5)};
go(1.8, 127, evt_arr, 2);
calibrateTilter();
tiltMid();
intake = 0;
go(0.35);
intake = -127;
go(-2.25);
goTime(0.5, -127);
go(0.2);
turnDegrees(-89);
go(0.15);
intake = -127;
punchThen(TILTER_TOP_CLOSE);
pros::delay(200);
punchThen(TILTER_MID_CLOSE);
turnDegrees(-3, 60);
go(0.9);
turnDegrees(-7, 60);
go(0.85);
go(-1.75);
turnDegrees(93);
goTime(0.5, -127);
go(1.0);
turnDegrees(-90);
intake = 127;
go(1.0);
go(-1.0);
intake = -127;
turnDegrees(90);
go(1.1);
turnDegrees(-90);
goTime(0.7, -80);
go(0.4);
if (getLoadCount() > 0) { //Second set of shots
  turnDegrees(5, 60);
  intake = -127;
  punchThen(TILTER_TOP_CLOSE);
  if (detectLoaded()) {
    while (!readyToFire()) {
      loadShooter();
    }
    shooter(0);
    pros::delay(100);
    punch();
  }
  tiltMid();
  turnDegrees(-6, 60);
}
go(1.7);
goTime(0.5, 127);
go(-1.2);
intake = 0;
turnDegrees(90);
intake = 90;
sdl::Event evt_arr2[] = {sdl::Event(stopIntake, sdl::callback_point::DISTANCED, 2.1)};
go(2.45, 127, evt_arr2, 1);
go(-0.5);
turnDegrees(-90);
intake = -127;
go(0.7);
goTime(0.5, 127);
go(-2.2);
turnDegrees(-90);
if (getLoadCount() == 2) {
  intake = 127;
}
go(1.0);
go(-1.0);
timer.reset();
while (!(getLoadCount() > 1) && timer.getTime() < 1000) { //Wait for 1 second or until a ball is loaded

}
if (detectLoaded()) {   //Third set of shots
  turnDegrees(93);
  go(0.1);
  punchThen(TILTER_TOP_CLOSE);
  if (detectLoaded()) {
    while (!readyToFire()) {
      loadShooter();
    }
    shooter(0);
    pros::delay(100);
    punchThen(TILTER_MID_CLOSE);
  }
  tiltMid();
  turnDegrees(-93);
}
go(-0.9);
goTime(0.4, -127);
go(0.2);
turnDegrees(-90);
go(0.9);
turnDegrees(-90);
goTime(0.4, 127);
go(-0.7,90);
go(-3.0);
intake = 0;
