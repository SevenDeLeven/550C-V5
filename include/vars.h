#ifndef VARS_H
#define VARS_H

#include "pros/adi.hpp"

#define SIDE_CAP 1
#define SIDE_FLAG 2
#define TEAM_BLUE 1
#define TEAM_RED 2
#define AUTON_MATCH 1
#define AUTON_SKILLS 2

#define TILTER_MID_CLOSE 182
#define TILTER_TOP_CLOSE 2091

#define TILTERRATIO (4096.0/638.1)

namespace pros {
class Motor;
}

extern int autonType;
extern int autonTeam;
extern int autonSide;

extern pros::Motor leftSide1;
extern pros::Motor leftSide2;
extern pros::Motor tilter;
extern pros::Motor launcher;
extern pros::Motor intake;
extern pros::Motor rightSide1;
extern pros::Motor rightSide2;

extern pros::ADIPotentiometer tiltPotent;

extern double tiltOffset;

extern void calibrateTilter();
extern void set_tilter_position(int position);

#endif
