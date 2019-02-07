#include "vars.h"

#include "pros/motors.hpp"
#include "pros/adi.hpp"

int autonType = 0;
int autonSide = 0;
int autonTeam = 0;

sdl::AutonConfig autonConfig;

pros::Motor leftSide1(10);
pros::Motor leftSide2(20);
pros::Motor leftLauncher(6);
pros::Motor intake(16);
pros::Motor tilter(17);
pros::Motor rightLauncher(7);
pros::Motor rightSide1(9);
pros::Motor rightSide2(19);

pros::ADIGyro gyro1(5);
pros::ADIGyro gyro2(6);
pros::ADIUltrasonic loadSonar(3,4);
pros::ADIPotentiometer tiltPotent(1);
pros::ADIButton launchButton(2);
