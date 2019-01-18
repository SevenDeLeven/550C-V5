#include "vars.h"

#include "pros/motors.hpp"
#include "pros/adi.hpp"

int autonType = 0;
int autonSide = 0;
int autonTeam = 0;

pros::Motor leftSide1(1);
pros::Motor leftSide2(2);
pros::Motor launcher2(4);
pros::Motor intake(5);
pros::Motor tilter(8);
pros::Motor launcher1(7);
pros::Motor rightSide1(9);
pros::Motor rightSide2(10);

pros::ADIUltrasonic centerSonar(5,6);
pros::ADIUltrasonic leftSonar(3,4);
pros::ADIUltrasonic rightSonar(7,8);
pros::ADIPotentiometer tiltPotent(1);
pros::ADIButton launchButton(2);
