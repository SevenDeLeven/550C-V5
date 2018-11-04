#include "main.h"
#include "sdlapi/motors.hpp"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor leftSide1(1);
	pros::Motor leftSide2(2);
	pros::Motor rightSide1(8);
	pros::Motor rightSide2(9);
	pros::Motor flyWheel(7);
	pros::Motor intake(6);
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

	bool flyWheelToggle = false;
	bool flyWheelPressed = false;

	while (true) {

		bool flyWheelCurPressed = master.get_digital(DIGITAL_X);
		if (flyWheelCurPressed && !flyWheelPressed) {
			flyWheelToggle = !flyWheelToggle;
		}

		int left = master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X);
		int right = master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X);
		int intakeSpeed = (((int)master.get_digital(DIGITAL_L1)) - ((int)master.get_digital(DIGITAL_L2))) * 127;
		int flyWheelSpeed = flyWheelToggle * -127;
		
		flyWheel.move(flyWheelSpeed);
		intake.move(intakeSpeed);
		leftDrive.move(left);
		rightDrive.move(right);

		flyWheelPressed = flyWheelCurPressed;
		pros::delay(20);
	}
}
