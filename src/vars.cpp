#include "vars.h"

#include "pros/motors.hpp"
#include "pros/adi.hpp"
#include "sdlapi/gyro.hpp"

void f_gyroUpdate(void*) {
  while (true) {
    gyro1.update();
    gyro2.update();
    pros::delay(1);
  }
}

int autonType = 0;
int autonSide = 0;
int autonTeam = 0;

sdl::AutonConfig autonConfig;

pros::Motor leftSide1(10);
pros::Motor leftSide2(20);
pros::Motor leftLauncher(6);
pros::Motor rightLauncher(7);
pros::Motor intake(16);
pros::Motor tilter(17);
pros::Motor rightSide1(9);
pros::Motor rightSide2(19);

pros::Task gyroTask(f_gyroUpdate);
pros::ADIAccelerometer accelerometer(1);
sdl::Gyro gyro1(5);
sdl::Gyro gyro2(6);
pros::ADIUltrasonic loadSonar(3,4);
pros::ADIPotentiometer tiltPotent(1);
pros::ADIButton launchButton(2);
