#include "EstimationAlgs/ComplementaryFilter/ComplementaryFilter.hpp"
#include "Euler/Euler.hpp"
#include "Matrix/Matrix.hpp"
#include "math.h"

namespace filters {
ComplementaryFilter::ComplementaryFilter(float alpha_gain) {
  this->_alpha_gain = alpha_gain;
  this->_last_update_euler =
      structures::Euler<float>(0, 0, 0, structures::RADIANS);
}

structures::Euler<float> ComplementaryFilter::update(structures::Matrix<float, 3, 1> acc_readings,
                                structures::Matrix<float, 3, 1> gyro_readings,
                                structures::Matrix<float, 3, 1> mag_readings,
                                uint32_t delta_t_ms) {

  // compute tilt angles from accelerometer readings
  float theta_x =
      atan2(acc_readings.getValue(1, 0), acc_readings.getValue(2, 0));
  float ay_az_mag = sqrt(pow(acc_readings.getValue(1, 0), 2) +
                         pow(acc_readings.getValue(2, 0), 2));
  float theta_y = atan2(-acc_readings.getValue(0, 0), ay_az_mag);

  // need to compute z angle using magnetometer readings
  structures::Matrix<float, 3, 3> mag_field_comp;
  mag_field_comp.setValue(0, 0, cos(theta_x));
  mag_field_comp.setValue(0, 1, sin(theta_x) * sin(theta_y));
  mag_field_comp.setValue(0, 2, sin(theta_x) * cos(theta_y));
  mag_field_comp.setValue(1, 0, 0.0);
  mag_field_comp.setValue(1, 1, cos(theta_y));
  mag_field_comp.setValue(1, 2, -sin(theta_y));
  mag_field_comp.setValue(2, 0, -sin(theta_x));
  mag_field_comp.setValue(2, 1, cos(theta_x) * sin(theta_y));
  mag_field_comp.setValue(2, 2, cos(theta_x) * cos(theta_y));

  structures::Matrix<float, 3, 1> mag_field_comp_post_mul =
      mag_field_comp * mag_readings;

  // compute theta_z
  float theta_z = atan2(-mag_field_comp_post_mul.getValue(1, 0),
                        mag_field_comp_post_mul.getValue(0, 0));

  // construct Euler that was estimated from accelerometer and magnetometer data
  structures::Euler<float> euler_accel_mag(theta_x, theta_y, theta_z, structures::RADIANS);

  // now estimate the orientation from the gyroscope readings alone
  float delta_t_sec = delta_t_ms/1000.0;
  theta_x = this->_last_update_euler.getX().getAngleValue() + gyro_readings.getValue(0, 0)*delta_t_sec;
  theta_y = this->_last_update_euler.getY().getAngleValue() + gyro_readings.getValue(1, 0)*delta_t_sec;
  theta_z = this->_last_update_euler.getZ().getAngleValue() + gyro_readings.getValue(2, 0)*delta_t_sec;

  // construct Euler that was estimated from gyroscope data
  structures::Euler<float> euler_gyro(theta_x, theta_y, theta_z, structures::RADIANS);
}
} // namespace filters