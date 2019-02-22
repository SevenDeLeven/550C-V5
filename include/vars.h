#ifndef VARS_H
#define VARS_H

#include "pros/rtos.hpp"
#include "pros/adi.hpp"
#include "classes.hpp"

#define CONFIG_FILE "/configfile.txt"

#define SIDE_CAP 1
#define SIDE_FLAG 2
#define TEAM_BLUE 1
#define TEAM_RED 2
#define AUTON_MATCH 1
#define AUTON_SKILLS 2
#define AUTON_TEST 3

#define TILTER_MID_CLOSE 100
#define TILTER_TOP_CLOSE 500

#define TICKSPERTILE (720*(900.0/392.0))
#define TICKSPERREVOLUTION_RIGHT (1445*(900.0/392.0))
#define TICKSPERREVOLUTION_LEFT (1345*(900.0/392.0))
#define TICKSPERREVOLUTION (1400*(900/392.0))

// #define DEBUG_INIT

namespace pros {
class Motor;
}

namespace sdl {
class Gyro;
}

extern sdl::AutonConfig autonConfig;

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

extern pros::Task gyroTask;
extern sdl::Gyro gyro1;
extern sdl::Gyro gyro2;
extern pros::ADIUltrasonic loadSonar;
extern pros::ADIPotentiometer tiltPotent;
extern pros::ADIButton launchButton;

extern void calibrateTilter();
extern void tiltMid();
extern void tiltTop();
extern void punch();
extern void punchThen(int nextPosition);
extern void set_tilter_position(int position);

extern void loadShooter();
extern void shooter(int speed);
extern bool detectLoaded();
extern bool readyToFire();
extern int getLoadCount();
extern float getGyro();
extern double getGyroDifference(double target);
extern void resetGyro();

#endif
