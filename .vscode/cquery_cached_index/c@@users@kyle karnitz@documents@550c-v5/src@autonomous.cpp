#include "main.h"
#include "sdlapi/motors.hpp"
#include "sdlapi/timer.hpp"
#include "sdlapi/event.hpp"
#define THRESHOLD 54
#define MINVEL 57
#define MINVEL_TURNING 27
#define PID_K_P (0.001)
#define PID_K_I (0.1)
#define PID_K_D (0)

bool flipTurningEnabled = false;
void flipTurning() {
  flipTurningEnabled = !flipTurningEnabled;
}
void setFlipTurning(bool flipTurning) {
  flipTurningEnabled = flipTurning;
}

sdl::motorgroup leftDrive;
sdl::motorgroup rightDrive;


void initShooter() {
  sdl::Timer tiltTimer;
  tilter = -100;
  bool tilterCalibrated = false;
  while (!launchButton.get_value() || tiltTimer.getTime() < 500) {
    if (!tilterCalibrated && tiltTimer.getTime() >= 500) {
      calibrateTilter();
      tiltMid();
    }
    loadShooter();
  }
  shooter(0);
  if (!tilterCalibrated && tiltTimer.getTime() >= 500) {
    calibrateTilter();
    tiltMid();
  }
}

void initShooter(void*) {
  initShooter();
}

void punchThenMid(double &maxVel, double &leftTargetDistance, double &rightTargetDistance) {
  punchThen(TILTER_MID_CLOSE);
}

void slowAfter(double &maxVel, double &leftTargetDistance, double &rightTargetDistance) {
   maxVel = maxVel/2;
}

void stopIntake(double &maxVel, double &leftTargetDistance, double &rightTargetDistance) {
  intake = 0;
}

void invertIntake(double &maxVel, double &leftTargetDistance, double &rightTargetDistance) {
 intake = -127;
 leftTargetDistance = 2.0*TICKSPERTILE;
 rightTargetDistance = 2.0*TICKSPERTILE;
}

void changeTargetDistance(double &maxVel, double &leftTargetDistance, double &rightTargetDistance) {
  leftTargetDistance = 0.4*TICKSPERTILE;
  rightTargetDistance = 0.4*TICKSPERTILE;
}

void goCheckpoint(double maxVel, double maxTime, double minTime) {
  maxTime *= 1000;
  maxVel = -maxVel;
  sdl::Timer timer;
  leftDrive.move(maxVel);
  rightDrive.move(maxVel);
  while (((abs(getAcc()-2028) < 70 || !((maxVel < 0 && getAcc()-2028 < 0) || (maxVel > 0 && getAcc()-2028 < 0))) && timer.getTime() < maxTime) || timer.getTime() < minTime) {

  }
  pros::delay(50);
  leftDrive.move(0);
  rightDrive.move(0);
}

void goCheckpoint(double maxVel, double maxTime) {
  goCheckpoint(maxVel, maxTime, 0.2);
}

void goCheckpoint(double maxVel) {
  goCheckpoint(maxVel, 0.8);
}

