setFlipTurning(false);
pros::Task shooterInitializationTask(initShooter);
intake = -127;
tilter = -70;
go(1.8);
calibrateTilter();
tiltTop();
go(-0.2);
turnDegrees(-57);
punchThen(TILTER_MID_CLOSE); //Position is actually next position after shooting
pros::delay(400);
punchThen(TILTER_TOP_CLOSE);
turnDegrees(90+57);
go(-1.45);
intake = 0;
