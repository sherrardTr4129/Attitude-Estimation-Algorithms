#pragma once

#include "../../Euler/Euler.hpp"
#include "../../Matrix/Matrix.hpp"
#include "../../Quaternion/Quaternion.hpp"
#include <stdint.h>

namespace filters {
class ComplementaryFilter {
public:
  ComplementaryFilter(float alpha_gain);
  ComplementaryFilter(const ComplementaryFilter &other) = delete;
  ComplementaryFilter &operator=(const ComplementaryFilter &other) = delete;
  structures::Quaternion<double> update(structures::Matrix<double, 3, 1> acc_readings,
                                  structures::Matrix<double, 3, 1> gyro_readings,
                                  structures::Matrix<double, 3, 1> mag_readings,
                                  uint32_t delta_t_ms);

private:
  float _alpha_gain;
  structures::Euler<double> _last_update_euler;
}; // end ComplementaryFilter class
} // namespace filters
