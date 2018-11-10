#include "main.h"
#include "sdlapi/motors.hpp"
#include "sdlapi/timer.hpp"

#define FLYWHEEL_MAX 1
#define FLYWHEEL_MIDDLEFAR 2
#define FLYWHEEL_TOPFAR 3

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	leftSide1.set_reversed(false);
	leftSide2.set_reversed(false);
	rightSide1.set_reversed(false);
	rightSide2.set_reversed(false);
	sdl::motorgroup leftDrive;
	leftDrive.add_motor(&leftSide1);
	leftDrive.add_motor(&leftSide2);
	sdl::motorgroup rightDrive;
	rightDrive.add_motor(&rightSide1);
	rightDrive.add_motor(&rightSide2);
	rightDrive.set_reversed(true);

	launcher.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
	tilter.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);

	int inversed = 1;
	bool directionPressed = false;
	sdl::Timer printTimer;
	while (true) {
		if (printTimer.getTime() > 500) {
			printf("%d\n", tiltPotent.get_value());
			printTimer.reset();
		}
		bool directionCurPressed = master.get_digital(DIGITAL_UP);

		if (directionCurPressed && !directionPressed) {
			inversed *= -1;
		}

		int left = (master.get_analog(ANALOG_LEFT_Y) * inversed) + master.get_analog(ANALOG_LEFT_X);
		int right = (master.get_analog(ANALOG_LEFT_Y) * inversed) - master.get_analog(ANALOG_LEFT_X);
		int intakeSpeed = (((int)master.get_digital(DIGITAL_L1)) - ((int)master.get_digital(DIGITAL_L2))) * 127;
		int tilterSpeed = ((int)master.get_digital(DIGITAL_A) - (int)master.get_digital(DIGITAL_Y)) * 40;
		int launcherSpeed = ((int) master.get_digital(DIGITAL_X)) * 127;

		intake = intakeSpeed;
		tilter = tilterSpeed;
		launcher = launcherSpeed;

		leftDrive.move(left);
		rightDrive.move(right);

		directionPressed = directionCurPressed;
		pros::delay(20);
	}
}
