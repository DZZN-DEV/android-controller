#include "joystick.h"

#include <QEvent>
#include <QPainter>
#include <QTouchEvent>

Joystick::Joystick(QWidget* parrent,
                   std::function<void(qreal, qreal)> const& sendAxisState,
                   int fixedSize)
    : QWidget(parrent), m_sendAxisState(sendAxisState) {
  setFixedSize(fixedSize, fixedSize);
  setAttribute(Qt::WA_AcceptTouchEvents);
}
bool Joystick::event(QEvent* event) {
  auto setCoordsFromEvent = [this](QTouchEvent* touchEvent) {
    if (touchEvent->pointCount()) {
      auto evPoint = touchEvent->point(0);
      QPointF pos = evPoint.position();
      qreal centreX, centreY;
      centreX = centreY = width() / 2.;
      m_x = (pos.x() - centreX) / centreX;
      m_y = (pos.y() - centreY) / centreY;
      if (qreal norm = qSqrt(m_x * m_x + m_y * m_y); norm > 1.0) {
        m_x /= norm;
        m_y /= norm;
      }
      if (m_sendAxisState) {
        m_sendAxisState(m_x, m_y);
      }
    }
  };
  switch (event->type()) {
    case QEvent::TouchBegin:
      m_isMoving = true;
    case QEvent::TouchUpdate:
      setCoordsFromEvent(static_cast<QTouchEvent*>(event));
      event->accept();
      repaint();
      return true;
    case QEvent::TouchEnd:
      m_x = m_y = 0;
      if (m_sendAxisState) {
        m_sendAxisState(m_x, m_y);
      }
      m_isMoving = false;
      repaint();
      event->accept();
      return true;
    default:
      return QWidget::event(event);
  }
}

void Joystick::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)

  QPainter painter(this);
  int joystickSize = width() - 1;
  QPointF centre{(1.0 + m_x) * width() / 2.0, (1.0 + m_y) * width() / 2.0};
  QRect rect{0, 0, joystickSize, joystickSize};
  painter.drawRect(rect);
  if (m_isMoving) {
    painter.setBrush(Qt::red);
  } else {
    painter.setBrush(painter.background().color().darker());
  }
  painter.drawEllipse(centre, width() / 4.0, width() / 4.0);
}
