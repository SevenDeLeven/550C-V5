#ifndef SDLAPI_EVENT_HPP
#define SDLAPI_EVENT_HPP

namespace sdl {

typedef void(*event_callback_t)(double &maxVel, double &leftTargetDistance, double &rightTargetDistance);

enum callback_point {
  TIMED,
  DISTANCED
};

class Event {
private:
  bool ran;
  callback_point point;
  event_callback_t callback;
  double point_run;
public:
  Event(event_callback_t callback, callback_point point, double point_run);
  virtual ~Event();
  bool update(int time, double distance);
  void call(double &maxVel, double &leftTargetDistance, double &rightTargetDistance);
};
};

#endif
