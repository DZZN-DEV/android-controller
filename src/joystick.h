#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QWidget>

class Joystick : public QWidget {
 protected:
  std::function<void(qreal, qreal)> m_sendAxisState;
  qreal m_x = 0;
  qreal m_y = 0;
  bool m_isMoving = false;

 public:
  Joystick(QWidget* parrent = nullptr,
           std::function<void(qreal, qreal)> const& sendAxisState = {},
           int fixedSize = 150);

 protected:
  bool event(QEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
};

#endif
