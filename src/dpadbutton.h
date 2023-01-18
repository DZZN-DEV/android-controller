#ifndef DPADBUTTON_H
#define DPADBUTTON_H

#include "gamepadbutton.h"

class DPadButton : public GamepadButton {
 public:
  enum class Direction { Up, Down, Left, Right };
  DPadButton(QWidget* parrent = nullptr,
             std::function<void(bool)> const& sendButtonState = {},
             Direction dir = Direction::Right, int fixedSize = 75);

 protected:
  Direction m_direction;

  void paintEvent(QPaintEvent* event) override;
};

#endif  // DPADBUTTON_H
