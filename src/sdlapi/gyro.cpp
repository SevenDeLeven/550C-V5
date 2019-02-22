#include "sdlapi/gyro.hpp"
#include "okapi/api.hpp"

namespace sdl {
Gyro::Gyro(int port) {
  this->offset = 0;
  this->multiplier = 0;
  this->value = 0;
  this->gyro = new okapi::ADIGyro(port);
}

Gyro::~Gyro() {

}

void Gyro::reset() {
  this->offset = -this->value;
}

void Gyro::update() {
  double curValue = this->gyro->get();
  if (abs(curValue-this->value) > 330) {  //If the gyroscope has overflowed in value
    this->offset += this->value;
  }
  this->value = curValue;
}

void Gyro::setOffset(double offset) {
  this->offset = offset;
}

void Gyro::setMultiplier(double multiplier) {
  this->multiplier = multiplier;
}

double Gyro::getOffset() {
  return this->offset;
}

double Gyro::getMultiplier() {
  return this->multiplier;
}

double Gyro::getValue() {
  return this->value + this->offset;
}

double Gyro::getValueOffset(double offset) {
  return this->value + this->offset + offset;
}

double Gyro::getRaw() {
  return this->value;
}

double Gyro::getRawOffset(double offset) {
  return this->value + offset;
}
} //Namespace SDL
