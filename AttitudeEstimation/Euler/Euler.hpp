#pragma once

namespace structures {
template <typename T> class Euler {
public:
  /**
   * @brief construct and euler class with provided values.
   * @param x rotation around x axis
   * @param y rotation around y axis
   * @param z rotation around z axis
   */
  Euler(T x, T y, T z) {
    this->_x = x;
    this->_y = y;
    this->_z = z;
  }

  /**
   * @brief constuct a zero euler
   */
  Euler() {
    this->_x = 0;
    this->_y = 0;
    this->_z = 0;
  }

  /**
   * @brief copy constructor for euler class
   */
  Euler(const Euler &other) {
    this->_x = other.getX();
    this->_y = other.getY();
    this->_z = other.getZ();
  }

  /**
   * @brief copy assignment operator overload.
   * @param other the other Euler class to copy into this instance.
   */
  Euler &operator=(const Euler &other) {
    this->_x = other.getX();
    this->_y = other.getY();
    this->_z = other.getZ();

    return *this;
  }

  /**
   * @brief gets the X component of the euler angle
   * @return the X component of the euler angle
   */
  T getX() const {return this->_x;} 

  /**
   * @brief gets the Y component of the euler angle
   * @return the Y component of the euler angle
   */
  T getY() const {return this->_y;}

  /**
   * @brief gets the Z component of the euler angle
   * @return the Z component of the euler angle
   */
  T getZ() const {return this->_z;}

private:
  T _x;
  T _y;
  T _z;
}; // end of Euler class
} // namespace structures