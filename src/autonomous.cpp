#include "main.h"
#include "sdlapi/motors.hpp"
#include "sdlapi/robot.hpp"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

pros::Motor leftSide1(1);
pros::Motor leftSide2(2);
pros::Motor flyWheel(6);
pros::Motor intake(7);
pros::Motor rightSide1(9);
pros::Motor rightSide2(10);

void autonomous() {
  sdl::Robot robot;
  sdl::motorgroup leftDrive = *robot.getLeftDrive();
  sdl::motorgroup rightDrive = *robot.getRightDrive();
  leftDrive.add_motor(&leftSide1);
  leftDrive.add_motor(&leftSide2);
  rightDrive.add_motor(&rightSide1);
  rightDrive.add_motor(&rightSide2);
  
}
