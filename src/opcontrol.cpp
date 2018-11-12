#include "main.h"
#include "sdlapi/motors.hpp"
#include "sdlapi/timer.hpp"

#define FLYWHEEL_MAX 1
#define FLYWHEEL_MIDDLEFAR 2
#define FLYWHEEL_TOPFAR 3

#define FORWARD_AXIS ANALOG_LEFT_Y
#define TURN_AXIS ANALOG_LEFT_X
#define DIRECTION_BUTTON DIGITAL_UP
#define INTAKE_UP_BUTTON DIGITAL_L1
#define INTAKE_DOWN_BUTTON DIGITAL_L2
#define LAUNCHER_BUTTON DIGITAL_X
#define TILTER_TOP_BUTTON DIGITAL_Y
#define TILTER_MID_BUTTON DIGITAL_A

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	calibrateTilter();
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
	bool tilterPressed = false;

	while (true) {
		if (printTimer.getTime() > 500) {
			printf("%d\n", tiltPotent.get_value());
			printTimer.reset();
		}

		bool directionCurPressed = master.get_digital(DIGITAL_UP);

		if (directionCurPressed && !directionPressed) {
			inversed *= -1;
		}

		bool tilterMidPressed = master.get_digital(TILTER_MID_BUTTON);
		bool tilterTopPressed = master.get_digital(TILTER_TOP_BUTTON);

		if (tilterMidPressed && tilterMidPressed != tilterPressed) {
			set_tilter_position(TILTER_MID_CLOSE);
		}

		if (tilterTopPressed && tilterTopPressed != tilterPressed) {
			set_tilter_position(TILTER_TOP_CLOSE);
		}

		int left = (master.get_analog(FORWARD_AXIS) * inversed) + master.get_analog(TURN_AXIS);
		int right = (master.get_analog(FORWARD_AXIS) * inversed) - master.get_analog(TURN_AXIS);
		int intakeSpeed = (((int)master.get_digital(INTAKE_UP_BUTTON)) - ((int)master.get_digital(INTAKE_DOWN_BUTTON))) * 127;
		// int tilterSpeed = ((int)master.get_digital(DIGITAL_A) - (int)master.get_digital(DIGITAL_Y)) * 40;
		int launcherSpeed = ((int) master.get_digital(LAUNCHER_BUTTON)) * 127;

		intake = intakeSpeed;
		// tilter = tilterSpeed;
		launcher = launcherSpeed;

		leftDrive.move(left);
		rightDrive.move(right);

		directionPressed = directionCurPressed;
		tilterPressed = tilterTopPressed || tilterMidPressed;
		pros::delay(20);
	}
}
