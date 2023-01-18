#ifndef GAMEPADBUTTON_H
#define GAMEPADBUTTON_H

#include <QEvent>
#include <QPainter>
#include <QWidget>
#include <functional>

class GamepadButton : public QWidget {
 protected:
  std::function<void(bool)> m_sendButtonState;
  bool m_isPressed = false;

 public:
  GamepadButton(QWidget* parent = nullptr,
                std::function<void(bool)> const& sendButtonState = {},
                int fixedWidth = 75, int fixedHeight = 50);

 protected:
  bool event(QEvent* event) override;
};

#endif  // GAMEPADBUTTON_H
