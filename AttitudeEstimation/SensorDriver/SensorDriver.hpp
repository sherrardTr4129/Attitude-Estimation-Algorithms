#pragma once

#include "../EstimationAlgs/ComplementaryFilter/ComplementaryFilter.hpp"
#include "../Matrix/Matrix.hpp"
#include "../Quaternion/Quaternion.hpp"
#include "AlgParams.hpp"
#include "Nicla_System.h"
#include "memory.h"

// define a few macros to do unit conversion
#define EARTH_G_MSS 9.81
#define ACCEL_SENSITIVITY 4096 // LSB/g
#define GYRO_SENSITIVITY 16.4  // LSB/deg/sec
#define MAG_SENSITIVITY 16     // LSB/uT
#define DEG_SEC_TO_RAD_SEC(x)                                                  \
  (x * 0.017453292519943) // convert from deg/sec to rad/sec
#define ACC_TO_MSS(x)                                                          \
  (x * (EARTH_G_MSS / ACCEL_SENSITIVITY)) // convert from ADC reading to m/sec^s
#define GYRO_TO_DEG_SEC(x)                                                     \
  (x * (1.0 / GYRO_SENSITIVITY)) // convert from ADC reading to deg/sec
#define MAG_TO_uT(x)                                                           \
  (x * (1.0 / MAG_SENSITIVITY)) // convert from ADC reading to uT

namespace filters {

/**
 * @brief enum to hold available filter types.
 */
typedef enum { COMPLEMENTARY, EKF, MADGWICK, MAHONY } available_filters_t;

/**
 * @brief a class to perform an update operation on our selected filter.
 */
class FilterDriver {
public:
  /**
   * @brief generic filter update function. NOTE: all reading matricies
   * are expected to be packed in <X, Y, Z> axis order.
   * @param acc_mat accelerometer reading matrix.
   * @param gyro_mat gyroscope reading matrix.
   * @param mag_mat magnetometer reading matrix.
   * @param ellapsed_time elapsed time since last update.
   * @return a Quaternion instance with the newly estimated attitude.
   */
  virtual structures::Quaternion<double>
  update(structures::Matrix<double, 3, 1> acc_mat,
         structures::Matrix<double, 3, 1> gyro_mat,
         structures::Matrix<double, 3, 1> mag_mat, uint32_t ellapsed_time) = 0;
}; // end FilterDriver class

/**
 * @brief a class to perform an update operation on a complementary filter.
 */
class ComplementaryDriver : public FilterDriver {
public:
  /**
   * @brief ComplementaryDriver constructor
   */
  ComplementaryDriver() : _comp_filt(COMP_FILTER_ALPHA_GAIN) {}

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
  update(structures::Matrix<double, 3, 1> acc_mat,
         structures::Matrix<double, 3, 1> gyro_mat,
         structures::Matrix<double, 3, 1> mag_mat,
         uint32_t ellapsed_time) override {

    // perform complementary filter update
    structures::Quaternion<double> new_quat_est =
        this->_comp_filt.update(acc_mat, gyro_mat, mag_mat, ellapsed_time);

    return new_quat_est;
  }

private:
  ComplementaryFilter _comp_filt;
}; // end ComplementaryDriver class

/**
 * @brief a class to perform an update operation on a EKF filter.
 */
class EKFDriver : public FilterDriver {
public:
  /**
   * @brief EKF filter update function. NOTE: all reading matricies
   * are expected to be packed in <X, Y, Z> axis order.
   * @param acc_mat accelerometer reading matrix.
   * @param gyro_mat gyroscope reading matrix.
   * @param mag_mat magnetometer reading matrix.
   * @param ellapsed_time elapsed time since last update.
   * @return a Quaternion instance with the newly estimated attitude.
   */
  structures::Quaternion<double>
  update(structures::Matrix<double, 3, 1> acc_mat,
         structures::Matrix<double, 3, 1> gyro_mat,
         structures::Matrix<double, 3, 1> mag_mat,
         uint32_t ellapsed_time) override {

    // TODO: Implement me
    structures::Quaternion<double> new_quat_est;
    return new_quat_est;
  }
}; // end EKFDriver class

/**
 * @brief a class to perform an update operation on a Madgwick filter.
 */
class MadgwickDriver : public FilterDriver {
public:
  /**
   * @brief Madgwick filter update function. NOTE: all reading matricies
   * are expected to be packed in <X, Y, Z> axis order.
   * @param acc_mat accelerometer reading matrix.
   * @param gyro_mat gyroscope reading matrix.
   * @param mag_mat magnetometer reading matrix.
   * @param ellapsed_time elapsed time since last update.
   * @return a Quaternion instance with the newly estimated attitude.
   */
  structures::Quaternion<double>
  update(structures::Matrix<double, 3, 1> acc_mat,
         structures::Matrix<double, 3, 1> gyro_mat,
         structures::Matrix<double, 3, 1> mag_mat,
         uint32_t ellapsed_time) override {

    // TODO: Implement me
    structures::Quaternion<double> new_quat_est;
    return new_quat_est;
  }
}; // end MadgwickDriver class

/**
 * @brief a class to perform an update operation on a Mahony filter.
 */
class MahonyDriver : public FilterDriver {
public:
  /**
   * @brief Mahony filter update function. NOTE: all reading matricies
   * are expected to be packed in <X, Y, Z> axis order.
   * @param acc_mat accelerometer reading matrix.
   * @param gyro_mat gyroscope reading matrix.
   * @param mag_mat magnetometer reading matrix.
   * @param ellapsed_time elapsed time since last update.
   * @return a Quaternion instance with the newly estimated attitude.
   */
  structures::Quaternion<double>
  update(structures::Matrix<double, 3, 1> acc_mat,
         structures::Matrix<double, 3, 1> gyro_mat,
         structures::Matrix<double, 3, 1> mag_mat,
         uint32_t ellapsed_time) override {

    // TODO: Implement me
    structures::Quaternion<double> new_quat_est;
    return new_quat_est;
  }
}; // end MahonyDriver class

class SensorManager {
public:
  /**
   * @brief constructor for the SensorManager class.
   * @param accelerometer pointer to the accelerometer SensorXYZ instance.
   * @param gyro pointer to the gyroscope SensorXYZ instance.
   * @param magnetometer pointer to the accelerometer SensorXYZ instance.
   * @param quaternion pointer to the internal quaternion estimation
   * SensorQuaternion instance.
   * @param selected_filter the filter that this instance of SensorManager will
   * use.
   */
  SensorManager(SensorXYZ *accelerometer, SensorXYZ *gyro,
                SensorXYZ *magnetometer, SensorQuaternion *quaternion,
                available_filters_t selected_filter) {

    // assign class members
    this->_accelerometer = accelerometer;
    this->_gyro = gyro;
    this->_magnetometer = magnetometer;
    this->_ground_truth_quat = quaternion;
    this->_selected_filter = selected_filter;
    this->_last_update = 0U;

    // create filter object based on selected_filter input
    switch (this->_selected_filter) {
    case COMPLEMENTARY:
      this->_filter_driver = std::make_unique<ComplementaryDriver>();
      break;
    case EKF:
      this->_filter_driver = std::make_unique<EKFDriver>();
      break;
    case MADGWICK:
      this->_filter_driver = std::make_unique<MadgwickDriver>();
      break;
    case MAHONY:
      this->_filter_driver = std::make_unique<MahonyDriver>();
      break;
    }
  }

