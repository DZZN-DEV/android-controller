#ifndef GAMEPADELLIPSEBUTTON_H
#define GAMEPADELLIPSEBUTTON_H

#include "gamepadnamedbutton.h"

class GamepadEllipseButton : public GamepadNamedButton {
 public:
  GamepadEllipseButton(QWidget* parent = nullptr, QString buttonText = {},
                       std::function<void(bool)> sendButtonState = {},
                       int fixedWidth = 75, int fixedHeight = 75);

 protected:
  void paintEvent(QPaintEvent* event) override;
};

#endif  // GAMEPADELLIPSEBUTTON_H
