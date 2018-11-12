#include "main.h"
#include "sdlapi/motors.hpp"
#include "sdlapi/timer.hpp"
#define THRESHOLD 80
#define MINVEL 18
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

double ticksPerTile = 720*(900.0/392.0);
double ticksPerRevolution = 1470*(900.0/392.0);

 sdl::motorgroup leftDrive;
 sdl::motorgroup rightDrive;


 void calibrateTilter() {
   tiltOffset = (tiltPotent.get_value()/TILTERRATIO) - tilter.get_position();
 }

 void set_tilter_position(int position) {
   double tiltDistance = tiltOffset + (position/TILTERRATIO);
   tilter.move_absolute(tiltDistance, 100);
 }

 void go(double tiles, double maxVel) {
   double distance = tiles*ticksPerTile;
   sdl::Timer timer;
   leftDrive.reset_position();
   rightDrive.reset_position();
 	 int direction = 1;
   if (distance < 0) {
   	direction *= -1;
   	distance = abs(distance);
   }

 	bool clearedTimer = false;
 	while (true) {
 		double leftDistance = abs(leftDrive.get_position());
 		double rightDistance = abs(rightDrive.get_position());
 		double leftDifference = distance-leftDistance;
 		double rightDifference = distance-rightDistance;
 		std::int32_t leftSpeed = (maxVel) * (leftDifference < 800 ? (leftDifference/800.0) : 1);
 		std::int32_t rightSpeed = (maxVel) * (rightDifference < 800 ? (rightDifference/800.0) : 1);
    if ((leftDifference) > THRESHOLD) {
      leftSpeed = abs(leftSpeed) < MINVEL ? (leftSpeed < 0 ? -MINVEL : MINVEL) : leftSpeed;
    }
    if (abs(rightDifference) > THRESHOLD) {
      rightSpeed = abs(rightSpeed) < MINVEL ? (rightSpeed < 0 ? -MINVEL : MINVEL) : rightSpeed;
    }
    if (leftDistance != 0 && rightDistance != 0) {
      leftSpeed *= rightDistance/leftDistance;
      rightSpeed *= leftDistance/rightDistance;
    }
 		leftDrive.move(leftSpeed*direction);
 		rightDrive.move(rightSpeed*direction);
 		if (clearedTimer && !((abs(leftDifference) <= THRESHOLD && abs(rightDifference) <= THRESHOLD))) {
 			clearedTimer = false;
 		}
 		if ((clearedTimer && timer.getTime() >= 100)) {
 			leftDrive.move(0);
       rightDrive.move(0);
 			return;
 		}
 		if ((abs(leftDifference) <= THRESHOLD && abs(rightDifference) <= THRESHOLD && !clearedTimer)) {
 			clearedTimer = true;
 			timer.reset();
 		}
 	}
 }
 void go(double tiles) {
   go(tiles, 127);
 }
 void goConstVel(double tiles, double vel) {
   double distance = tiles*ticksPerTile;
   leftDrive.reset_position();
   rightDrive.reset_position();
 	int direction = 1;
   if (distance < 0) {
   	direction *= -1;
   	distance = abs(distance);
   }
 	while (true) {
 		double leftDistance = abs(leftDrive.get_position());
 		double rightDistance = abs(rightDrive.get_position());
 		double leftDifference = distance-leftDistance;
 		double rightDifference = distance-rightDistance;
 		leftDrive.move_velocity(vel*direction);
 		rightDrive.move_velocity(vel*direction);
 		if ((abs(leftDifference) <= 10 && abs(rightDifference) <= 10)) {
       leftDrive.move(0);
       rightDrive.move(0);
 			return;
 		}
 	}
 }

 void goTime(double time, double vel) {
   leftDrive.move(vel);
   rightDrive.move(vel);
   pros::delay(time*1000);
   leftDrive.move(0);
   rightDrive.move(0);
 }

 void turnDegrees(double degrees, double maxVel) {
   double distance = (degrees/360.0)*ticksPerRevolution;
   sdl::Timer timer;
   leftDrive.reset_position();
   rightDrive.reset_position();
 	int direction = 1;
   if (distance < 0) {
   	direction *= -1;
   	distance = abs(distance);
   }

 	bool clearedTimer = false;
 	while (true) {
 		double leftDistance = abs(leftDrive.get_position());
 		double rightDistance = abs(rightDrive.get_position());
 		double leftDifference = distance-leftDistance;
 		double rightDifference = distance-rightDistance;
 		std::int32_t leftSpeed = (maxVel) * (leftDifference < 200 ? (leftDifference/200.0) : 1);
 		std::int32_t rightSpeed = (maxVel) * (rightDifference < 200 ? (rightDifference/200.0) : 1);
     if (leftDifference > THRESHOLD) {
       leftSpeed = abs(leftSpeed) < MINVEL ? (leftSpeed < 0 ? -MINVEL : MINVEL) : leftSpeed;
     }
     if (abs(rightDifference) > THRESHOLD) {
       rightSpeed = abs(rightSpeed) < MINVEL ? (rightSpeed < 0 ? -MINVEL : MINVEL) : rightSpeed;
     }
     if (leftDistance != 0 && rightDistance != 0) {
       leftSpeed *= rightDistance/leftDistance;
       rightSpeed *= leftDistance/rightDistance;
     }
 		leftDrive.move(leftSpeed*direction*-1);
 		rightDrive.move(rightSpeed*direction);
 		if (clearedTimer && !((abs(leftDifference) <= THRESHOLD && abs(rightDifference) <= THRESHOLD))) {
 			clearedTimer = false;
 		}
 		if ((clearedTimer && timer.getTime() >= 100)) {
 			leftDrive.move(0);
       rightDrive.move(0);
 			return;
 		}
 		if ((abs(leftDifference) <= THRESHOLD && abs(rightDifference) <= THRESHOLD && !clearedTimer)) {
 			clearedTimer = true;
 			timer.reset();
 		}
 	}
 }

  void turnDegrees(double degrees) {
    turnDegrees(degrees, 127);
  }

void autonomous() {
  calibrateTilter();
  // pros::motor_pid_s_t velPid = pros::Motor::convert_pid(10,10,10,10);
  // leftSide1.set_vel_pid(velPid);
  // leftSide2.set_vel_pid(velPid);
  // rightSide1.set_vel_pid(velPid);
  // rightSide2.set_vel_pid(velPid);
  leftDrive.add_motor(&leftSide1);
  leftDrive.add_motor(&leftSide2);
  rightDrive.add_motor(&rightSide1);
  rightDrive.add_motor(&rightSide2);
  leftDrive.set_reversed(true);
  if (autonType == AUTON_MATCH) {
    if (autonSide == SIDE_CAP) {
      auton_cap();
    } else if (autonSide == SIDE_FLAG) {
      auton_flag();
    }
  } else if (autonType == AUTON_SKILLS) {
    auton_skills();
  }
}

void auton_skills() {
  #include "autonSkills.h"
}

void auton_flag() {
  int direction = autonTeam == TEAM_BLUE ? 1 : -1;
  #include "autonFlag.h"
}

void auton_cap() {
  int direction = autonTeam == TEAM_BLUE ? 1 : -1;
  #include "autonCap.h"
}
