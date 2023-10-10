#pragma once

namespace structures {
template <typename T> class Quaternion {
public:
  /**
   * @brief creates a new quaternion with the provided fields.
   * @param x the quaternion x component.
   * @param y the quaternion y component.
   * @param z the quaternion z component.
   * @param w the quaternion w component.
   */
  Quaternion(T x, T y, T z, T w) {
    this->_x = x;
    this->_y = y;
    this->_z = z;
    this->_w = w;
  }

  /**
   * @brief copy constructor for the quaternion class.
   * @param other the other quaternion class to copy.
   */
  Quaternion(const Quaternion<T> &other) {
    this->_x = other.getX();
    this->_y = other.getY();
    this->_z = other.getZ();
    this->_w = other.getW();
  }

  /**
   * @brief creates a new identity quaternion.
   */
  Quaternion() {
    this->_x = 0;
    this->_y = 0;
    this->_z = 0;
    this->_w = 1;
  }

  /**
   * @brief copy assignment operator overload
   * @param other the other Quaternion to copy into this instance.
   * @returns new quaternion instance.
   */
  Quaternion<T> &operator=(const Quaternion &other) {
    this->_x = other.getX();
    this->_y = other.getY();
    this->_z = other.getZ();
    this->_w = other.getW();

    return *this;
  }

  /**
   * @brief multiplication operator overload between quaternions.
   * @param other the other Quaternion to multiply with this one
   * @returns the product of the multiplication
   */
  Quaternion<T> operator*(const Quaternion &other) {
    Quaternion<T> new_quat;
    new_quat.setW(this->getW() * other.getW() - this->getX() * other.getX() -
                  this->getY() * other.getY() - this->getZ() * other.getZ());
    new_quat.setX(this->getW() * other.getX() + this->getX() * other.getW() +
                  this->getY() * other.getZ() - this->getZ() * other.getY());
    new_quat.setY(this->getW() * other.getY() - this->getX() * other.getZ() +
                  this->getY() * other.getW() + this->getZ() * other.getX());
    new_quat.setZ(this->getW() * other.getZ() + this->getX() * other.getY() -
                  this->getY() * other.getX() + this->getZ() * other.getW());

    return new_quat;
  }

  /**
   * @brief multiplication operator overload between a quaternion and a scalar.
   * @param other the scalar to multiply with this quaternion
   * @returns the product of the multiplication
   */

  Quaternion<T> operator*(const T &other) {
    Quaternion<T> new_quat;
    new_quat.setW(this->getW() * other);
    new_quat.setX(this->getX() * other);
    new_quat.setY(this->getY() * other);
    new_quat.setZ(this->getZ() * other);

    return new_quat;
  }

  /**
   * @brief gets the X component of the quaternion.
   * @returns the X component of the quaternion.
   */
  T getX() const { return this->_x; }

  /**
   * @brief gets the Y component of the quaternion.
   * @returns the Y component of the quaternion.
   */
  T getY() const { return this->_y; }

  /**
   * @brief gets the Z component of the quaternion.
   * @returns the Z component of the quaternion.
   */
  T getZ() const { return this->_z; }

  /**
   * @brief gets the W component of the quaternion.
   * @returns the W component of the quaternion.
   */
  T getW() const { return this->_w; }

  /**
   * @brief sets the X component of the quaternion.
   * @param x the new X component value.
   */
  void setX(T x) { this->_x = x; }

  /**
   * @brief sets the Y component of the quaternion.
   * @param y the new Y component value.
   */
  void setY(T y) { this->_y = y; }

  /**
   * @brief sets the Z component of the quaternion.
   * @param z the new Z component value.
   */
  void setZ(T z) { this->_z = z; }

  /**
   * @brief sets the W component of the quaternion.
   * @param w the new W component value.
   */
  void setW(T w) { this->_w = w; }

private:
  T _x;
  T _y;
  T _z;
  T _w;
}; // end Quaternion class
} // namespace structures