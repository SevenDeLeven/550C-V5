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
go(1.75, 90);
intake = -127;
go(-1.75);
goTime(0.5, -127);
go(0.05);
turnDegrees(-90);
go(0.35);
turnDegrees(-8);
punch();
tiltTop();
pros::delay(500);
punch();
tiltMid();
turnDegrees(-12);
go(1.8);
goTime(0.5,127);
go(-2.2);
turnDegrees(45);
intake = 110;
go(sqrt(2)*1.5, 90);
go(-sqrt(2)*0.5);
intake = -127;
punch();
tiltTop();
pros::delay(500);
punch();
intake = 0;
