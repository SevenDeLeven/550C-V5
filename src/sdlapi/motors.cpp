#include "sdlapi/motors.hpp"

using namespace sdl;

motorgroup::motorgroup() {
  this->motors = std::vector<pros::Motor>();
  this->reversed = false;
}

motorgroup::motorgroup(const bool reversed) {
  this->motors = std::vector<pros::Motor>();
  this->reversed = reversed;
}

motorgroup::~motorgroup() {

}

void motorgroup::moveAbsolute(const double position, const std::int32_t maxVelocity) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move_absolute(position * (this->reversed ? -1 : 1), maxVelocity);
  }
}

void motorgroup::moveRelative(const double position, const std::int32_t maxVelocity) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move_relative(position * (this->reversed ? -1 : 1), maxVelocity);
  }
}

void motorgroup::setVelocity(const std::int32_t vel) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move_velocity(vel * (this->reversed ? -1 : 1));
  }
}

void motorgroup::setSpeed(const std::int32_t speed) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move(speed);
  }
}

void motorgroup::setVoltageLimit(const std::int32_t limit) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_voltage_limit(limit);
  }
}

void motorgroup::setVoltage(const std::int32_t voltage) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move_voltage(voltage);
  }
}

void motorgroup::setReversed(const bool reversed) {
  this->reversed = reversed;
}

void motorgroup::reverse() {
  this->reversed = !this->reversed;
}

void motorgroup::setZeroPosition(const double position) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_zero_position(position);
  }
}

void motorgroup::resetPosition() {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_zero_position(this->motors[i].get_position());
  }
}

void motorgroup::setBrakeMode(const pros::motor_brake_mode_e_t mode) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_brake_mode(mode);
  }
}

void motorgroup::setGearing(const pros::motor_gearset_e_t gearset) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_gearing(gearset);
  }
}
