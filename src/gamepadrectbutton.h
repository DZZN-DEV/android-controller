#ifndef GAMEPADRECTBUTTON_H
#define GAMEPADRECTBUTTON_H

#include "gamepadnamedbutton.h"

class GamepadRectButton : public GamepadNamedButton {
 public:
  GamepadRectButton(QWidget* parent = nullptr, QString buttonText = {},
                    std::function<void(bool)> sendButtonState = {},
                    int fixedWidth = 75, int fixedHeight = 50);

 protected:
  virtual void paintEvent(QPaintEvent* event) override;
};

#endif  // GAMEPADRECTBUTTON_H