#include "mainwidget.h"

#include <QHostInfo>

MainWidget::MainWidget(QWidget* parent) : QWidget(parent), m_udpSocket(this) {
  QVBoxLayout* layout = new QVBoxLayout(this);

  m_gamepad = new Gamepad(this, [this](QByteArray const& byteArray) {
    m_udpSocket.writeDatagram(byteArray, m_address, m_port);
  });
  layout->addWidget(m_gamepad);

  m_settingsWidget = new SettingsWidget(this);
  m_settingsWidget->hide();
  m_settingsWidget->addInput(
      "Address", "127.0.0.1",
      [this](QString const& address) { m_address = QHostAddress(address); });

  const quint16 defaultPort = 15366;
  m_settingsWidget->addInput("Port", QString::number(defaultPort),
                             [this](QString const& port) {
                               m_port = port.toUInt();
                               if (!m_port) {
                                 m_port = defaultPort;
                               }
                             });
  m_settingsWidget->addToggle("Send gyro", {},
                              [this](Qt::CheckState checkState) {
                                if (checkState == Qt::CheckState::Checked) {
                                  m_gamepad->enableGyro();
                                } else {
                                  m_gamepad->disableGyro();
                                }
                              });

  layout->addWidget(m_settingsWidget);

  m_openSettings = new QPushButton("Settings", this);
  layout->addWidget(m_openSettings, 0, Qt::AlignBottom | Qt::AlignLeft);
  QObject::connect(m_openSettings, &QPushButton::clicked, [this]() {
    m_settingsWidget->setDisabled(false);
    m_openSettings->hide();
    m_gamepad->hide();
    m_settingsWidget->show();
    m_goBack->show();
  });

  m_goBack = new QPushButton("Back", this);
  QObject::connect(m_goBack, &QPushButton::clicked, [this]() {
    m_settingsWidget->setDisabled(true);
    m_goBack->hide();
    m_settingsWidget->hide();
    m_gamepad->show();
    m_openSettings->show();
    emit m_settingsWidget->applySettings();
  });
  m_goBack->hide();
  layout->addWidget(m_goBack, 0, Qt::AlignBottom | Qt::AlignLeft);

  m_settingsWidget->applySettings();
}
