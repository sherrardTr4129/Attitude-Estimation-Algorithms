#pragma once
#include <vector>

template <typename T> class Quaternion {
    public:
      Quaternion(T x, T y, T z, T w);
      Quaternion(Quaternion<T> const& other);
      Quaternion();
      T getX();
      T getY();
      T getZ();
      T getW();
      void setX(T x);
      void setY(T y);
      void setZ(T z);
      void setW(T w);

    private:
      T _x;
      T _y;
      T _z;
      T _w;
};

/**
 * @brief creates a new quaternion with the provided fields.
*/
template <typename T> Quaternion<T>::Quaternion(T x, T y, T z, T w) {
    this->_x = x;
    this->_y = y;
    this->_z = z;
    this->_w = w;
}

/**
 * @brief creates a new quaternion from existing quaternion.
*/
template <typename T> Quaternion<T>::Quaternion(Quaternion<T> const& other) {
    this->_x = other._x;
    this->_y = other._y;
    this->_z = other._z;
    this->_w = other._w;
}

/**
 * @brief creates a new identity quaternion.
*/
template <typename T> Quaternion<T>::Quaternion() {
    this->_x = 0;
    this->_y = 0;
    this->_z = 0;
    this->_w = 1;
}

/**
 * @brief gets the X component of the quaternion.
 * @returns the X component of the quaternion.
*/
template <typename T> T Quaternion<T>::getX() {
    return this->_x;
}

/**
 * @brief gets the Y component of the quaternion.
 * @returns the Y component of the quaternion.
*/
template <typename T> T Quaternion<T>::getY() {
    return this->_y;
}

/**
 * @brief gets the Z component of the quaternion.
 * @returns the Z component of the quaternion.
*/
template <typename T> T Quaternion<T>::getZ() {
    return this->_z;
}

/**
 * @brief gets the W component of the quaternion.
 * @returns the W component of the quaternion.
*/
template <typename T> T Quaternion<T>::getW() {
    return this->_w;
}

/**
 * @brief sets the X component of the quaternion.
 * @param x the new X component value.
*/
template <typename T> void Quaternion<T>::setX(T x) {
    this->_x = x;
}

/**
 * @brief sets the Y component of the quaternion.
 * @param y the new Y component value.
*/
template <typename T> void Quaternion<T>::setY(T y) {
    this->_y = y;
}

/**
 * @brief sets the Z component of the quaternion.
 * @param z the new Z component value.
*/
template <typename T> void Quaternion<T>::setZ(T z) {
    this->_z = z;
}

/**
 * @brief sets the W component of the quaternion.
 * @param w the new W component value.
*/
template <typename T> void Quaternion<T>::setW(T w) {
    this->_w = w;
}