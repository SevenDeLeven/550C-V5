#ifndef VARS_H
#define VARS_H

#define SIDE_CAP 1
#define SIDE_FLAG 2
#define TEAM_BLUE 1
#define TEAM_RED 2
#define AUTON_MATCH 1
#define AUTON_SKILLS 2

namespace pros {
class Motor;
}

extern int autonType;
extern int autonTeam;
extern int autonSide;

extern pros::Motor leftSide1;
extern pros::Motor rightSide1;
extern pros::Motor leftSide2;
extern pros::Motor rightSide2;
extern pros::Motor flyWheel;
extern pros::Motor intake;

#endif
