#pragma once

#include "../../Euler/Euler.hpp"
#include "../../Matrix/Matrix.hpp"
#include <stdint.h>

namespace filters {
class ComplementaryFilter {
public:
  ComplementaryFilter(float alpha_gain);
  ComplementaryFilter(const ComplementaryFilter &other) = delete;
  ComplementaryFilter &operator=(const ComplementaryFilter &other) = delete;
  structures::Euler<float> update(structures::Matrix<float, 3, 1> acc_readings,
                                  structures::Matrix<float, 3, 1> gyro_readings,
                                  structures::Matrix<float, 3, 1> mag_readings,
                                  uint32_t delta_t_ms);

private:
  float _alpha_gain;
  structures::Euler<float> _last_update_euler;
}; // end ComplementaryFilter class
} // namespace filters
