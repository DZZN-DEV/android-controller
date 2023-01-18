#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <QAccelerometer>
#include <QByteArray>
#include <QGyroscope>
#include <QTimer>
#include <QWidget>

#include "controller_data.hpp"

class Gamepad : public QWidget {
 private:
  std::function<void(QByteArray const&)> m_sendData;
  QAccelerometer m_accelerometer;
  QGyroscope m_gyroscope;
  QTimer m_timer;
  int const m_timerInterval = 50;
  bool m_doSendGyro = false;

  void sendButtonData(button code, int val);
  void sendAxisData(axis code, qreal val);
  void sendGyroData();

 public:
  Gamepad(QWidget* parent = nullptr,
          std::function<void(QByteArray const&)> const& sendData = {});

  void enableGyro();
  void disableGyro();
};

#endif  // GAMEPAD_H
