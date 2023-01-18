#include "settingswidget.h"

#include <qnamespace.h>

#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QScreen>

SettingsWidget::SettingsWidget(QWidget* parent)
    : QWidget(parent), m_settings(this) {
  m_settingsLayout = new QGridLayout(this);
  const QSize screenSize = qApp->screens().first()->size();
  const qreal marginRatio = 0.3;
  int const marginTopBottom = screenSize.height() * marginRatio;
  int const marginLeftRight = screenSize.width() * marginRatio;
  m_settingsLayout->setContentsMargins(marginLeftRight, marginTopBottom,
                                       marginLeftRight, marginTopBottom);
}

void SettingsWidget::addInput(
    QString const& label, QString const& defaultValue,
    std::function<void(QString const&)> const& onApply) {
  int const row = m_settingsLayout->rowCount();
  QLabel* inputLabel = new QLabel(label, this);
  m_settingsLayout->addWidget(inputLabel, row, 0);

  QLineEdit* lineEdit = new QLineEdit(
      m_settings.value(label, defaultValue).value<QString>(), this);
  QObject::connect(lineEdit, &QLineEdit::editingFinished,
                   [=]() { lineEdit->clearFocus(); });
  m_settingsLayout->addWidget(lineEdit, row, 1);

  QObject::connect(this, &SettingsWidget::applySettings, this, [=, this]() {
    QString lineEditText = lineEdit->text();
    m_settings.setValue(label, lineEditText);
    if (onApply) {
      onApply(lineEditText);
    }
  });
}

void SettingsWidget::addToggle(
    QString const& label, Qt::CheckState defaultValue,
    std::function<void(Qt::CheckState)> const& onApply) {
  QCheckBox* checkBox = new QCheckBox(label, this);
  checkBox->setCheckState(
      m_settings.value(label, defaultValue).value<Qt::CheckState>());
  m_settingsLayout->addWidget(checkBox);

  QObject::connect(this, &SettingsWidget::applySettings, this, [=, this]() {
    Qt::CheckState checkState = checkBox->checkState();
    m_settings.setValue(label, checkState);
    if (onApply) {
      onApply(checkState);
    }
  });
}
