#include "dpadbutton.h"

#include <QPainter>
#include <QtMath>

DPadButton::DPadButton(QWidget* parrent,
                       std::function<void(bool)> const& sendButtonState,
                       Direction dir, int fixedSize)
    : GamepadButton(parrent, sendButtonState, fixedSize, fixedSize),
      m_direction(dir) {}

void DPadButton::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event)
  auto rotatePoint = [](QPoint const& toRotate, QPoint const& referencePoint,
                        qreal rad) {
    int x = toRotate.x() - referencePoint.x();
    int y = toRotate.y() - referencePoint.y();

    return QPoint(x * qCos(rad) - y * qSin(rad) + referencePoint.x(),
                  x * qSin(rad) + y * qCos(rad) + referencePoint.y());
  };
  qreal deltaRad = 0.0;
  switch (m_direction) {
    case Direction::Up:
      break;
    case Direction::Down:
      deltaRad += M_PI;
      break;
    case Direction::Left:
      deltaRad -= M_PI / 2;
      break;
    case Direction::Right:
      deltaRad += M_PI / 2;
      break;
  }
  QPoint circleCentre{width() / 2, width() / 2};
  QPoint trianglePoint{width() / 2, 0};
  QPolygon triangle(
      {rotatePoint(trianglePoint, circleCentre, deltaRad),
       rotatePoint(trianglePoint, circleCentre, -2.0 * M_PI / 3.0 + deltaRad),
       rotatePoint(trianglePoint, circleCentre, 2.0 * M_PI / 3.0 + deltaRad)});

  QPainter painter(this);
  if (m_isPressed) {
    painter.setBrush(Qt::red);
  } else {
    painter.setBrush(painter.background().color().darker());
  }
  painter.drawPolygon(triangle);
}
