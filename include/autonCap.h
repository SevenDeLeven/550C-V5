initShooter();
shooter(0);
intake = -127;
go(1.8);
go(-0.8);
turnDegrees(90);
go(1.0);
turnDegrees(-90);
intake = 127;
go(1.0, 90);
go(-0.5);
turnDegrees(90);
go(-0.5);
turnDegrees(-154);
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
turnDegrees(154);
go(-1.9);
intake = 0;
