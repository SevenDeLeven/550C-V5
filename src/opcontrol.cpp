#include "main.h"
#include "vars.h"
#include "sdlapi/motors.hpp"
#include "sdlapi/timer.hpp"
#include <vector>

#define SHOOT_TIME 3000

#define FORWARD_AXIS ANALOG_LEFT_Y
#define TURN_AXIS ANALOG_LEFT_X
#define DIRECTION_BUTTON DIGITAL_UP
#define INTAKE_UP_BUTTON DIGITAL_L1
#define INTAKE_DOWN_BUTTON DIGITAL_L2
#define ARM_UP_BUTTON DIGITAL_R1
#define ARM_DOWN_BUTTON DIGITAL_R2
#define LAUNCHER_BUTTON DIGITAL_X
#define TILTER_TOP_BUTTON DIGITAL_Y
#define TILTER_MID_BUTTON DIGITAL_A
#define DEBUG_BUTTON DIGITAL_RIGHT
#define DOUBLEFIRE_BUTTON DIGITAL_B


sdl::Timer doubleLaunchTimer;

void doubleFire() {
	doubleLaunchTimer.reset();
}

void tiltMid() {
	set_tilter_position(TILTER_MID_CLOSE);
}

void tiltTop() {
	set_tilter_position(TILTER_TOP_CLOSE);
}

void f_doubleFire(void*) {
	while (true) {
		while (doubleLaunchTimer.getTime() >= SHOOT_TIME) {pros::Task::delay(20);}
		intake = -127;
		tiltMid();
		pros::delay(500);
		launcher1 = 127;
		launcher2 = 127;
		pros::delay(500);
		tiltTop();
		pros::delay(2000);
		intake = 0;
		launcher1 = 0;
		launcher2 = 0;
	}
}
void punch() {
	launcher1 = 127;
	launcher2 = 127;
	pros::delay(1000);
	while (launchButton.get_value() != 1) {

	}
	launcher1 = 0;
	launcher1.set_brake_mode(MOTOR_BRAKE_HOLD);
	launcher2 = 0;
	launcher2.set_brake_mode(MOTOR_BRAKE_HOLD);
}
void calibrateTilter() {
  tilter.tare_position();
}

void set_tilter_position(int position) {
  tilter.move_absolute(position, 200);
}

void opcontrol() {
	pros::Controller controller(pros::E_CONTROLLER_MASTER);
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

	launcher1.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
	launcher2.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
	tilter.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);

	int inversed = 1;
	bool doubleFirePressed = false;
	bool directionPressed = false;
	bool tilterPressed = false;
	bool debugPressed = false;
	bool firePressed = false;
	bool debugMode = false;
	sdl::Timer launchTimer;
	launchTimer.add(-1000);
	doubleLaunchTimer.reset();
	doubleLaunchTimer.add(-SHOOT_TIME);
	pros::Task doubleFireTask(f_doubleFire);
	bool tilterCalibrated = false;
	sdl::Timer calibrationTimer;
	tilter = -100;
	while (true) {

		if (!tilterCalibrated && calibrationTimer.getTime() >= 500) {
			tilterCalibrated = true;
			calibrateTilter();
			tiltMid();
		}

		bool directionCurPressed = controller.get_digital(DIRECTION_BUTTON);
		bool debugCurPressed = controller.get_digital(DEBUG_BUTTON);
		bool doubleFireCurPressed = controller.get_digital(DOUBLEFIRE_BUTTON);

		if (directionCurPressed && !directionPressed) {
			inversed *= -1;
		}


		bool fireCurPressed = controller.get_digital(LAUNCHER_BUTTON);
		if (fireCurPressed && !firePressed && tilterCalibrated) {
			launchTimer.reset();
		}

		if (debugCurPressed != debugPressed && debugCurPressed) {
			debugMode = !debugMode;
		}

		bool tilterMidPressed = controller.get_digital(TILTER_MID_BUTTON);
		bool tilterTopPressed = controller.get_digital(TILTER_TOP_BUTTON);

		if (doubleLaunchTimer.getTime() >= SHOOT_TIME && tilterCalibrated) {
			/* READ WHEN TILTER IS CALIBRATED */
			if (tilterMidPressed && tilterMidPressed != tilterPressed) {
				tiltMid();
			}
			if (tilterTopPressed && tilterTopPressed != tilterPressed) {
				tiltTop();
			}
			if (doubleFirePressed && doubleFireCurPressed != doubleFirePressed) {
				doubleFire();
			}
		}



		int left = (controller.get_analog(FORWARD_AXIS) * inversed) + controller.get_analog(TURN_AXIS);
		int right = (controller.get_analog(FORWARD_AXIS) * inversed) - controller.get_analog(TURN_AXIS);
		int intakeSpeed = (((int)controller.get_digital(INTAKE_UP_BUTTON)) - ((int)controller.get_digital(INTAKE_DOWN_BUTTON))) * 127;
		//int armSpeed = (((int)controller.get_digital(ARM_UP_BUTTON)) - ((int)controller.get_digital(ARM_DOWN_BUTTON))) * 127;
		//int tilterSpeed = ((int)controller.get_digital(DIGITAL_A) - (int)controller.get_digital(DIGITAL_Y)) * 40;
		int launcherSpeed = ((int) (launchTimer.getTime() < 1000 || !launchButton.get_value())) * 127;

		//tilter = tilterSpeed;
		if (doubleLaunchTimer.getTime() >= SHOOT_TIME && tilterCalibrated) {
			launcher1 = launcherSpeed;
			launcher2 = launcherSpeed;
			if (launcherSpeed == 0) {
				launcher1.set_brake_mode(MOTOR_BRAKE_HOLD);
				launcher2.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
			intake = intakeSpeed;
		}

		leftDrive.move(left);
		rightDrive.move(right);

		directionPressed = directionCurPressed;
		debugPressed = debugCurPressed;
		tilterPressed = tilterTopPressed || tilterMidPressed;
		firePressed = fireCurPressed;
		doubleFirePressed = doubleFireCurPressed;
		pros::Task::delay(20);
	}
}
