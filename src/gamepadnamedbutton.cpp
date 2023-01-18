#include "gamepadnamedbutton.h"

GamepadNamedButton::GamepadNamedButton(
    QWidget* parent, QString buttonText,
    std::function<void(bool)> const& sendButtonState, int fixedWidth,
    int fixedHeight)
    : GamepadButton(parent, sendButtonState, fixedWidth, fixedHeight),
      m_buttonText(buttonText) {}
