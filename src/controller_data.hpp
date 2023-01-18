#ifndef CONTROLLER_DATA_HPP
#define CONTROLLER_DATA_HPP
#include <cstdint>

const uint8_t controller_version = 1;

enum class input_type : char { KEY = 1, GYRO = 2, AXIS = 3 };

enum class button : uint16_t {
  A = 0,
  B,
  X,
  Y,
  TRIGGER_LEFT1,
  TRIGGER_RIGHT1,
  TRIGGER_LEFT2,
  TRIGGER_RIGHT2,
  SELECT,
  START,
  DPAD_UP,
  DPAD_DOWN,
  DPAD_LEFT,
  DPAD_RIGHT
};

enum class button_state : uint8_t { OFF = 0, ON = 1 };

enum class axis : uint16_t {
  X = 0,
  Y,
  RX,
  RY,
  ACCEL_X,
  ACCEL_Y,
  ACCEL_Z,
  GYRO_X,
  GYRO_Y,
  GYRO_Z
};

#endif
