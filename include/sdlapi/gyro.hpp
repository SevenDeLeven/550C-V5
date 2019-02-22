#ifndef _SDLAPI_GYRO_HPP_
#define _SDLAPI_GYRO_HPP_

#include "okapi/api.hpp"

namespace okapi {
class ADIGyro;
}

namespace sdl {

class Gyro {
private:
  double offset;
  double multiplier;
  double value;
  okapi::ADIGyro * gyro;
public:
  Gyro(int port);
  virtual ~Gyro();

  void reset();
  void update();
  void setOffset(double offset);
  void setMultiplier(double multiplier);

  double getOffset();
  double getMultiplier();
  double getValue();
  double getValueOffset(double offset);
  double getRaw();
  double getRawOffset(double offset);
};    //CLASS GYRO

}     //NAMESPACE SDL

#endif
