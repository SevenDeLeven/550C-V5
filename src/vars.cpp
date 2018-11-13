#include "vars.h"

#include "pros/motors.hpp"
#include "pros/adi.hpp"

int autonType = 0;
int autonSide = 0;
int autonTeam = 0;

pros::Motor leftSide1(1);
pros::Motor leftSide2(2);
pros::Motor intake(5);
pros::Motor tilter(6);
pros::Motor launcher(7);
pros::Motor rightSide1(9);
pros::Motor rightSide2(10);

pros::ADIPotentiometer tiltPotent(1);

double tiltOffset = 0;

void calibrateTilter() {
  tiltOffset = -(tiltPotent.get_value()/TILTERRATIO) + (tilter.get_position());
}

void set_tilter_position(int position) {
  double tiltDistance = tiltOffset + (position/TILTERRATIO);
  tilter.move_absolute(tiltDistance, 100);
}
