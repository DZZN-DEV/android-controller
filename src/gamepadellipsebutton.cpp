#include "gamepadellipsebutton.h"

GamepadEllipseButton::GamepadEllipseButton(
    QWidget* parent, QString buttonText,
    std::function<void(bool)> sendButtonState, int fixedWidth, int fixedHeight)
    : GamepadNamedButton(parent, buttonText, sendButtonState, fixedWidth,
                         fixedHeight) {}

void GamepadEllipseButton::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)

  QPainter painter(this);
  int buttonWidth = width() - 1;
  int buttonHeight = height() - 1;
  auto font = painter.font();
  font.setPixelSize(buttonHeight * 0.6);
  painter.setFont(font);
  QRect rect{0, 0, buttonWidth, buttonHeight};
  if (m_isPressed) {
    painter.setBrush(Qt::red);
  } else {
    painter.setBrush(painter.background().color().darker());
  }
  painter.drawEllipse(rect);
  painter.drawText(rect, Qt::AlignCenter, m_buttonText);
}
