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
#define FIX_BUTTON DIGITAL_LEFT

bool doubleShooting = false;
pros::Controller* controller;
void doubleFire() {
	doubleShooting = true;
}

void tiltMid() {
	set_tilter_position(TILTER_MID_CLOSE);
}

void tiltTop() {
	set_tilter_position(TILTER_TOP_CLOSE);
}

bool detectLoaded() {
	return loadSonar.get_value() <= 135;
}

bool readyToFire() {
	return detectLoaded() && loadSonar.get_value() >= 115;
}

int getLoadCount() {
	int loadSonarValue = loadSonar.get_value();
	return loadSonarValue <= 50 ? 2 : (loadSonarValue <= 135 ? 1 : 0);
}

void f_doubleFire(void*) {
	sdl::Timer waitTimer;
	while (true) {
		while (!doubleShooting) {pros::Task::delay(20);}
		int totalLoad = getLoadCount();
		bool shouldContinue = true;
		intake = -127;
		tiltMid();
		waitTimer.reset();
		while (waitTimer.getTime() < 500) {
			if (!controller->get_digital(DOUBLEFIRE_BUTTON)) {
				shouldContinue = false;
				break;
			}
		}
		if (!shouldContinue) {
			doubleShooting = false;
			continue;
		}
		shooter(127);

		//Launch ball (500ms)
		waitTimer.reset();
		while (waitTimer.getTime() < 500) {
			if (!controller->get_digital(DOUBLEFIRE_BUTTON)) {
				shouldContinue = false;
				break;
			}
		}
		if (!shouldContinue) {
			doubleShooting = false;
			continue;
		}

		tiltTop();
		//Load ball
		while (!launchButton.get_value()) {
			if (!controller->get_digital(DOUBLEFIRE_BUTTON)) {
				shouldContinue = false;
				break;
			}
		}

		if (!shouldContinue) {
			doubleShooting = false;
			continue;
		}

		//Launch (500ms)
		shooter(127);

		waitTimer.reset();
		while (waitTimer.getTime() < 500) {
			if (!controller->get_digital(DOUBLEFIRE_BUTTON)) {
				shouldContinue = false;
				break;
			}
		}
		intake = 0;
		shooter(0);
		doubleShooting = false;
	}
}



void punch() {
	shooter(127);
	pros::delay(500);
	while (launchButton.get_value() != 1) {

	}
	shooter(0);
}

void punchThen(int nextPosition) {
	shooter(127);
	pros::delay(500);
	set_tilter_position(nextPosition);
	while (launchButton.get_value() != 1) {

	}
	shooter(0);
}

void loadShooter() {
	if (!launchButton.get_value()) {
		shooter(127);
	} else {
		shooter(0);
	}
}

void shooter(int speed) {
	leftLauncher = speed;
	rightLauncher = speed;
	if (speed == 0) {
		leftLauncher.move_velocity(0);
		leftLauncher.set_brake_mode(MOTOR_BRAKE_HOLD);
		rightLauncher.move_velocity(0);
		rightLauncher.set_brake_mode(MOTOR_BRAKE_HOLD);
	}
}


void calibrateTilter() {
  tilter.tare_position();
}

void set_tilter_position(int position) {
  tilter.move_absolute(position, 200);
}
float getAcc() {
	return accelerometer.get_value();
}

float getGyro() {
	double gyro1Val = gyro1.getValue();
	double gyro2Val = gyro2.getValue();
	return (gyro1Val + gyro2Val)/20.0f;
}

double getGyroDifference(double target) {
	double gyroVal = getGyro();
	double gyroDifference = gyroVal-target;
	return gyroDifference;
}

void resetGyro() {
	gyro1.reset();
	gyro2.reset();
}

