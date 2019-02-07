// sdl::Timer tiltTimer;
// tilter = -100;
// rightLauncher = 127;
// leftLauncher = 127;
// setFlipTurning(false);
// while (!launchButton.get_value()) {
//
// }
// shooter(0);
// while (tiltTimer.getTime() < 500) {
//
// }
// calibrateTilter();
// tiltTop();
// pros::delay(400);
// while (!readyToFire()) {
//   loadShooter();
// }
// pros::delay(100);
// punch();
// go(-0.15);
// turnDegrees(90);
// goTime(0.25, -127);
// intake = -127;
// go(2.0, 90);
// go(-0.31);
// intake = 0;
// if(autonConfig.park) {
//   turnDegrees(90);
//   goTime(0.15, 127);
//   go(-2.4);
// }

// int firstCalibration = autonTeam == TEAM_BLUE ? 0 : 12;
// sdl::Timer tiltTimer;
// tilter = -100;
// rightLauncher = 127;
// leftLauncher = 127;
// setFlipTurning(true);
// while (!launchButton.get_value()) {
//
// }
// shooter(0);
// while (tiltTimer.getTime() < 500) {
//
// }
// calibrateTilter();
// tiltMid();
// go(0.5);
// turnDegrees(71 + autonConfig.turnOffset);
// while (!readyToFire()) {
//   loadShooter();
// }
// pros::delay(100);
// punch();
// turnDegrees(-71 - autonConfig.turnOffset);
// intake = -127;
// go(1.35);
// go(-0.29);
// intake = 0;
// turnDegrees(-90);
// go(-1.95);

sdl::Timer tiltTimer;
tilter = -100;
rightLauncher = 127;
leftLauncher = 127;
setFlipTurning(true);
while (!launchButton.get_value()) {

}
shooter(0);
while (tiltTimer.getTime() < 500) {

}
calibrateTilter();
tiltMid();
setFlipTurning(true);
intake = -127;
go(1.8);
go(-0.25);
turnDegrees(-90);
goTime(0.2, 127);
go(-2.3);
intake = 0;
