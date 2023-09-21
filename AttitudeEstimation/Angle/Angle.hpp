#pragma once
#include <math.h>

namespace structures {

/**
 * @brief a enum representing an angle type.
 */
typedef enum { DEGREES, RADIANS } angle_type_t;

template <typename T> class Angle {
public:
  /**
   * @brief default constructor for angle class.
   */
  Angle() {
    this->_angle_value = 0;
    this->_angle_type = DEGREES;
  }

  /**
   * @brief parameterized angle class constructor.
   * @param angle_value the value of the angle to store in this instance.
   * @param angle_type angle_type_t representing the angle type for this
   * instance.
   */
  Angle(T angle_value, angle_type_t angle_type) {
    this->_angle_value = angle_value;
    this->_angle_type = angle_type;
    this->normalizeAngle();
  }

  /**
   * @brief angle class copy constructor.
   * @param other the other angle class instance to copy into this instance.
   */
  Angle(const Angle &other) {
    this->_angle_value = other.getAngleValue();
    this->_angle_type = other.getAngleType();
    this->normalizeAngle();
  }

  /**
   * @brief angle class copy assign operator overload.
   * @param other the other angle class instance to copy into this instance.
   * @returns a new angle class instance
   */
  Angle &operator=(const Angle &other) {
    this->_angle_value = other.getAngleValue();
    this->_angle_type = other.getAngleType();
    this->normalizeAngle();

    return *this;
  }

  /**
   * @brief returns the angle value of this instance.
   * @return the angle value of this instance.
   */
  T getAngleValue() const { return this->_angle_value; }

  /**
   * @brief sets a new angle value for this angle class instance.
   * @param new_value the new angle value in units of this->_angle_value.
   */
  void setAngleValue(T new_value) {
    this->_angle_value = new_value;
    this->normalizeAngle();
  }

  /**
   * @brief returns the angle type of this instance.
   * @return the angle type of this instance.
   */
  angle_type_t getAngleType() const { return this->_angle_type; }

  /**
   * @brief normalizes this angle instance value between set value bounds.
   */
  void normalizeAngle() {
    T width;
    T offset_val;

    if (this->getAngleType() == DEGREES) {
      width = this->_degree_end_range - this->_degree_start_range;
      offset_val = this->getAngleValue() - this->_degree_start_range;
      this->_angle_value = (offset_val - (floor(offset_val / width) * width)) +
                           this->_degree_start_range;
    } else {
      width = this->_rad_end_range - this->_rad_start_range;
      offset_val = this->getAngleValue() - this->_rad_start_range;
      this->_angle_value = (offset_val - (floor(offset_val / width) * width)) +
                           this->_rad_start_range;
    }
  }

  /**
   * @brief converts the the angle type and value of this
   * class into radians, if not already in radians.
   */
  void toRadians() {
    if (this->getAngleType() == DEGREES) {
      this->_angle_type = RADIANS;
      this->setAngleValue(this->getAngleValue() * (M_PI / 180.0));
      this->normalizeAngle();
    }
  }

  /**
   * @brief converts the the angle type and value of this
   * class into degrees, if not already in degrees.
   */
  void toDegrees() {
    if (this->getAngleType() == RADIANS) {
      this->_angle_type = DEGREES;
      this->setAngleValue(this->getAngleValue() * (180.0 / M_PI));
      this->normalizeAngle();
    }
  }

private:
  T _angle_value;
  angle_type_t _angle_type;
  T _degree_start_range = 0;
  T _degree_end_range = 360;
  T _rad_start_range = 0;
  T _rad_end_range = 2 * M_PI;

}; // end angle class
} // namespace structures