void opcontrol() {
	#ifdef DEBUG_INIT
	competition_initialize();
	#endif
	controller = new pros::Controller(pros::E_CONTROLLER_MASTER);
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

	leftSide1.set_reversed(true);
	rightSide1.set_reversed(true);

	shooter(0);
	tilter.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);

	int inversed = 1;
	bool doubleFirePressed = false;
	bool directionPressed = false;
	bool tilterPressed = false;
	bool debugPressed = false;
	bool firePressed = false;
	bool debugMode = false;

	sdl::Timer launchTimer;
	sdl::Timer debugTimer;

	launchTimer.add(-1000);
	pros::Task doubleFireTask(f_doubleFire);
	int tilterCalibrationStage = 0;
	bool tilterCalibrated = false;
	sdl::Timer calibrationTimer;
	tilter = -100;
	controller->print(0,3,"550C-V5");
	calibrationTimer.reset();
	while (true) {
		if (debugTimer.getTime() >= 1000) {
			printf("Load Count: %d\n", getLoadCount());
			printf("loadSonar value: %d\n", loadSonar.get_value());
			printf("gyro value: %f\n", getGyro());
			int loadSonarValue = (getLoadCount() * 7);
			std::string loadBar = "";
			for (int i = 0; i < 13; i++) {
				loadBar += i < loadSonarValue ? "O" : " ";
			}
			// controller->clear_line(0);
			controller->print(1, 0, "%s", loadBar);
			debugTimer.reset();
		}
		if (tilterCalibrationStage == 0 && calibrationTimer.getTime() >= 750) {
			tilterCalibrationStage = 1;
			tilter = -40;
		}
		if (tilterCalibrationStage == 1 && calibrationTimer.getTime() >= 900) {
			tilterCalibrationStage = 2;
			tilter = 0;
		}
		if (tilterCalibrationStage == 2 && calibrationTimer.getTime() >= 1000) {
			tilterCalibrationStage = 3;
			tilterCalibrated = true;
			calibrateTilter();
			tiltMid();
		}

		bool directionCurPressed = controller->get_digital(DIRECTION_BUTTON);
		bool debugCurPressed = controller->get_digital(DEBUG_BUTTON);
		bool doubleFireCurPressed = controller->get_digital(DOUBLEFIRE_BUTTON);

		if (directionCurPressed && !directionPressed) {
			inversed *= -1;
		}


		bool fireCurPressed = controller->get_digital(LAUNCHER_BUTTON);
		if (fireCurPressed && !firePressed && tilterCalibrated) {
			launchTimer.reset();
		}

		if (debugCurPressed != debugPressed && debugCurPressed) {
			debugMode = !debugMode;
		}

		bool tilterMidPressed = controller->get_digital(TILTER_MID_BUTTON);
		bool tilterTopPressed = controller->get_digital(TILTER_TOP_BUTTON);

		int left = (controller->get_analog(FORWARD_AXIS) * inversed) + controller->get_analog(TURN_AXIS);
		int right = (controller->get_analog(FORWARD_AXIS) * inversed) - controller->get_analog(TURN_AXIS);
		int intakeSpeed = (((int)controller->get_digital(INTAKE_UP_BUTTON)) - ((int)controller->get_digital(INTAKE_DOWN_BUTTON))) * 127;
		//int armSpeed = (((int)controller->get_digital(ARM_UP_BUTTON)) - ((int)controller->get_digital(ARM_DOWN_BUTTON))) * 127;
		//int tilterSpeed = ((int)controller->get_digital(DIGITAL_A) - (int)controller->get_digital(DIGITAL_Y)) * 40;
		int launcherSpeed = ((int) ((launchTimer.getTime() < 500 || !launchButton.get_value())) && !controller->get_digital(FIX_BUTTON)) * 127 - ((int)(controller->get_digital(FIX_BUTTON))*127);

		//tilter = tilterSpeed;
		if (!doubleShooting && tilterCalibrated) {
			/* READ WHEN TILTER IS CALIBRATED */
			if (tilterMidPressed && tilterMidPressed != tilterPressed) {
				tiltMid();
			}
			if (tilterTopPressed && tilterTopPressed != tilterPressed) {
				tiltTop();
			}
			if (doubleFireCurPressed && doubleFireCurPressed != doubleFirePressed) {
				doubleFire();
			}

			shooter(launcherSpeed);
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
