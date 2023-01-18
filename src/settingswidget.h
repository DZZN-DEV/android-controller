#ifndef SETTINGSIWDGET_H
#define SETTINGSIWDGET_H

#include <QGridLayout>
#include <QSettings>
#include <QWidget>

class SettingsWidget : public QWidget {
  Q_OBJECT

 protected:
  QGridLayout* m_settingsLayout;
  QSettings m_settings;

 public:
  SettingsWidget(QWidget* parent = nullptr);
  void addInput(QString const& label, QString const& defaultValue,
                std::function<void(QString const&)> const& onApply);
  void addToggle(QString const& label, Qt::CheckState defaultValue,
                 std::function<void(Qt::CheckState)> const& onApply);
 signals:
  void applySettings();
};

#endif  // SETTINGSIWDGET_H
