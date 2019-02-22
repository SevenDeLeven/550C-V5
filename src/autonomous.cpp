#include "main.h"
#include "sdlapi/motors.hpp"
#include "sdlapi/timer.hpp"
#include "sdlapi/event.hpp"
#define THRESHOLD 54
#define MINVEL 40
#define MINVEL_TURNING 30


bool flipTurningEnabled = false;
void flipTurning() {
  flipTurningEnabled = !flipTurningEnabled;
}
void setFlipTurning(bool flipTurning) {
  flipTurningEnabled = flipTurning;
}

sdl::motorgroup leftDrive;
sdl::motorgroup rightDrive;

void slowAfter(double &maxVel, double &leftTargetDistance, double &rightTargetDistance) {
   maxVel = 90;
 }

void go(double tiles, double maxVel, sdl::Event* events, int eventCount) {
   tiles = -tiles;
   double distance = tiles*TICKSPERTILE;
   sdl::Timer timer;
 	 int direction = 1;
   if (distance < 0) {
   	direction *= -1;
   	distance = abs(distance);
   }

 	bool clearedTimer = false;
  leftDrive.reset_position();
  rightDrive.reset_position();
  sdl::Timer currentTimeTimer;
 	while (true) {
    int currentTime = currentTimeTimer.getTime();
 		double leftDistance = abs(leftDrive.get_position());
 		double rightDistance = abs(rightDrive.get_position());
 		double leftDifference = distance-leftDistance;
 		double rightDifference = distance-rightDistance;
 		std::int32_t leftSpeed = (maxVel) * (leftDifference < 400 ? (leftDifference/400.0) : 1);
 		std::int32_t rightSpeed = (maxVel) * (rightDifference < 400 ? (rightDifference/400.0) : 1);
    if (leftDistance != 0 && rightDistance != 0) {
      double distanceRatio = ((leftDistance+rightDistance)/2.0)/200.0;
      double leftFraction = (rightDistance/leftDistance);
      leftFraction *= leftFraction*leftFraction*leftFraction;
      double rightFraction = (leftDistance/rightDistance);
      rightFraction *= rightFraction*rightFraction*rightFraction;

      leftSpeed *= leftFraction;
      rightSpeed *= rightFraction;
    }
    if ((leftDifference) > THRESHOLD) {
      leftSpeed = abs(leftSpeed) < MINVEL ? (leftSpeed < 0 ? -MINVEL : MINVEL) : leftSpeed;
    }
    if (abs(rightDifference) > THRESHOLD) {
      rightSpeed = abs(rightSpeed) < MINVEL ? (rightSpeed < 0 ? -MINVEL : MINVEL) : rightSpeed;
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
    for (int i = 0; i < eventCount; i++) {
      if (events[i].update(currentTime, (leftDistance+rightDistance)/2.0)) {
        events[i].call(maxVel, distance, distance);
      }
    }
 	}
 }




 void go(double tiles, int maxVel) {
   go(tiles, maxVel, nullptr, 0);
 }



 void go(double tiles) {
   go(tiles, 127);
 }



 void goCurve(double tiles, double curve, double maxVel) {
  if (curve == 0) {
    return;
  }
  double distance = tiles*TICKSPERTILE;
  sdl::Timer timer;
  int direction = 1;
  if (distance < 0) {
    direction *= -1;
    distance = abs(distance);
  }

  bool clearedTimer = false;
  double leftTargetDistance = distance * curve;
  double rightTargetDistance = distance / curve;
  while (true) {
    double leftDistance = abs(leftDrive.get_position());
    double rightDistance = abs(rightDrive.get_position());
    double leftDifference = leftTargetDistance-leftDistance;
    double rightDifference = rightTargetDistance-rightDistance;
    std::int32_t leftSpeed = (maxVel) * (leftDifference < 800 ? (leftDifference/800.0) : 1);
    std::int32_t rightSpeed = (maxVel) * (rightDifference < 800 ? (rightDifference/800.0) : 1);
    if ((leftDifference) > THRESHOLD) {
      leftSpeed = abs(leftSpeed) < MINVEL ? (leftSpeed < 0 ? -MINVEL : MINVEL) : leftSpeed;
    }
    if (abs(rightDifference) > THRESHOLD) {
      rightSpeed = abs(rightSpeed) < MINVEL ? (rightSpeed < 0 ? -MINVEL : MINVEL) : rightSpeed;
    }
    leftDrive.move(leftSpeed*direction*curve);
    rightDrive.move(rightSpeed*direction/curve);
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




 void goCurve(double tiles, double curve) {
   goCurve(-tiles, curve, 127);
 }




void goConstVel(double tiles, double maxVel) {
  tiles = -tiles;
  double distance = tiles*TICKSPERTILE;
  sdl::Timer timer;
 	int direction = 1;
  if (distance < 0) {
 	  direction *= -1;
   	distance = abs(distance);
  }

 	bool clearedTimer = false;
  leftDrive.move(maxVel*direction/4);
  rightDrive.move(maxVel*direction/4);
  pros::delay(250);
  leftDrive.move(0);
  rightDrive.move(0);
  leftDrive.reset_position();
  rightDrive.reset_position();
 	while (true) {
 		double leftDistance = abs(leftDrive.get_position());
 		double rightDistance = abs(rightDrive.get_position());
 		double leftDifference = distance-leftDistance;
 		double rightDifference = distance-rightDistance;
 		std::int32_t leftSpeed = (maxVel);
 		std::int32_t rightSpeed = (maxVel);
    if (leftDistance != 0 && rightDistance != 0) {
      double leftFraction = (rightDistance/leftDistance) - 1.0;
      leftFraction *= 4.0;
      leftFraction += 1.0;
      double rightFraction = (leftDistance/rightDistance) - 1.0;
      rightFraction *= 4.0;
      rightFraction += 1.0;

      leftSpeed *= leftFraction;
      rightSpeed *= rightFraction;
    }
    if (leftDifference < -THRESHOLD) {
      leftSpeed *= -1;
    }
    if (rightDifference < -THRESHOLD) {
      rightSpeed *= -1;
    }
 		leftDrive.move(leftSpeed*direction);
 		rightDrive.move(rightSpeed*direction);
 		if ((abs(leftDifference) <= THRESHOLD && abs(rightDifference) <= THRESHOLD)) {
      leftDrive.move(0);
       rightDrive.move(0);
 			return;
    }
  }
}




void goTime(double time, double vel) {
  vel = -vel;
  leftDrive.move(vel);
  rightDrive.move(vel);
  pros::delay(time*1000);
  leftDrive.move(0);
  rightDrive.move(0);
}




 void turnDegrees(double degrees, double maxVel) {
  while (degrees > 360) {
    degrees -= 360;
  }
  while (degrees < -360) {
    degrees += 360;
  }
  if (degrees > 180) {
    degrees -= 360;
  }
  if (degrees < -180) {
    degrees += 360;
  }
  int TURN_THRESHOLD = 20;
  int turnDirection = ((autonType == AUTON_MATCH && autonTeam == TEAM_BLUE) ? -1 : 1 ) * (flipTurningEnabled ? -1 : 1);
  degrees *= turnDirection;
  int tpr = turnDirection == 1 ? TICKSPERREVOLUTION_RIGHT : TICKSPERREVOLUTION_LEFT;
  double distance = (abs(degrees)/360.0)*tpr;
  sdl::Timer timer;
  int direction = 1;
  // if (distance < 0) {
  // 	direction *= -1;
  // 	distance = abs(distance);
  // }

 	bool clearedTimer = false;
  leftDrive.reset_position();
  rightDrive.reset_position();
  resetGyro();

  sdl::Timer printTimer;
 	while (true) {

 		std::int32_t leftSpeed = maxVel;
 		std::int32_t rightSpeed = maxVel;

    //Distance Setting
 		double leftDistance = abs(leftDrive.get_position());
 		double rightDistance = abs(rightDrive.get_position());
    double gyroDifference = getGyroDifference(degrees)*TICKSPERREVOLUTION/360.0;

    //Curve Correction
    if (leftDistance != 0 && rightDistance != 0) {
      //Quartic Correction
      double leftFraction = rightDistance/leftDistance;
      leftFraction *= leftFraction*leftFraction*leftFraction;
      double rightFraction = leftDistance/rightDistance;
      rightFraction *= rightFraction*rightFraction*rightFraction;

      leftSpeed *= abs(leftFraction);
      rightSpeed *= abs(rightFraction);
    }

    //Target Approach Slowdown
    leftSpeed *= (abs(gyroDifference) < 500 ? abs(gyroDifference)/500.0 : 1);
    rightSpeed *= (abs(gyroDifference) < 500 ? abs(gyroDifference)/500.0 : 1);

    //Minimum Velocity Checking
    if (abs(gyroDifference) > TURN_THRESHOLD) {
      leftSpeed = abs(leftSpeed) < MINVEL_TURNING ? (leftSpeed < 0 ? -MINVEL_TURNING : MINVEL_TURNING) : leftSpeed;
    }
    if (abs(gyroDifference) > TURN_THRESHOLD) {
      rightSpeed = abs(rightSpeed) < MINVEL_TURNING ? (rightSpeed < 0 ? -MINVEL_TURNING : MINVEL_TURNING) : rightSpeed;
    }

    //Direction Correction
    leftSpeed *= gyroDifference < 0 ? -1 : 1;
    rightSpeed *= gyroDifference < 0 ? -1 : 1;


    //Finalize
 		leftDrive.move(leftSpeed*direction);
 		rightDrive.move(rightSpeed*direction*-1);



    //Target Reach Check w/ 500ms timer to ensure robot is in position
 		if (clearedTimer && !((abs(gyroDifference) <= TURN_THRESHOLD))) {
 			clearedTimer = false;
 		}
 		if (clearedTimer && timer.getTime() >= 500) {
 			leftDrive.move(0);
      rightDrive.move(0);
 			return;
 		}
 		if (abs(gyroDifference) <= TURN_THRESHOLD && !clearedTimer) {
 			clearedTimer = true;
 			timer.reset();
 		}
    pros::delay(1);
  }
}

void turnDegrees(double degrees) {
  turnDegrees(degrees, 127);
}

void autonomous() {
  calibrateTilter();
  leftDrive.add_motor(&leftSide1);
  leftDrive.add_motor(&leftSide2);
  rightDrive.add_motor(&rightSide1);
  rightDrive.add_motor(&rightSide2);
  leftDrive.set_reversed(true);
  leftSide1.set_reversed(true);
  rightSide1.set_reversed(true);
  if (autonType == AUTON_MATCH) {
    if (autonSide == SIDE_CAP) {
      auton_cap();
    } else if (autonSide == SIDE_FLAG) {
      auton_flag();
    }
  } else if (autonType == AUTON_SKILLS) {
    auton_skills();
  } else if (autonType == AUTON_TEST) {
    auton_test();
  }
}

void auton_test() {
  #include "autonTest.h"
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
