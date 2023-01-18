#include "gamepadbutton.h"

GamepadButton::GamepadButton(QWidget* parent,
                             std::function<void(bool)> const& sendButtonState,
                             int fixedWidth, int fixedHeight)
    : QWidget(parent), m_sendButtonState(sendButtonState) {
  setFixedSize(fixedWidth, fixedHeight);
  setAttribute(Qt::WA_AcceptTouchEvents);
}

bool GamepadButton::event(QEvent* event) {
  switch (event->type()) {
    case QEvent::TouchBegin:
      if (m_sendButtonState) {
        m_sendButtonState(true);
      }
      event->accept();
      m_isPressed = true;
      repaint();
      return true;
    case QEvent::TouchEnd:
      if (m_sendButtonState) {
        m_sendButtonState(false);
      }
      event->accept();
      m_isPressed = false;
      repaint();
      return true;
    default:
      return QWidget::event(event);
  }
}