void pidGo(double tiles, double maxVel, sdl::Event* events, int eventCount) {
  tiles = -tiles;
  double targetDistance = tiles*TICKSPERTILE;
  sdl::Timer timer;
  sdl::Timer currentTimeTimer;
  int direction = 1;
  if (targetDistance < 0)  {
    direction *= -1;
    targetDistance = abs(targetDistance);
  }

  sdl::Timer clearTimer;
  bool clearedTimer = false;
  leftDrive.reset_position();
  rightDrive.reset_position();

  double leftErrorI = 0;
  double rightErrorI = 0;
  double lastLeftError = 0;
  double lastRightError = 0;

  double currentTime = pros::millis()/1000.0;
  double lastTime = currentTime;
  double deltaTime = 0;

  while (true) {
    loadShooter();
    currentTime = pros::millis()/1000.0;
    deltaTime = currentTime-lastTime;
    double leftDistance = abs(leftDrive.get_position());
    double rightDistance = abs(rightDrive.get_position());
    double leftError = targetDistance - leftDistance;
    double rightError = targetDistance - rightDistance;

    double leftPOut = leftError;
    double rightPOut = rightError;

    double leftIOut = leftErrorI;
    double rightIOut = rightErrorI;

    double leftDOut = (leftError - lastLeftError) / deltaTime;
    double rightDOut = (rightError - lastRightError) / deltaTime;

    int leftSpeed = (leftPOut*PID_K_P)+(leftIOut*PID_K_I)+(leftDOut*PID_K_D);
    if (abs(leftSpeed) > maxVel) {
      leftSpeed = maxVel * (leftSpeed < 0 ? -1 : 1);
    }

    int rightSpeed = (rightPOut*PID_K_P)+(rightIOut*PID_K_I)+(rightDOut*PID_K_D);
    if (abs(rightSpeed) > maxVel) {
      rightSpeed = maxVel * (rightSpeed < 0 ? -1 : 1);
    }

    leftDrive.move(leftSpeed);
    rightDrive.move(rightSpeed);


    leftErrorI += leftError*deltaTime;
    rightErrorI += rightError*deltaTime;
    lastLeftError = leftError;
    lastRightError = rightError;
    lastTime = currentTime;

    pros::delay(10);
  }
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

  bool resetVelocityCorrectionTimer = false;
  sdl::Timer velocityCorrectionTimer;
 	while (true) {
    loadShooter();
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
 		if ((clearedTimer && timer.getTime() >= 200)) {
 			leftDrive.move(0);
       rightDrive.move(0);
 			return;
 		}
 		if ((abs(leftDifference) <= THRESHOLD && abs(rightDifference) <= THRESHOLD && !clearedTimer)) {
 			clearedTimer = true;
 			timer.reset();
 		}

    if (resetVelocityCorrectionTimer && (leftDrive.get_actual_velocity() >= 20 || rightDrive.get_actual_velocity() >= 20)) {
      resetVelocityCorrectionTimer = false;
    }
    if (resetVelocityCorrectionTimer && leftDrive.get_actual_velocity() < 15 && rightDrive.get_actual_velocity() < 15 && velocityCorrectionTimer.getTime() > 500) {
      leftDrive.move(0);
      rightDrive.move(0);
      return;
    }
    if (leftDrive.get_actual_velocity() < 15 && rightDrive.get_actual_velocity() < 15 && !resetVelocityCorrectionTimer) {
      velocityCorrectionTimer.reset();
      resetVelocityCorrectionTimer = true;
    }
    // if (velocityCorrectionTimer.getTime() > 100) {
    //   velocityCorrectionTimer.reset();
    //   if (abs(leftDrive.get_actual_velocity()) < 200 && abs(leftDifference) > THRESHOLD) {
    //     leftVelocityCorrection += 1;
    //   }
    //   if (abs(rightDrive.get_actual_velocity()) < 200 && abs(rightDifference) > THRESHOLD) {
    //     rightVelocityCorrection += 1;
    //   }
    //   leftVelocityCorrection = leftVelocityCorrection > 2 ? 2 : leftVelocityCorrection;
    //   rightVelocityCorrection = rightVelocityCorrection > 2 ? 2 : rightVelocityCorrection;
    // }
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




 void turnDegrees(double degrees, double maxVel, double decelMult) {
  while (degrees > 180) {
    degrees -= 360;
  }
  while (degrees < -180) {
    degrees += 360;
  }
  double TURN_THRESHOLD = 0.54;
  int turnDirection = ((autonType == AUTON_MATCH && autonTeam == TEAM_BLUE) ? -1 : 1 ) * (flipTurningEnabled ? -1 : 1);
  degrees *= turnDirection;
  int tpr = turnDirection == 1 ? TICKSPERREVOLUTION_RIGHT : TICKSPERREVOLUTION_LEFT;
  double distance = (abs(degrees)/360.0)*tpr;
  sdl::Timer timer;
  int direction = 1;

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
    double gyroDifference = getGyroDifference(degrees);

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
    leftSpeed *= (abs(gyroDifference) < 45*decelMult ? abs(gyroDifference)/(45.0*decelMult) : 1);
    rightSpeed *= (abs(gyroDifference) < 45*decelMult ? abs(gyroDifference)/(45.0*decelMult) : 1);

    //Minimum Velocity Checking
    if (abs(gyroDifference) > TURN_THRESHOLD) {
      leftSpeed = abs(leftSpeed) < MINVEL_TURNING ? (leftSpeed < 0 ? -MINVEL_TURNING : MINVEL_TURNING) : leftSpeed;
      rightSpeed = abs(rightSpeed) < MINVEL_TURNING ? (rightSpeed < 0 ? -MINVEL_TURNING : MINVEL_TURNING) : rightSpeed;
    }

    //Direction Correction
    leftSpeed *= gyroDifference < 0 ? -1 : 1;
    rightSpeed *= gyroDifference < 0 ? -1 : 1;


    //Finalize
 		leftDrive.move(leftSpeed*direction);
 		rightDrive.move(rightSpeed*direction*-1);



    //Target Reach Check w/ 300ms timer to ensure robot is in position without momentum
 		if (clearedTimer && abs(gyroDifference) > TURN_THRESHOLD) {
 			clearedTimer = false;
 		}
 		if (clearedTimer && timer.getTime() >= 300) {
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

void turnDegrees(double degrees, int maxVel) {
  turnDegrees(degrees, maxVel, 1);
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








//AUTON TEST
void auton_test() {
  if (autonConfig.park) {
    turnDegrees(90*(autonConfig.turnOffset));
    intake = 127;
    pros::delay(100);
    intake = 0;
  } else {
    pidGo(autonConfig.turnOffset, 127, nullptr, 0);
    intake = 127;
    pros::delay(100);
    intake = 0;
  }
}
































//SKILLS
void auton_skills() {
  sdl::Timer tiltTimer;
  sdl::Timer timer;

  setFlipTurning(false);
  tilter = -70;
  intake = -127;
  sdl::Event evt_arr[] = {sdl::Event(slowAfter, sdl::callback_point::DISTANCED, 1.5)};
  go(1.8, 127, evt_arr, 2);
  calibrateTilter();
  tiltMid();
  intake = 0;
  go(0.35);
  intake = -127;
  go(-2.25);
  goTime(0.5, -127);
  go(0.2);
  turnDegrees(-89);
  go(0.15);
  intake = -127;
  punchThen(TILTER_TOP_CLOSE);
  pros::delay(200);
  punchThen(TILTER_MID_CLOSE);
  turnDegrees(-3, 60);
  go(0.9);
  turnDegrees(-7, 60);
  go(0.85);
  go(-1.75);
  turnDegrees(93);
  goTime(0.5, -127);
  go(1.0);
  turnDegrees(-90);
  intake = 127;
  go(1.0);
  go(-1.0);
  intake = -127;
  turnDegrees(90);
  go(1.1);
  turnDegrees(-90);
  goTime(0.7, -80);
  go(0.4);
  if (getLoadCount() > 0) { //Second set of shots
    turnDegrees(5, 60);
    intake = -127;
    punchThen(TILTER_TOP_CLOSE);
    if (detectLoaded()) {
      while (!readyToFire()) {
        loadShooter();
      }
      shooter(0);
      pros::delay(100);
      punch();
    }
    tiltMid();
    turnDegrees(-6, 60);
  }
  go(1.7);
  goTime(0.5, 127);
  go(-1.2);
  intake = 0;
  turnDegrees(90);
  intake = 90;
  sdl::Event evt_arr2[] = {sdl::Event(stopIntake, sdl::callback_point::DISTANCED, 2.1)};
  go(2.45, 127, evt_arr2, 1);
  go(-0.5);
  turnDegrees(-90);
  intake = -127;
  go(0.7);
  goTime(0.5, 127);
  go(-2.2);
  turnDegrees(-90);
  if (getLoadCount() == 2) {
    intake = 127;
  }
  go(1.0);
  go(-1.0);
  timer.reset();
  while (!(getLoadCount() > 1) && timer.getTime() < 1000) { //Wait for 1 second or until a ball is loaded

  }
  if (detectLoaded()) {   //Third set of shots
    turnDegrees(93);
    go(0.1);
    punchThen(TILTER_TOP_CLOSE);
    if (detectLoaded()) {
      while (!readyToFire()) {
        loadShooter();
      }
      shooter(0);
      pros::delay(100);
      punchThen(TILTER_MID_CLOSE);
    }
    tiltMid();
    turnDegrees(-93);
  }
  go(-0.9);
  goTime(0.4, -127);
  go(0.2);
  turnDegrees(-90);
  go(0.9);
  turnDegrees(-90);
  goTime(0.4, 127);
  go(-0.7,90);
  go(-3.0);
  intake = 0;

}



















//AUTON FLAG
void auton_flag() {
  int direction = autonTeam == TEAM_BLUE ? 1 : -1;
  setFlipTurning(true);

  intake = -127;
  tilter = -70;
  go(1.9);
  calibrateTilter();
  tiltTop();
  go(-1.9);
  goTime(0.5, -127);
  go(0.2);
  turnDegrees(89);
  go(0.25);
  punchThen(TILTER_MID_CLOSE); //Position is actually next position after shooting
  pros::delay(100);
  punchThen(TILTER_TOP_CLOSE);
  go(0.4);
  turnDegrees(11);
  go(1.3);
  go(-1.55);
  turnDegrees(-61);
  intake = 127;
  sdl::Event evt_arr[] = {sdl::Event(stopIntake, sdl::callback_point::DISTANCED, 1), sdl::Event(punchThenMid, sdl::callback_point::DISTANCED, 0.7)};
  go(1.3,60,evt_arr,2);
  go(-0.5);
  punchThen(TILTER_TOP_CLOSE);
  intake = 0;

  // turnDegrees(-44);
  // sdl::Event evt_arr[] = {sdl::Event(changeTargetDistance, sdl::callback_point::DISTANCED, 0.64)};
  // go(0.7, 100, evt_arr, 2);
  // pros::delay(1500);
  // intake = 60;
  // go(1.0);
  // go(-0.4);
  // intake = -127;
  // turnDegrees(-3, 60);
  // punchThen(TILTER_TOP_CLOSE); //Position is actually next position after shooting
  // pros::delay(100);
  // punchThen(TILTER_MID_CLOSE);

}






















//AUTON CAP
void auton_cap() {
  int direction = autonTeam == TEAM_BLUE ? 1 : -1;
  setFlipTurning(false);
  pros::Task shooterInitializationTask(initShooter);
  intake = -127;
  tilter = -70;
  go(1.8);
  calibrateTilter();
  tiltTop();
  go(-0.2);
  turnDegrees(-57);
  punchThen(TILTER_MID_CLOSE); //Position is actually next position after shooting
  pros::delay(400);
  punchThen(TILTER_TOP_CLOSE);
  turnDegrees(90+57);
  go(-1.45);
  intake = 0;

}