  /**
   * @brief handles running the selected filter on new data.
   */
  void run() {

    // initialize last update value with current time
    this->_last_update = millis();
    while (true) {
      // get new sensor readings
      BHY2.update();

      // pack sensor readings into arrays
      double accelerometer_readings[3][1] = {
          {ACC_TO_MSS(this->_accelerometer->x())},
          {ACC_TO_MSS(this->_accelerometer->y())},
          {ACC_TO_MSS(this->_accelerometer->z())}};
      double gyro_readings[3][1] = {
          {DEG_SEC_TO_RAD_SEC(GYRO_TO_DEG_SEC(this->_gyro->x()))},
          {DEG_SEC_TO_RAD_SEC(GYRO_TO_DEG_SEC(this->_gyro->y()))},
          {DEG_SEC_TO_RAD_SEC(GYRO_TO_DEG_SEC(this->_gyro->z()))}};
      double magnetometer_readings[3][1] = {
          {MAG_TO_uT(this->_magnetometer->x())},
          {MAG_TO_uT(this->_magnetometer->y())},
          {MAG_TO_uT(this->_magnetometer->z())}};

      // construct matrix objects
      structures::Matrix<double, 3, 1> acc_mat(accelerometer_readings);
      structures::Matrix<double, 3, 1> gyro_mat(gyro_readings);
      structures::Matrix<double, 3, 1> mag_mat(magnetometer_readings);

      // get elapsed time since last update
      uint32_t ellapsed_time = millis() - this->_last_update;

      // perform update
      structures::Quaternion<double> estimated_quat =
          this->_filter_driver->update(acc_mat, gyro_mat, mag_mat,
                                       ellapsed_time);

      // update ellapsed_time
      this->_last_update = millis();

      // format json message and print to serial monitor
      char final_json_char_arr[512];
      sprintf(final_json_char_arr, this->_JSON_format_patt,
              this->_ground_truth_quat->w(), this->_ground_truth_quat->x(),
              this->_ground_truth_quat->y(), this->_ground_truth_quat->z(),
              estimated_quat.getW(), estimated_quat.getX(),
              estimated_quat.getY(), estimated_quat.getZ());

      Serial.println(final_json_char_arr);
    }
  }

private:
  std::unique_ptr<FilterDriver> _filter_driver;
  SensorXYZ *_accelerometer;
  SensorXYZ *_gyro;
  SensorXYZ *_magnetometer;
  SensorQuaternion *_ground_truth_quat;
  available_filters_t _selected_filter;
  uint32_t _last_update;
  char _JSON_format_patt[200] =
      "{\"ground_truth_quat\": {\"w\": %f, \"x\": %f, \"y\": %f, \"z\": "
      "%f},\"estimated_quat\": {\"w\": %f,\"x\": %f,\"y\": %f,\"z\": %f}}\n";
};
} // namespace filters
