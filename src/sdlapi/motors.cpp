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

void motorgroup::add_motor(pros::Motor* motor) {
  this->motors.push_back(*motor);
}

void motorgroup::add_motor(std::int8_t motorport) {
  pros::Motor* motor = new pros::Motor(motorport);
  this->motors.push_back(*motor);
}

void motorgroup::move(const std::int32_t speed) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move(speed * (this->reversed ? -1 : 1));
  }
}

void motorgroup::move_absolute(const double position, const std::int32_t maxVelocity) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move_absolute(position * (this->reversed ? -1 : 1), maxVelocity);
  }
}

void motorgroup::move_relative(const double position, const std::int32_t maxVelocity) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move_relative(position * (this->reversed ? -1 : 1), maxVelocity);
  }
}

void motorgroup::move_velocity(const std::int32_t vel) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move_velocity(vel * (this->reversed ? -1 : 1));
  }
}

void motorgroup::set_voltage_limit(const std::int32_t limit) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_voltage_limit(limit);
  }
}

void motorgroup::move_voltage(const std::int32_t voltage) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].move_voltage(voltage);
  }
}

void motorgroup::set_reversed(const bool reversed) {
  this->reversed = reversed;
}

void motorgroup::reverse() {
  this->reversed = !this->reversed;
}

void motorgroup::set_zero_position(const double position) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_zero_position(position);
  }
}

void motorgroup::reset_position() {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_zero_position(this->motors[i].get_position());
  }
}

void motorgroup::set_brake_mode(const pros::motor_brake_mode_e_t mode) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_brake_mode(mode);
  }
}

void motorgroup::set_gearing(const pros::motor_gearset_e_t gearset) {
  for (int i = 0; i < this->motors.size(); i++) {
    this->motors[i].set_gearing(gearset);
  }
}
