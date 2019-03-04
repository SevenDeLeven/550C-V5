sdl::Timer tiltTimer;
sdl::Timer timer;

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
sdl::Event evt_arr[] = {sdl::Event(slowAfter, sdl::callback_point::DISTANCED, 1.5)};
go(1.8, 127, evt_arr, 2);
intake = 20;
go(0.35);
intake = -127;
go(-1.25);
turnDegrees(-90);
timer.reset();
while (!(getLoadCount() > 1) && timer.getTime() < 1000) { //Wait for 1 second or until a ball is loaded

}
intake = 90;
go(1.5);
go(-1.5);
turnDegrees(90);
go(-0.8);
goTime(0.5, -127);
go(0.2);
turnDegrees(-90);
intake = -127;
while (timer.getTime() < 300) {
  loadShooter();
}
shooter(0);
pros::delay(100);
punchThen(TILTER_TOP_CLOSE); //Position is actually next position after shooting
pros::delay(400);
if (detectLoaded()) {   //First set of shots
  sdl::Timer timer;
  while (!readyToFire()) {
    loadShooter();
  }
  shooter(0);
  pros::delay(100);
  punchThen(TILTER_MID_CLOSE);  //Position is actually next position after shooting
}
tiltMid();
go(0.75);          //ADVANCED Maneuver technique (taken from Thomas)
turnDegrees(-12, 90);
go(1.0);
go(-1);
turnDegrees(90);
goTime(0.5, -127);
go(2.1);
turnDegrees(-91);
if (detectLoaded()) { //Second set of shots
  go(-0.95);
  turnDegrees(3);
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
  turnDegrees(-3);
  go(1.85);
} else {
  intake = -127;
  go(0.8);
}
goTime(0.5, 127);
go(-1.2);
intake = 0;
turnDegrees(90);
intake = 90;
go(2.45);
go(-0.65);
turnDegrees(-90);
intake = -127;
go(0.7);
goTime(0.5, 127);
go(-2.2);
turnDegrees(-90);
go(1.0);
go(-1.1);
timer.reset();
while (!(getLoadCount() > 1) && timer.getTime() < 1000) {//Wait for 1 second or until a ball is loaded

}
if (detectLoaded()) {   //Third set of shots
  turnDegrees(93);
  go(0.15);
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
  go(-0.15);
  turnDegrees(-93);
}
go(-0.9);
goTime(0.4, -127);
go(0.2);
turnDegrees(-90);
go(1);
turnDegrees(-90);
goTime(0.4, 127);
go(-3.5);
intake = 0;
