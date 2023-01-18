#include "gamepad.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QScreen>

#include "controller_data.hpp"
#include "dpadbutton.h"
#include "gamepadellipsebutton.h"
#include "gamepadrectbutton.h"
#include "joystick.h"
#include "util.h"

Gamepad::Gamepad(QWidget* parent,
                 std::function<void(QByteArray const&)> const& sendData)
    : QWidget(parent),
      m_sendData(sendData),
      m_accelerometer(this),
      m_gyroscope(this),
      m_timer(this) {
  const QSize screenSize = qApp->screens().first()->size();
  const qreal ratio = 0.06;
  const qreal marginRatio = 0.5;
  int const controllWidth = screenSize.width() * ratio;
  int const controllHeight = screenSize.height() * ratio;
  int const margin = controllWidth * marginRatio;

  QHBoxLayout* mainLayout = new QHBoxLayout(this);

  auto addButtonsToLayout = [&](auto const& buttons, QVBoxLayout* layout) {
    for (auto&& buttonElem : buttons) {
      QString buttonText;
      button buttonCode;
      std::tie(buttonText, buttonCode) = buttonElem;
      GamepadEllipseButton* ellpiseButton = new GamepadEllipseButton(
          this, buttonText,
          [=, this](bool val) { sendButtonData(buttonCode, val); },
          controllWidth, controllWidth);
      layout->addWidget(ellpiseButton);
    }
  };

  {
    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->setContentsMargins(margin * 2, 0, 0, 0);
    mainLayout->addLayout(leftLayout);
    leftLayout->setAlignment(Qt::AlignTop);
    std::list<std::tuple<QString, button>> leftTriggers{
        {"L", button::TRIGGER_LEFT1}, {"L2", button::TRIGGER_LEFT2}};
    addButtonsToLayout(leftTriggers, leftLayout);
  }

  QVBoxLayout* middleLayout = new QVBoxLayout();
  mainLayout->addLayout(middleLayout);
  QHBoxLayout* controlsLayout = new QHBoxLayout();
  middleLayout->addLayout(controlsLayout);

  {
    QGridLayout* dpadLayout = new QGridLayout();

    controlsLayout->addLayout(dpadLayout);
    std::list<std::tuple<std::tuple<int, int>, button, DPadButton::Direction>>
        dpadButtons = {
            {{2, 1}, button::DPAD_DOWN, DPadButton::Direction::Down},
            {{1, 2}, button::DPAD_RIGHT, DPadButton::Direction::Right},
            {{1, 0}, button::DPAD_LEFT, DPadButton::Direction::Left},
            {{0, 1}, button::DPAD_UP, DPadButton::Direction::Up}};
    for (auto&& buttonElem : dpadButtons) {
      std::tuple<int, int> gridPos;
      int row;
      int col;
      button buttonCode;
      DPadButton::Direction dir;
      std::tie(gridPos, buttonCode, dir) = buttonElem;
      std::tie(row, col) = gridPos;
      DPadButton* dpadButton = new DPadButton(
          this, [=, this](bool val) { sendButtonData(buttonCode, val); }, dir,
          controllWidth);
      dpadLayout->addWidget(dpadButton, row, col);
    }
  }

  {
    QHBoxLayout* rectButtonsLayout = new QHBoxLayout();
    controlsLayout->addLayout(rectButtonsLayout);
    std::list<std::tuple<QString, button>> rectButtons = {
        {"Select", button::SELECT}, {"Start", button::START}};
    for (auto&& buttonElem : rectButtons) {
      QString buttonText;
      button buttonCode;
      std::tie(buttonText, buttonCode) = buttonElem;
      GamepadRectButton* rectButton = new GamepadRectButton(
          this, buttonText,
          [=, this](bool val) { sendButtonData(buttonCode, val); },
          controllWidth, controllHeight);
      rectButtonsLayout->addWidget(rectButton, 0, Qt::AlignCenter);
    }
  }

  {
    QGridLayout* rightButtonsLayout = new QGridLayout();

    controlsLayout->addLayout(rightButtonsLayout);
    std::list<std::tuple<std::tuple<int, int>, QString, button>> rightButtons =
        {{{2, 1}, "A", button::A},
         {{1, 2}, "B", button::B},
         {{1, 0}, "X", button::X},
         {{0, 1}, "Y", button::Y}};
    for (auto&& buttonElem : rightButtons) {
      std::tuple<int, int> gridPos;
      int row;
      int col;
      QString buttonText;
      button buttonCode;
      std::tie(gridPos, buttonText, buttonCode) = buttonElem;
      std::tie(row, col) = gridPos;
      GamepadEllipseButton* ellipseButton = new GamepadEllipseButton(
          this, buttonText,
          [=, this](bool val) { sendButtonData(buttonCode, val); },
          controllWidth, controllWidth);
      rightButtonsLayout->addWidget(ellipseButton, row, col);
    }
  }

  {
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    bottomLayout->setContentsMargins(margin, margin * 0.25, margin,
                                     margin * 0.25);
    middleLayout->addLayout(bottomLayout);
    std::vector<std::tuple<axis, axis, Qt::AlignmentFlag>> joysticksAxes = {
        {axis::X, axis::Y, Qt::AlignLeft},
        {axis::RX, axis::RY, Qt::AlignRight}};

    for (auto&& joystickAxes : joysticksAxes) {
      axis xAxis, yAxis;
      Qt::AlignmentFlag alignFlag;
      std::tie(xAxis, yAxis, alignFlag) = joystickAxes;
      Joystick* joystick = new Joystick(
          this,
          [=, this](qreal x, qreal y) {
            sendAxisData(xAxis, x);
            sendAxisData(yAxis, y);
          },
          controllWidth * 2);
      bottomLayout->addWidget(joystick, 0, alignFlag);
    }
  }

  {
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(0, 0, margin * 2, 0);
    mainLayout->addLayout(rightLayout);
    rightLayout->setAlignment(Qt::AlignTop);
    std::list<std::tuple<QString, button>> leftTriggers{
        {"R", button::TRIGGER_RIGHT1}, {"R2", button::TRIGGER_RIGHT2}};
    addButtonsToLayout(leftTriggers, rightLayout);
  }

  setMinimumSize(minimumSizeHint());

  m_timer.start(m_timerInterval);
  m_timer.callOnTimeout(this, [=, this]() { sendGyroData(); });
}
void Gamepad::enableGyro() {
  m_accelerometer.start();
  m_gyroscope.start();
  m_doSendGyro = true;
}
void Gamepad::disableGyro() {
  m_doSendGyro = false;
  m_accelerometer.stop();
  m_gyroscope.stop();
  QByteArray byteArray;
  append(byteArray, std::make_tuple(qToUnderlying(input_type::GYRO), 0.f, 0.f,
                                    0.f, 0.f, 0.f, 0.f));
  m_sendData(byteArray);
}
void Gamepad::sendGyroData() {
  if (m_doSendGyro) {
    auto accelReading = m_accelerometer.reading();
    auto gyroReading = m_gyroscope.reading();
    if (accelReading && gyroReading) {
      QByteArray byteArray;
      qreal accelX = accelReading->x();
      qreal accelY = accelReading->y();
      qreal accelZ = accelReading->z();
      qreal gyroX = gyroReading->x();
      qreal gyroY = gyroReading->y();
      qreal gyroZ = gyroReading->z();

      append(byteArray, std::make_tuple(qToUnderlying(input_type::GYRO), accelX,
                                        accelY, accelZ, gyroX, gyroY, gyroZ));
      m_sendData(byteArray);
    }
  }
}
void Gamepad::sendAxisData(axis code, qreal val) {
  QByteArray byteArray;
  append(byteArray, std::make_tuple(qToUnderlying(input_type::AXIS),
                                    qToUnderlying(code), val));
  m_sendData(byteArray);
}
void Gamepad::sendButtonData(button code, int val) {
  QByteArray byteArray;
  append(byteArray, std::make_tuple(qToUnderlying(input_type::KEY),
                                    qToUnderlying(code), val));
  m_sendData(byteArray);
}
