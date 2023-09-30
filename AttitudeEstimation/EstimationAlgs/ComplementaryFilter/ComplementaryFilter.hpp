#pragma once

#include "../../Euler/Euler.hpp"
#include "../../Matrix/Matrix.hpp"
#include "../../Quaternion/Quaternion.hpp"
#include <stdint.h>

namespace filters {
class ComplementaryFilter {
public:
  /**
   * @brief constructor for ComplementaryFilter class
   */
  ComplementaryFilter() {
    this->_alpha_gain = 0.0;
    this->_last_update_euler =
        structures::Euler<double>(0, 0, 0, structures::RADIANS);
  }

  /**
   * @brief copy constructor for ComplementaryFilter class
   */
  ComplementaryFilter(const ComplementaryFilter& other) {
    this->_alpha_gain = other._alpha_gain;
    this->_last_update_euler = other._last_update_euler;
  }

  /**
   * @brief copy assignment operator overload for ComplementaryFilter class
   */
  ComplementaryFilter operator=(const ComplementaryFilter& other) {
    this->_alpha_gain = other._alpha_gain;
    this->_last_update_euler = other._last_update_euler;

    return *this;
  }

  /**
   * @brief constructor for ComplementaryFilter class.
   * @param alpha_gain the complementery gain to use when combining
   * orientation measured from accelerometer and magnetometer, and
   * gyroscope. A higher value for alpha_gain results in more preference
   * given to the gyroscope estimation, and a lower value results in more
   * preference given to the accelerometer and magnetometer estimation.
   */
  ComplementaryFilter(float alpha_gain) {
    this->_alpha_gain = alpha_gain;
    this->_last_update_euler =
        structures::Euler<double>(0, 0, 0, structures::RADIANS);
  }

  /**
   * @brief Complementary filter update function. NOTE: all reading matricies
   * are expected to be packed in <X, Y, Z> axis order.
   * @param acc_mat accelerometer reading matrix.
   * @param gyro_mat gyroscope reading matrix.
   * @param mag_mat magnetometer reading matrix.
   * @param ellapsed_time elapsed time since last update.
   * @return a Quaternion instance with the newly estimated attitude.
   */
  structures::Quaternion<double>
  update(structures::Matrix<double, 3, 1> acc_readings,
         structures::Matrix<double, 3, 1> gyro_readings,
         structures::Matrix<double, 3, 1> mag_readings, uint32_t delta_t_ms) {
    // compute tilt angles from accelerometer readings
    double theta_x =
        atan2(acc_readings.getValue(1, 0), acc_readings.getValue(2, 0));
    double ay_az_mag = sqrt(pow(acc_readings.getValue(1, 0), 2) +
                            pow(acc_readings.getValue(2, 0), 2));
    double theta_y = atan2(-acc_readings.getValue(0, 0), ay_az_mag);

    // need to compute z angle using magnetometer readings
    structures::Matrix<double, 3, 3> mag_field_comp;
    mag_field_comp.setValue(0, 0, cos(theta_x));
    mag_field_comp.setValue(0, 1, sin(theta_x) * sin(theta_y));
    mag_field_comp.setValue(0, 2, sin(theta_x) * cos(theta_y));
    mag_field_comp.setValue(1, 0, 0.0);
    mag_field_comp.setValue(1, 1, cos(theta_y));
    mag_field_comp.setValue(1, 2, -sin(theta_y));
    mag_field_comp.setValue(2, 0, -sin(theta_x));
    mag_field_comp.setValue(2, 1, cos(theta_x) * sin(theta_y));
    mag_field_comp.setValue(2, 2, cos(theta_x) * cos(theta_y));

    structures::Matrix<double, 3, 1> mag_field_comp_post_mul =
        mag_field_comp * mag_readings;

    // compute theta_z
    double theta_z = atan2(-mag_field_comp_post_mul.getValue(1, 0),
                           mag_field_comp_post_mul.getValue(0, 0));

    // construct Euler that was estimated from accelerometer and magnetometer
    // data
    structures::Euler<double> euler_accel_mag(theta_x, theta_y, theta_z,
                                              structures::RADIANS);

    // now estimate the orientation from the gyroscope readings alone
    double delta_t_sec = delta_t_ms / 1000.0;

    // perform basic numerical integration to get angle from angular rates
    theta_x = gyro_readings.getValue(0, 0) * delta_t_sec;
    theta_y = gyro_readings.getValue(1, 0) * delta_t_sec;
    theta_z = gyro_readings.getValue(2, 0) * delta_t_sec;
    structures::Euler<double> euler_gyro_instantaneous(
        theta_x, theta_y, theta_z, structures::RADIANS);

    // add angle to previous angle
    structures::Euler<double> euler_gyro =
        this->_last_update_euler + euler_gyro_instantaneous;

    // compute final euler angle based on provided weight
    structures::Euler<double> final_euler =
        euler_gyro * this->_alpha_gain +
        euler_accel_mag * (1 - this->_alpha_gain);

    return final_euler.toQuaternion();
  }

private:
  float _alpha_gain;
  structures::Euler<double> _last_update_euler;
}; // end ComplementaryFilter class
} // namespace filters
