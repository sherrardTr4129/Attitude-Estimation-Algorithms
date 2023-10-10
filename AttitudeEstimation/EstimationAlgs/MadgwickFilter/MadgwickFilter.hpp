#pragma once

#include "../../Matrix/Matrix.hpp"
#include "../../Quaternion/Quaternion.hpp"

namespace filters {
class MadgwickFilter {
public:
  /**
   * @brief default constructor for MadgwickFilter class.
   */
  MadgwickFilter() { this->_beta_filter_gain = 0; }

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
   * @param ellapsed_time_us elapsed time in microseconds since last update.
   * @return a Quaternion instance with the newly estimated attitude.
   */
  structures::Quaternion<double>
  update(structures::Matrix<double, 3, 1> acc_readings,
         structures::Matrix<double, 3, 1> gyro_readings,
         structures::Matrix<double, 3, 1> mag_readings,
         uint32_t ellapsed_time_us) {

    // compute Q_dot
    structures::Quaternion<double> qyro_quat(gyro_readings.getValue(0, 0),
                                             gyro_readings.getValue(1, 0),
                                             gyro_readings.getValue(2, 0), 0);

    structures::Quaternion<double> q_dot = (this->_last_quat * qyro_quat) * 0.5;

    // compute the norm of the acceleration measurement
    double acc_norm = acc_readings.norm();
    double mag_norm = mag_readings.norm();

    // if it's nonzero, compute the gradient and update qDot
    if (acc_norm > 0) {
      // normalize acceleration and magnetometer measurements
      structures::Matrix<double, 3, 1> a_normalized =
          acc_readings * (1 / acc_norm);
      structures::Matrix<double, 3, 1> m_normalized =
          mag_readings * (1 / mag_norm);

      // rotate normalized magnetometer measurements
      structures::Quaternion<double> norm_mag_quat(
          m_normalized.getValue(0, 0), m_normalized.getValue(1, 0),
          m_normalized.getValue(2, 0), 0);

      structures::Quaternion<double> h_quat =
          this->_last_quat * (norm_mag_quat * this->_last_quat.conj());
      double bx = pow(pow(h_quat.getX(), 2) + pow(h_quat.getY(), 2), 0.5);
      double bz = h_quat.getZ();

      // normalize quaternion and compute objective function.
      structures::Quaternion<double> last_quat_norm = this->_last_quat.norm();
      double qw = last_quat_norm.getW();
      double qx = last_quat_norm.getX();
      double qy = last_quat_norm.getY();
      double qz = last_quat_norm.getZ();

      double objective_vec[6][1] = {
          {2.0 * (qx * qz - qw * qy) - a_normalized.getValue(0, 0)},
          {2.0 * (qw * qx + qy * qz) - a_normalized.getValue(1, 0)},
          {2.0 * (0.5 - pow(qx, 2) - pow(qy, 2)) - a_normalized.getValue(2, 0)},
          {2.0 * bx * (0.5 - pow(qy, 2) - pow(qz, 2)) +
           2.0 * bz * (qx * qz - qw * qy) - m_normalized.getValue(0, 0)},
          {2.0 * bx * (qx * qy - qw * qz) + 2.0 * bz * (qw * qx + qy * qz) -
           m_normalized.getValue(1, 0)},
          {2.0 * bx * (qw * qy + qx * qz) +
           2.0 * bz * (0.5 - pow(qx, 2) - pow(qy, 2)) -
           m_normalized.getValue(2, 0)}};

      // compute jacobian
      double jacobian_vec[6][4] = {
          {-2.0 * qy, 2.0 * qz, -2.0 * qw, 2.0 * qx},
          {2.0 * qx, 2.0 * qw, 2.0 * qz, 2.0 * qy},
          {0.0, -4.0 * qx, -4.0 * qy, 0.0},
          {-2.0 * bz * qy, 2.0 * bz * qz, -4.0 * bx * qy - 2.0 * bz * qw,
           -4.0 * bx * qz + 2.0 * bz * qx},
          {-2.0 * bx * qz + 2.0 * bz * qx, 2.0 * bx * qy + 2.0 * bz * qw,
           2.0 * bx * qx + 2.0 * bz * qz, -2.0 * bx * qw + 2.0 * bz * qy},
          {2.0 * bx * qy, 2.0 * bx * qz - 4.0 * bz * qx,
           2.0 * bx * qw - 4.0 * bz * qy, 2.0 * bx * qx}};

      // compute gradient
      structures::Matrix<double, 6, 1> objective_mat(objective_vec);
      structures::Matrix<double, 6, 4> jacobian_mat(jacobian_vec);
      structures::Matrix<double, 4, 1> gradient_mat =
          jacobian_mat.transpose() * objective_mat;

      // normalize gradient
      gradient_mat = gradient_mat * (1 / gradient_mat.norm());

      // adjust gradient by beta gain
      gradient_mat = gradient_mat * this->_beta_filter_gain;

      // adjust q_dot
      q_dot.setW(q_dot.getW() - gradient_mat.getValue(0, 0));
      q_dot.setX(q_dot.getX() - gradient_mat.getValue(1, 0));
      q_dot.setY(q_dot.getY() - gradient_mat.getValue(2, 0));
      q_dot.setZ(q_dot.getZ() - gradient_mat.getValue(3, 0));
    }

    // perform discretized integration
    double ellapsed_time_sec = (ellapsed_time_us) / ((double)1e6);
    q_dot = q_dot * ellapsed_time_sec;

    // update internal quaternion estimate
    this->_last_quat.setW(this->_last_quat.getW() + q_dot.getW());
    this->_last_quat.setX(this->_last_quat.getX() + q_dot.getX());
    this->_last_quat.setY(this->_last_quat.getY() + q_dot.getY());
    this->_last_quat.setZ(this->_last_quat.getZ() + q_dot.getZ());
    this->_last_quat = this->_last_quat.norm();

    return this->_last_quat;
  }

private:
  structures::Quaternion<double> _last_quat;
  double _beta_filter_gain;

}; // end MadgwickFilter class
} // end namespace filters