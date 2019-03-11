#ifndef SDLAPI_MOTORS_HPP
#define SDLAPI_MOTORS_HPP

#include <vector>
#include "../pros/motors.hpp"

namespace sdl {

class motorgroup {
private:
  std::vector<pros::Motor> motors;
  bool reversed;
public:
  /**
  * Constructor for motorgroup
  *
  * Designed to be a multi-motor control system which looks identical to the pros::Motor class
  *
  * \param reversed
  *   Whether or not this group should be reversed. This does not set the motors' reversed flags, but
  *     instead stores the boolean and changes the direction accordingly
  *
  * \param gearset
  *   The initial gearset of the motors. This does set the gearset of all motors in the motorgroup
  *
  * \param units
  *   The encoder units to have each motor set to use. This does set the units flag of all motors in the motorgroup
  */
  motorgroup();

  motorgroup(const bool reversed);

  motorgroup(const bool reversed, const pros::motor_gearset_e_t gearset);

  motorgroup(const bool reversed, const pros::motor_gearset_e_t gearset, const pros::motor_encoder_units_e_t units);

  virtual ~motorgroup();


  /**
  * Adds a motor to the group
  *
  * \param motor
  *   The motor to add to the list
  */
  void add_motor(pros::Motor* motor);
  /**
  *
  * \param motorport
  *   The port of the motor to add to the list
  */
  void add_motor(std::int8_t motorport);
  /**
  * Sets the velocity of all motors in the group
  *
  * \param velocity
  *   The target velocity to set for all motors
  */
  void move_velocity(const std::int32_t velocity);
  /**
  * Sets the speed of the motor group
  *
  * \note Use this for joystick controlls
  *
  * \param speed
  *   The speed (from -127 to 127) to set the motors to. This is the primative way of setting the speed of motors
  */
  void move(const std::int32_t speed);
  /**
  * Sets the voltage of all motors to voltage
  *
  * \param voltage
  *   The voltage in millivolts to set the motors to
  */
  void move_voltage(const std::int32_t voltage);
  /**
  * Sets the target velocity of all motors to 0
  */
  void stop();
  /**
  * Sets the brake mode of all motors
  *
  * \param mode
  *   The brake mode to set the motors to, of type motor_brake_mode_e_t
  */
  void set_brake_mode(const pros::motor_brake_mode_e_t mode);
  /**
  * Sets the gearing of all motors in the motor group
  *
  * \note only use this if the gearing of all the motors in this set is the same
  *
  * \param gearing
  *   The gear type of the motors of type motor_gearset_e_t
  */
  void set_gearing(const pros::motor_gearset_e_t gearing);
  /**
  * Sets the current zero position of all of the motors
  *
  * \param position
  *   The position to set the zero position of
  */
  void set_zero_position(const double position);
  /**
  * Resets the positions of the motor group
  *
  * It does this by setting the zero positions of all of the motors to their current reading of encoder
  */
  void reset_position();
  /**
  * Sets the reversed flag of the motor group
  *
  * \note Does not set reversed key of motors in group
  * \note Be careful with reversing and using moveAbsolute, as doing so would cause the motor to move to the opposite
  *         side of encoder value (e.g. moveAbsolute to +1000, then reversing would set it to -1000)
  */
  void set_reversed(const bool reversed);
  /**
  * Reverses the motor group
  *
  * \note Does not set reversed key of motors in group
  * \note Be careful with reversing and using moveAbsolute, as doing so would cause the motor to move to the opposite
  *         side of encoder value (e.g. moveAbsolute to +1000, then reversing would set it to -1000)
  */
  void reverse();
  /**
  * Sets the encoder units of the group of motors
  *
  * \param units
  *   The units of type motor_encoder_units_e_t
  */
  void set_encoder_units(const pros::motor_encoder_units_e_t units);
  /**
  * Sets the voltage limit of the group of motors
  *
  * \param limit
  *   The limit of the voltage in millivolts
  */
  void set_voltage_limit(const std::int32_t limit);
  /**
  * Sets the target absolute position of the motor group
  *
  * \param position
  *   The position the group is targeted for
  *
  * \param maxVelocity
  *   The maximum velocity the group is allowed to move
  *
  * \deprecated This function may cause motors to conflict if there has been an inaccuracy in the encoders
  */
  void move_absolute(const double position, const std::int32_t maxVelocity);
  /**
  * Sets the target relative position of the motor group
  *
  * \param position
  *   The position relative to the motors' current position
  *
  * \param maxVelocity
  *   The maximum velocity the group is allowed to move
  */
  void move_relative(const double position, const std::int32_t maxVelocity);

  /**
  * Gets the average velocity of all the motors combined
  *
  * \returns
  *   The average velocity of all motors in the group
  */
  std::int32_t get_actual_velocity();
  /**
  * Gets the total torque of all the motors combined
  *
  * \returns
  *   The total torque provided by all motors in the group
  */
  std::int32_t get_torque();
  /**
  * Gets the current being drawn from all motors
  *
  * \returns
  *   The total current provided by all motors in the group
  */
  std::int32_t get_current_draw();

  /**
  * Gets the average position of all the motors combined
  *
  * \returns
  *   The average position of all motors in the group
  */
  double get_position();
};

}

#endif
