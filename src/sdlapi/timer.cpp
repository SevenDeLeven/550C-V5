#include "sdlapi/timer.hpp"
#include "main.h"

using namespace sdl;

Timer::Timer() {
  this->reset();
}

Timer::~Timer() {

}

void Timer::reset() {
  this->start = pros::millis();
}

int Timer::getTime() {
  return pros::millis()-(this->start);
}
