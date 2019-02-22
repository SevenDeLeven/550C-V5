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
go(1.90);
go(-0.9);
turnDegrees(-90);
timer.reset();
while (!(getLoadCount() > 1) && timer.getTime() < 2000) {//Wait for 2 seconds or until a ball is loaded

}
intake = 127;
go(1.5);
go(-1.5);
turnDegrees(90);
go(-0.8);
goTime(0.4, -127);
go(0.1);
turnDegrees(-92);
go(0.1);
intake = -127;
while (timer.getTime() < 300) {
  loadShooter();
}
shooter(0);
pros::delay(100);
punchThen(TILTER_TOP_CLOSE); //Position is actually next position after shooting
pros::delay(500);
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
turnDegrees(-4.0);
go(1.6);
go(-1);
turnDegrees(90);
goTime(0.25, -127);
go(2);
turnDegrees(-91);
if (detectLoaded()) { //Second set of shots
  go(-1.0);
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
  go(2.0);
} else {
  intake = -127;
  go(1.0);
}
goTime(0.3, 127);
go(-1.2);
intake = 0;
turnDegrees(90);
intake = 127;
go(2.45);
go(-0.4);
turnDegrees(-90);
intake = -127;
go(0.8);
goTime(0.5, 127);
go(-2.1);
turnDegrees(-90);
go(1.0);
go(-1.0);
timer.reset();
while (!(getLoadCount() > 1) && timer.getTime() < 2000) {//Wait for 2 seconds or until a ball is loaded

}
if (detectLoaded()) {   //Third set of shots
  turnDegrees(90);
  punchThen(TILTER_TOP_CLOSE);
  if (detectLoaded()) {
    while (!readyToFire()) {
      loadShooter();
    }
    shooter(0);
    pros::delay(100);
    punchThen(TILTER_MID_CLOSE);
  }
  turnDegrees(-90);
}
go(-0.9);
goTime(0.4, -127);
go(0.125);
turnDegrees(-90);
go(1.0);
turnDegrees(-90);
goTime(0.25, 127);
go(-3.5);
intake = 0;
