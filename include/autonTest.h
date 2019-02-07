if (autonConfig.park) {
  turnDegrees(90*(autonConfig.turnOffset));
  intake = 127;
  pros::delay(100);
  intake = 0;
} else {
  go(autonConfig.turnOffset);
  intake = 127;
  pros::delay(100);
  intake = 0;
}
