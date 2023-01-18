#ifndef GAMEPADNAMEDBUTTON_H
#define GAMEPADNAMEDBUTTON_H

#include "gamepadbutton.h"

class GamepadNamedButton : public GamepadButton {
 protected:
  QString m_buttonText;

 public:
  GamepadNamedButton(QWidget* parent = nullptr, QString buttonText = {},
                     std::function<void(bool)> const& sendButtonState = {},
                     int fixedWidth = 75, int fixedHeight = 50);
};

#endif  // GAMEPADNAMEDBUTTON_H
