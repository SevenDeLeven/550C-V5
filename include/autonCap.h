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
tiltTop();
pros::delay(500);
punch();
turnDegrees(90);
goTime(0.25, -127);
intake = -127;
go(2.0, 90);
go(-0.75);
turnDegrees(-75);
go(0.1);
punch();
intake = 0;
turnDegrees(110);
intake = 127;
go(sqrt(2)*1);
go(-sqrt(2)*0.5);
intake = 0;
turnDegrees(-135);
goTime(0.5, 127);
go(0.7);
