#include "sdlapi/robot.hpp"
#include "sdlapi/timer.hpp"
#include "math.h"

using namespace sdl;
Robot::Robot() {

}

Robot::~Robot() {

}

void Robot::setTicksPerTile(double ticksPerTile) {
  this->ticksPerTile = ticksPerTile;
}

void Robot::setTicksPerRevolution(double ticksPerRevolution) {
  this->ticksPerRevolution = ticksPerRevolution;
}

void Robot::go(double tiles) {
  long distance = tiles*this->ticksPerTile;
  Timer timer;
  leftDrive.reset_position();
  rightDrive.reset_position();
	int direction = 1;
  if (distance < 0) {
  	direction *= -1;
  	distance = abs(distance);
  }

	bool clearedTimer = false;
	while (true) {
		long leftDistance = abs(this->leftDrive.get_position());
		long rightDistance = abs(this->rightDrive.get_position());
		long leftDifference = distance-leftDistance;
		long rightDifference = distance-rightDistance;
		int leftSpeed = (200) * (leftDifference < 200 ? (leftDifference/200.0) : 1);
		int rightSpeed = (200) * (rightDifference < 200 ? (rightDifference/200.0) : 1);
    leftSpeed = abs(leftSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : leftSpeed;
    rightSpeed = abs(rightSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : rightSpeed;
		if (leftDistance != 0 && rightDistance != 0) {
			leftSpeed *= ((float)rightDistance)/((float)leftDistance);
			rightSpeed *= ((float)leftDistance)/((float)rightDistance);
		}
		leftDrive.move_velocity(leftSpeed*direction);
		rightDrive.move_velocity(rightSpeed*direction);
		if (clearedTimer && !((abs(leftDifference) <= 10 && abs(rightDifference) <= 10))) {
			clearedTimer = false;
		}
		if ((clearedTimer && timer.getTime() >= 100)) {
			leftDrive.move(0);
      rightDrive.move(0);
			return;
		}
		if ((abs(leftDifference) <= 10 && abs(rightDifference) <= 10 && !clearedTimer)) {
			clearedTimer = true;
			timer.reset();
		}
	}
}

void Robot::go(double tiles, double maxVel) {
  long distance = tiles*this->ticksPerTile;
  Timer timer;
  leftDrive.reset_position();
  rightDrive.reset_position();
	int direction = 1;
  if (distance < 0) {
  	direction *= -1;
  	distance = abs(distance);
  }

	bool clearedTimer = false;
	while (true) {
		long leftDistance = abs(this->leftDrive.get_position());
		long rightDistance = abs(this->rightDrive.get_position());
		long leftDifference = distance-leftDistance;
		long rightDifference = distance-rightDistance;
		int leftSpeed = (maxVel) * (leftDifference < 200 ? (leftDifference/200.0) : 1);
		int rightSpeed = (maxVel) * (rightDifference < 200 ? (rightDifference/200.0) : 1);
    leftSpeed = abs(leftSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : leftSpeed;
    rightSpeed = abs(rightSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : rightSpeed;
		if (leftDistance != 0 && rightDistance != 0) {
			leftSpeed *= ((float)rightDistance)/((float)leftDistance);
			rightSpeed *= ((float)leftDistance)/((float)rightDistance);
		}
		leftDrive.move_velocity(leftSpeed*direction);
		rightDrive.move_velocity(rightSpeed*direction);
		if (clearedTimer && !((abs(leftDifference) <= 10 && abs(rightDifference) <= 10))) {
			clearedTimer = false;
		}
		if ((clearedTimer && timer.getTime() >= 100)) {
			leftDrive.move(0);
      rightDrive.move(0);
			return;
		}
		if ((abs(leftDifference) <= 10 && abs(rightDifference) <= 10 && !clearedTimer)) {
			clearedTimer = true;
			timer.reset();
		}
	}
}

void Robot::goConstVel(double tiles, double vel) {
  long distance = tiles*this->ticksPerTile;
  leftDrive.reset_position();
  rightDrive.reset_position();
	int direction = 1;
  if (distance < 0) {
  	direction *= -1;
  	distance = abs(distance);
  }
	while (true) {
		long leftDistance = abs(this->leftDrive.get_position());
		long rightDistance = abs(this->rightDrive.get_position());
		long leftDifference = distance-leftDistance;
		long rightDifference = distance-rightDistance;
		leftDrive.move_velocity(vel*direction);
		rightDrive.move_velocity(vel*direction);
		if ((abs(leftDifference) <= 10 && abs(rightDifference) <= 10)) {
      leftDrive.move(0);
      rightDrive.move(0);
			return;
		}
	}
}

void Robot::turnDegrees(double degrees) {
  long distance = (degrees/360.0)*this->ticksPerRevolution;
  Timer timer;
  leftDrive.reset_position();
  rightDrive.reset_position();
	int direction = 1;
  if (distance < 0) {
  	direction *= -1;
  	distance = abs(distance);
  }

	bool clearedTimer = false;
	while (true) {
		long leftDistance = abs(this->leftDrive.get_position());
		long rightDistance = abs(this->rightDrive.get_position());
		long leftDifference = distance-leftDistance;
		long rightDifference = distance-rightDistance;
		int leftSpeed = (200) * (leftDifference < 200 ? (leftDifference/200.0) : 1);
		int rightSpeed = (200) * (rightDifference < 200 ? (rightDifference/200.0) : 1);
    leftSpeed = abs(leftSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : leftSpeed;
    rightSpeed = abs(rightSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : rightSpeed;
		if (leftDistance != 0 && rightDistance != 0) {
			leftSpeed *= ((float)rightDistance)/((float)leftDistance);
			rightSpeed *= ((float)leftDistance)/((float)rightDistance);
		}
		leftDrive.move_velocity(leftSpeed*direction);
		rightDrive.move_velocity(rightSpeed*direction*-1);
		if (clearedTimer && !((abs(leftDifference) <= 10 && abs(rightDifference) <= 10))) {
			clearedTimer = false;
		}
		if ((clearedTimer && timer.getTime() >= 100)) {
			leftDrive.move(0);
      rightDrive.move(0);
			return;
		}
		if ((abs(leftDifference) <= 10 && abs(rightDifference) <= 10 && !clearedTimer)) {
			clearedTimer = true;
			timer.reset();
		}
	}
}

void Robot::turnDegrees(double degrees, double maxVel) {
  long distance = (degrees/360.0)*this->ticksPerRevolution;
  Timer timer;
  leftDrive.reset_position();
  rightDrive.reset_position();
	int direction = 1;
  if (distance < 0) {
  	direction *= -1;
  	distance = abs(distance);
  }

	bool clearedTimer = false;
	while (true) {
		long leftDistance = abs(this->leftDrive.get_position());
		long rightDistance = abs(this->rightDrive.get_position());
		long leftDifference = distance-leftDistance;
		long rightDifference = distance-rightDistance;
		int leftSpeed = (maxVel) * (leftDifference < 200 ? (leftDifference/200.0) : 1);
		int rightSpeed = (maxVel) * (rightDifference < 200 ? (rightDifference/200.0) : 1);
    leftSpeed = abs(leftSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : leftSpeed;
    rightSpeed = abs(rightSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : rightSpeed;
		if (leftDistance != 0 && rightDistance != 0) {
			leftSpeed *= ((float)rightDistance)/((float)leftDistance);
			rightSpeed *= ((float)leftDistance)/((float)rightDistance);
		}
		leftDrive.move_velocity(leftSpeed*direction);
		rightDrive.move_velocity(rightSpeed*direction*-1);
		if (clearedTimer && !((abs(leftDifference) <= 10 && abs(rightDifference) <= 10))) {
			clearedTimer = false;
		}
		if ((clearedTimer && timer.getTime() >= 100)) {
			leftDrive.move(0);
      rightDrive.move(0);
			return;
		}
		if ((abs(leftDifference) <= 10 && abs(rightDifference) <= 10 && !clearedTimer)) {
			clearedTimer = true;
			timer.reset();
		}
	}
}


motorgroup* Robot::getLeftDrive() {
  return &this->leftDrive;
}

motorgroup* Robot::getRightDrive() {
  return &this->rightDrive;
}
