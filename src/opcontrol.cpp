#include "main.h"
#include "sdlapi/motors.hpp"
#include "sdlapi/timer.hpp"

#define FLYWHEEL_MAX 1
#define FLYWHEEL_MIDDLEFAR 2
#define FLYWHEEL_TOPFAR 3

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	master.set_text(0,0,"FW: OFF");
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

	bool flyWheelToggle = false;
	bool flyWheelPressed = false;
	int inversed = 1;
	bool directionPressed = false;

	int flyWheelMode = 0;
	bool readyAlertDone = false;
	bool temp_alert = false;
	int flyWheelSpeedUpdate = 0;
	sdl::Timer flyWheelRunTimer;

	while (true) {

		bool flyWheelMaxCurPressed = master.get_digital(DIGITAL_X);
		bool flyWheelFarMiddleCurPressed = master.get_digital(DIGITAL_B);
		bool flyWheelFarTopCurPressed = master.get_digital(DIGITAL_A);
		bool directionCurPressed = master.get_digital(DIGITAL_UP);

		if (!flyWheelPressed && (flyWheelMaxCurPressed || flyWheelFarMiddleCurPressed || flyWheelFarTopCurPressed)) {
			flyWheelRunTimer.reset();
			if (flyWheelMode != 0) {
				flyWheelMode = 0;
				readyAlertDone = false;
				master.set_text(0,0,"FW: OFF   ");
			} else if (flyWheelMaxCurPressed) {
				flyWheelMode = FLYWHEEL_MAX;
				master.set_text(0,0,"FW: MAX   ");
			} else if (flyWheelFarMiddleCurPressed) {
				flyWheelMode = FLYWHEEL_MIDDLEFAR;
				master.set_text(0,0,"FW: MIDFar");
			} else if (flyWheelFarTopCurPressed) {
				flyWheelMode = FLYWHEEL_TOPFAR;
				master.set_text(0,0,"FW: TOPFar");
			}
		}

		if (!temp_alert && flyWheel.get_temperature() > 40) {
			master.set_text(2,0,"WARN: FW HOT");
			master.rumble("--..--");
			temp_alert = true;
		}

		if (directionCurPressed && !directionPressed) {
			inversed *= -1;
		}

		int left = (master.get_analog(ANALOG_LEFT_Y) * inversed) + master.get_analog(ANALOG_LEFT_X);
		int right = (master.get_analog(ANALOG_LEFT_Y) * inversed) - master.get_analog(ANALOG_LEFT_X);
		int intakeSpeed = (((int)master.get_digital(DIGITAL_L1)) - ((int)master.get_digital(DIGITAL_L2))) * 127;
		if (flyWheelMode == 0) {
			flyWheel.move(0);
			readyAlertDone = false;
		} else if (flyWheelMode == FLYWHEEL_MAX) {
			flyWheel.move_velocity(200);
			if (!readyAlertDone && flyWheel.get_actual_velocity() >= 130 && flyWheelRunTimer.getTime() > 500) {
				master.rumble("--");
				readyAlertDone = true;
			}
		} else if (flyWheelMode == FLYWHEEL_TOPFAR) {
			flyWheel.move_velocity(128);
			if (!readyAlertDone && flyWheel.get_actual_velocity() >= 120 && flyWheelRunTimer.getTime() > 500) {
				master.rumble("--");
				readyAlertDone = true;
			}
		} else if (flyWheelMode == FLYWHEEL_MIDDLEFAR) {
			flyWheel.move_velocity(118);
			if (!readyAlertDone && flyWheel.get_actual_velocity() >= 110 && flyWheelRunTimer.getTime() > 500) {
				master.rumble("--");
				readyAlertDone = true;
			}
		}
		flyWheelSpeedUpdate++;
		flyWheelSpeedUpdate%=20;
		if (flyWheelSpeedUpdate == 0) {
			master.print(1,0,"FW RPM: %d   ", (int)flyWheel.get_actual_velocity());
		}

		intake.move(intakeSpeed);
		leftDrive.move(left);
		rightDrive.move(right);

		flyWheelPressed = (flyWheelMaxCurPressed || flyWheelFarMiddleCurPressed || flyWheelFarTopCurPressed);
		directionPressed = directionCurPressed;
		pros::delay(20);
	}
}
