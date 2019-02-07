sdl::Timer tiltTimer;
setFlipTurning(false);
tilter = -100;
shooter(127);
while (!launchButton.get_value()) {

}
shooter(0);
while (tiltTimer.getTime() < 500) {

}
calibrateTilter();
tiltMid();
intake = -127;
sdl::Event f_evtList[] = {sdl::Event(slowAfter, sdl::callback_point::DISTANCED, 1.2)};
go(1.80, 127, f_evtList, 1);
go(-1.80);
goTime(0.5, -127);
go(0.2);
turnDegrees(-88);
sdl::Timer timer;
while (timer.getTime() < 300) {
  loadShooter();
}
shooter(0);
pros::delay(100);
punchThen(TILTER_TOP_CLOSE); //Position is actually next position after shooting
if (getLoadCount() > 0) {
  sdl::Timer timer;
  while (!readyToFire()) {
    loadShooter();
  }
  shooter(0);
  pros::delay(100);
  punchThen(TILTER_MID_CLOSE);  //Position is actually next position after shooting
}
turnDegrees(-2);
go(1.8);
goTime(0.5,127);
go(-2);
turnDegrees(45);
intake = 127;
go(sqrt(2)*1.4, 100);
go(-sqrt(2)*0.21);
if (detectLoaded()) {
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
}
go(-sqrt(2)*(1.4-0.21));
intake = 0;
tiltMid();
turnDegrees(-45);
go(-1.0);
turnDegrees(-90);
goTime(0.5, 127);
go(-4.6);
