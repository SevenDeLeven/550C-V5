#ifndef SDLAPI_ROBOT_HPP
#define SDLAPI_ROBOT_HPP
#include "motors.hpp"

namespace sdl {

class Robot {
private:
  motorgroup* m_leftDrive;
  motorgroup* m_rightDrive;
  double ticksPerTile;
  double ticksPerRevolution;
public:
  Robot();
  virtual ~Robot();

  void setTicksPerTile(double ticksPerTile);
  void setTicksPerRevolution(double ticksPerRevolution);

  void go(double tiles);
  void go(double tiles, double maxVel);
  void goConstVel(double tiles, double vel);
  void goTime(double vel, double time);
  void turnDegrees(double degrees);
  void turnDegrees(double degrees, double maxVel);

  motorgroup* getLeftDrive();
  motorgroup* getRightDrive();
};  //class Robot

}   //namespace sdl

#endif  //SDLAPI_ROBOT_HPP
