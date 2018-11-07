#include "main.h"
#include "sdlapi/robot.hpp"
#include "sdlapi/timer.hpp"
#include "math.h"

using namespace sdl;
Robot::Robot() {
  this->m_leftDrive = new motorgroup();
  this->m_rightDrive = new motorgroup();
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
  motorgroup leftDrive = *this->m_leftDrive;
  motorgroup rightDrive = *this->m_rightDrive;
    leftDrive.move(127);
    pros::delay(500);
  double distance = tiles*this->ticksPerTile;
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
		double leftDistance = abs(leftDrive.get_position());
		double rightDistance = abs(rightDrive.get_position());
		double leftDifference = distance-leftDistance;
		double rightDifference = distance-rightDistance;
		std::int32_t leftSpeed = (200) * (leftDifference < 200 ? (leftDifference/200.0) : 1);
		std::int32_t rightSpeed = (200) * (rightDifference < 200 ? (rightDifference/200.0) : 1);
    leftSpeed = abs(leftSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : leftSpeed;
    rightSpeed = abs(rightSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : rightSpeed;
		// leftDrive.move(leftSpeed*direction > 127 ? 127 : leftSpeed*direction < -127 ? -127 : leftSpeed*direction);
		// rightDrive.move(rightSpeed*direction > 127 ? 127 : rightSpeed*direction < -127 ? -127 : rightSpeed*direction);
    leftDrive.move(127);
    rightDrive.move(127);
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
motorgroup leftDrive = *this->m_leftDrive;
motorgroup rightDrive = *this->m_rightDrive;
  double distance = tiles*this->ticksPerTile;
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
		double leftDistance = abs(leftDrive.get_position());
		double rightDistance = abs(rightDrive.get_position());
		double leftDifference = distance-leftDistance;
		double rightDifference = distance-rightDistance;
		std::int32_t leftSpeed = (maxVel) * (leftDifference < 200 ? (leftDifference/200.0) : 1);
		std::int32_t rightSpeed = (maxVel) * (rightDifference < 200 ? (rightDifference/200.0) : 1);
    leftSpeed = abs(leftSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : leftSpeed;
    rightSpeed = abs(rightSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : rightSpeed;
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
motorgroup leftDrive = *this->m_leftDrive;
motorgroup rightDrive = *this->m_rightDrive;
  double distance = tiles*this->ticksPerTile;
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

void Robot::goTime(double time, double vel) {
motorgroup leftDrive = *this->m_leftDrive;
motorgroup rightDrive = *this->m_rightDrive;
  leftDrive.move(vel);
  rightDrive.move(vel);
  pros::delay(time*1000);
  leftDrive.move(0);
  rightDrive.move(0);
}

void Robot::turnDegrees(double degrees) {
motorgroup leftDrive = *this->m_leftDrive;
motorgroup rightDrive = *this->m_rightDrive;
  double distance = (degrees/360.0)*this->ticksPerRevolution;
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
		double leftDistance = abs(leftDrive.get_position());
		double rightDistance = abs(rightDrive.get_position());
		double leftDifference = distance-leftDistance;
		double rightDifference = distance-rightDistance;
		std::int32_t leftSpeed = (200) * (leftDifference < 200 ? (leftDifference/200.0) : 1);
		std::int32_t rightSpeed = (200) * (rightDifference < 200 ? (rightDifference/200.0) : 1);
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
motorgroup leftDrive = *this->m_leftDrive;
motorgroup rightDrive = *this->m_rightDrive;
  double distance = (degrees/360.0)*this->ticksPerRevolution;
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
		double leftDistance = abs(leftDrive.get_position());
		double rightDistance = abs(rightDrive.get_position());
		double leftDifference = distance-leftDistance;
		double rightDifference = distance-rightDistance;
		std::int32_t leftSpeed = (maxVel) * (leftDifference < 200 ? (leftDifference/200.0) : 1);
		std::int32_t rightSpeed = (maxVel) * (rightDifference < 200 ? (rightDifference/200.0) : 1);
    leftSpeed = abs(leftSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : leftSpeed;
    rightSpeed = abs(rightSpeed) < 5 ? (leftSpeed < 0 ? -5 : 5) : rightSpeed;
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
  return this->m_leftDrive;
}

motorgroup* Robot::getRightDrive() {
  return this->m_rightDrive;
}
