#pragma once

#include "../../Matrix/Matrix.hpp"
#include "../../Quaternion/Quaternion.hpp"
#include <Arduino.h>

namespace filters {
class MahonyFilter {
public:
  /**
   * @brief default constructor
   * @return a new MahonyFilter instance
   */
  MahonyFilter() {
    this->_kI = 0.0;
    this->_kP = 0.0;
  }

  /**
   * @brief default constructor
   * @param kI integral gain
   * @param kP proportional gain
   * @return a new MahonyFilter instance
   */
  MahonyFilter(double kI, double kP) {
    this->_kI = kI;
    this->_kP = kP;
  }

  /**
   * @brief copy constructor
   * @param other the other filter instance to copy
   * into this instance.
   * @return a new MahonyFilter instance
   */
  MahonyFilter(const MahonyFilter &other) {
    this->_kI = other._kI;
    this->_kP = other._kP;
  }

  /**
   * @brief copy assignment operator.
   * @param other the other filter instance to copy
   * into this instance.
   * @return a new MahonyFilter instance
   */
  MahonyFilter operator=(const MahonyFilter &other) {
    this->_kI = other._kI;
    this->_kP = other._kP;
    return *this;
  }

  /**
   * @brief Mahony filter update function. NOTE: all reading matricies
   * are expected to be packed in <X, Y, Z> axis order.
   * @param acc_mat accelerometer reading matrix.
   * @param gyro_mat gyroscope reading matrix.
   * @param mag_mat magnetometer reading matrix.
   * @param ellapsed_time_us elapsed time in microseconds since last update.
   * @return a Quaternion instance with the newly estimated attitude.
   */
  structures::Quaternion<double>
  update(structures::Matrix<double, 3, 1> acc_readings,
         structures::Matrix<double, 3, 1> gyro_readings,
         structures::Matrix<double, 3, 1> mag_readings,
         uint32_t ellapsed_time_us) {

    // compute ellapsed time in seconds
    double delta_sec = ellapsed_time_us / ((double)1e6);

    // compute norm of acc_readings
    double a_norm = acc_readings.norm();

    if (a_norm > 0) {
      double m_norm = mag_readings.norm();

      acc_readings = acc_readings * (1 / a_norm);
      mag_readings = mag_readings * (1 / m_norm);

      structures::Matrix<double, 3, 3> dcm_mat =
          this->quatToDCM(this->_last_quat);

      double earth_grav_field[3][1] = {{0}, {0}, {1}};
      structures::Matrix<double, 3, 1> earth_grav_field_mat(earth_grav_field);

      structures::Matrix<double, 3, 1> v_a =
          dcm_mat.transpose() * earth_grav_field_mat;

      // rotate magnetic field to inertial frame
      structures::Matrix<double, 3, 1> h_mod = dcm_mat * mag_readings;

      double v_m_vec[3][1] = {
          {0},
          {pow(pow(h_mod.getValue(0, 0), 2) + pow(h_mod.getValue(1, 0), 2),
               0.5)},
          {h_mod.getValue(2, 0)}};

      structures::Matrix<double, 3, 1> v_m(v_m_vec);
      v_m = v_m * (1 / v_m.norm());

      // track changes in gyro bias
      structures::Matrix<double, 3, 1> omega_mes =
          this->cross(acc_readings, v_a) + this->cross(mag_readings, v_m);
      structures::Matrix<double, 3, 1> gyro_bias_dot =
          omega_mes * (-1 * this->_kI);

      // estimate gyro bias change
      this->_gyro_bias = this->_gyro_bias + (gyro_bias_dot * delta_sec);

      // perform gyro reading correction
      gyro_readings =
          gyro_readings - (this->_gyro_bias + (omega_mes * this->_kP));
    }

    // compute quaternion rate of change
    structures::Quaternion<double> p(gyro_readings.getValue(0, 0),
                                     gyro_readings.getValue(1, 0),
                                     gyro_readings.getValue(2, 0), 0.0);
    structures::Quaternion<double> q_dot = (this->_last_quat * p) * 0.5;

    // update orientation
    this->_last_quat = this->_last_quat + (q_dot * delta_sec);

    // normalize quaternion
    this->_last_quat = this->_last_quat.norm();

    // return a copy of the updated quaternion
    return this->_last_quat;
  }

private:
  /**
   * @brief function to compute direction cosine matrix
   * from quaternion.
   * @param q the quaternion to use.
   * @return the direction cosine matrix
   */
  structures::Matrix<double, 3, 3> quatToDCM(structures::Quaternion<double> q) {
    q = q.norm();

    double dcm_vec[3][3] = {
        {pow(q[0], 2) + pow(q[1], 2) - pow(q[2], 2) - pow(q[3], 2),
         2.0 * (q[1] * q[2] - q[0] * q[3]), 2.0 * (q[1] * q[3] + q[0] * q[2])},
        {2.0 * (q[1] * q[2] + q[0] * q[3]),
         pow(q[0], 2) - pow(q[1], 2) + pow(q[2], 2) - pow(q[3], 2),
         2.0 * (q[2] * q[3] - q[0] * q[1])},
        {2.0 * (q[1] * q[3] - q[0] * q[2]), 2.0 * (q[0] * q[1] + q[2] * q[3]),
         pow(q[0], 2) - pow(q[1], 2) - pow(q[2], 2) + pow(q[3], 2)}};

    structures::Matrix<double, 3, 3> dcm_mat(dcm_vec);
    return dcm_mat;
  }

  /**
   * @brief cross product operator for two 3D vectors
   * @param a the first vector in the cross operation
   * @param b the second vector in the cross operation
   */
  structures::Matrix<double, 3, 1> cross(structures::Matrix<double, 3, 1> a,
                                         structures::Matrix<double, 3, 1> b) {
    double cross_res_vec[3][1] = {{a.getValue(1, 0) * b.getValue(2, 0) -
                                   a.getValue(2, 0) * b.getValue(1, 0)},
                                  {a.getValue(2, 0) * b.getValue(0, 0) -
                                   a.getValue(0, 0) * b.getValue(2, 0)},
                                  {a.getValue(0, 0) * b.getValue(1, 0) -
                                   a.getValue(1, 0) * b.getValue(0, 0)}};

    structures::Matrix<double, 3, 1> cross_res_mat(cross_res_vec);
    return cross_res_mat;
  }

  double _kI;
  double _kP;
  structures::Matrix<double, 3, 1> _gyro_bias;
  structures::Quaternion<double> _last_quat;
};
} // namespace filters