#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QPushButton>
#include <QUdpSocket>
#include <QVBoxLayout>
#include <QWidget>

#include "gamepad.h"
#include "settingswidget.h"

class MainWidget : public QWidget {
 public:
  MainWidget(QWidget* parent = nullptr);

 private:
  QUdpSocket m_udpSocket;
  Gamepad* m_gamepad;
  SettingsWidget* m_settingsWidget;
  QHostAddress m_address;
  quint16 m_port;
  QPushButton* m_openSettings;
  QPushButton* m_goBack;
};

#endif  // MAINWIDGET_H
