#ifndef SDLAPI_TIMER_HPP
#define SDLAPI_TIMER_HPP

namespace sdl {

class Timer {
private:
  int start;
public:
  Timer();
  virtual ~Timer();
  void reset();
  int getTime();
  void add(int a);
}; //class Timer

} //namespace sdl

#endif  //SDLAPI_TIMER_HPP
