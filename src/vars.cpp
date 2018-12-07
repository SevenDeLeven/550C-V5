#include "vars.h"

#include "pros/motors.hpp"
#include "pros/adi.hpp"

int autonType = 0;
int autonSide = 0;
int autonTeam = 0;

pros::Motor leftSide1(1);
pros::Motor leftSide2(2);
pros::Motor arm(4);
pros::Motor intake(5);
pros::Motor tilter(6);
pros::Motor launcher(7);
pros::Motor rightSide1(9);
pros::Motor rightSide2(10);

pros::ADIPotentiometer tiltPotent(1);
pros::ADIButton launchButton(2);

double tiltOffset = 0;

void calibrateTilter() {
  tilter.set_zero_position(-tiltPotent.get_value()/TILTERRATIO);
}

void setTilterPosition(int position) {
  double tiltDistance = (position/TILTERRATIO);
  tilter.move_absolute(tiltDistance, 200);
}
