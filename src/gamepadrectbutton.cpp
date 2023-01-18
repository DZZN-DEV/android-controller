#include "gamepadrectbutton.h"

GamepadRectButton::GamepadRectButton(QWidget* parent, QString buttonText,
                                     std::function<void(bool)> sendButtonState,
                                     int fixedWidth, int fixedHeight)
    : GamepadNamedButton(parent, buttonText, sendButtonState, fixedWidth,
                         fixedHeight) {}

void GamepadRectButton::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)

  QPainter painter(this);
  int buttonWidth = width() - 1;
  int buttonHeight = height() - 1;
  QRect rect{0, 0, buttonWidth, buttonHeight};
  if (m_isPressed) {
    painter.setBrush(Qt::red);
  } else {
    painter.setBrush(painter.background().color().darker());
  }
  painter.drawRect(rect);
  painter.drawText(rect, Qt::AlignCenter, m_buttonText);
}
