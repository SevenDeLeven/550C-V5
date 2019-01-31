#include "sdlapi/event.hpp"
#include "vars.h"
#include "math.h"

using namespace sdl;
Event::Event(event_callback_t callback, callback_point point, double point_run) {
  this->callback = callback;
  this->point = point;
  this->point_run = point_run;
  this->ran = false;
}

Event::~Event() {

}

bool Event::update(int time, double distance) {
  if (ran) {
    return false;
  }
  if (point == callback_point::TIMED) {
    return time >= this->point_run;
  } else if (point == callback_point::DISTANCED) {
    return abs(distance) >= this->point_run*TICKSPERTILE;
  }
  return false;
}

void Event::call(double &maxVel, double &leftTargetDistance, double &rightTargetDistance) {
  ran = true;
  this->callback(maxVel, leftTargetDistance, rightTargetDistance);
}
