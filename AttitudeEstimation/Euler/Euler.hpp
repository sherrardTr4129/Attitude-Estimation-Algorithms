#pragma once

#include "../Angle/Angle.hpp"
#include "../Quaternion/Quaternion.hpp"

namespace structures {
template <typename T> class Euler {
public:
  /**
   * @brief construct and euler class with provided values.
   * @param x Angle rotation around x axis
   * @param y Angle rotation around y axis
   * @param z Angle rotation around z axis
   * @param angle_types the type of angles given in this constructor
   */
  Euler(T x, T y, T z, angle_type_t angle_types) {
    this->_x = Angle(x, angle_types);
    this->_y = Angle(y, angle_types);
    this->_z = Angle(z, angle_types);
    this->_angle_types = angle_types;
  }

  /**
   * @brief constuct a zero euler of angle type degrees
   */
  Euler() {
    this->_x = Angle((T)0, DEGREES);
    this->_y = Angle((T)0, DEGREES);
    this->_z = Angle((T)0, DEGREES);
    this->_angle_types = DEGREES;
  }

  /**
   * @brief copy constructor for euler class
   */
  Euler(const Euler &other) {
    this->_x = other.getX();
    this->_y = other.getY();
    this->_z = other.getZ();
    this->_angle_types = other.getAngleType();
  }

  /**
   * @brief copy assignment operator overload.
   * @param other the other Euler class to copy into this instance.
   */
  Euler &operator=(const Euler &other) {
    this->_x = other.getX();
    this->_y = other.getY();
    this->_z = other.getZ();
    this->_angle_types = other.getAngleType();

    return *this;
  }

  /**
   * @brief gets the X component of the euler angle
   * @return the X component of the euler angle
   */
  Angle<T> getX() const { return this->_x; }

  /**
   * @brief gets the Y component of the euler angle
   * @return the Y component of the euler angle
   */
  Angle<T> getY() const { return this->_y; }

  /**
   * @brief gets the Z component of the euler angle
   * @return the Z component of the euler angle
   */
  Angle<T> getZ() const { return this->_z; }

  /**
   * @brief sets the rotation about the x axis.
   * @param x the new rotation about the x axis.
   */
  void setX(Angle<T> x) { this->_x = x; }

  /**
   * @brief sets the rotation about the y axis.
   * @param y the new rotation about the y axis.
   */
  void setY(Angle<T> y) { this->_y = y; }

  /**
   * @brief sets the rotation about the z axis.
   * @param z the new rotation about the z axis.
   */
  void setZ(Angle<T> z) { this->_z = z; }

  /**
   * @brief get angle type of this class instance
   * @return the angle type of this class instance
   */
  angle_type_t getAngleType() const { return this->_angle_types; }

  /**
   * @brief convert all angles to radians, if not already in radians
   */
  void toRadians() {
    if (_angle_types == DEGREES) {
      this->_angle_types = RADIANS;
      this->_x.toRadians();
      this->_y.toRadians();
      this->_z.toRadians();
    }
  }

  /**
   * @brief convert all angles to degrees, if not already in degrees
   */
  void toDegrees() {
    if (_angle_types == RADIANS) {
      this->_angle_types = DEGREES;
      this->_x.toDegrees();
      this->_y.toDegrees();
      this->_z.toDegrees();
    }
  }

  /**
   * @brief generate a new quaternion from this Euler class instance.
   * @return
   */
  Quaternion<T> toQuaternion() {
    // make sure we are in units of Radians
    Euler<T> euler_to_convert = *this;

    if (euler_to_convert.getAngleType() == DEGREES) {
      euler_to_convert.toRadians();
    }

    // roll (x), pitch (y), yaw (z)
    T roll = euler_to_convert.getX().getAngleValue();
    T pitch = euler_to_convert.getY().getAngleValue();
    T yaw = euler_to_convert.getZ().getAngleValue();

    // compute Quaternion components
    T w = cos(roll / 2) * cos(pitch / 2) * cos(yaw / 2) +
          sin(roll / 2) * sin(pitch / 2) * sin(yaw / 2);
    T x = sin(roll / 2) * cos(pitch / 2) * cos(yaw / 2) -
          cos(roll / 2) * sin(pitch / 2) * sin(yaw / 2);
    T y = cos(roll / 2) * sin(pitch / 2) * cos(yaw / 2) +
          sin(roll / 2) * cos(pitch / 2) * sin(yaw / 2);
    T z = cos(roll / 2) * cos(pitch / 2) * sin(yaw / 2) -
          sin(roll / 2) * sin(pitch / 2) * cos(yaw / 2);

    return Quaternion<T>(x, y, z, w);
  }

private:
  Angle<T> _x;
  Angle<T> _y;
  Angle<T> _z;
  angle_type_t _angle_types;
}; // end of Euler class
} // namespace structures