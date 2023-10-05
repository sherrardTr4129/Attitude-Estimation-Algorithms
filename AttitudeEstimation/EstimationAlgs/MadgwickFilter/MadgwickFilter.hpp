#pragma once

#include "../../Matrix/Matrix.hpp"
#include "../../Quaternion/Quaternion.hpp"

namespace filters {
class MadgwickFilter {
public:
  /**
   * @brief constructor for MadgwickFilter class.
   */
  MadgwickFilter(double beta_filter_gain) {
    this->_beta_filter_gain = beta_filter_gain;
  }

  /**
   * @brief copy constructor for MadgwickFilter class.
   */
  MadgwickFilter(const MadgwickFilter &other) {
    this->_last_quat = other._last_quat;
    this->_beta_filter_gain = other._beta_filter_gain;
  }

  /**
   * @brief copy assignment operator override for
   * MadgwickFilter class.
   */
  MadgwickFilter operator=(const MadgwickFilter &other) {
    this->_last_quat = other._last_quat;
    this->_beta_filter_gain = other._beta_filter_gain;
    return *this;
  }

  /**
   * @brief Madgwick filter update function. NOTE: all reading matricies
   * are expected to be packed in <X, Y, Z> axis order.
   * @param acc_mat accelerometer reading matrix.
   * @param gyro_mat gyroscope reading matrix.
   * @param mag_mat magnetometer reading matrix.
   * @param ellapsed_time elapsed time in microseconds since last update.
   * @return a Quaternion instance with the newly estimated attitude.
   */
  structures::Quaternion<double>
  update(structures::Matrix<double, 3, 1> acc_readings,
         structures::Matrix<double, 3, 1> gyro_readings,
         structures::Matrix<double, 3, 1> mag_readings,
         uint32_t ellapsed_time) {}

private:
  structures::Quaternion<double> _last_quat;
  double _beta_filter_gain;

}; // end MadgwickFilter class
} // end namespace filters