#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "Settings.h"

class GeoLocationData;
class MainWindow;
class WidgetsManager;

class SettingsDialog : public QDialog
{
  Q_OBJECT

public:
  SettingsDialog(QWidget *parent = nullptr);
  ~SettingsDialog() override = default;

  signals:
  void settingsChanged();

private slots:
  void changeSettings();
  void resetOrder();

private:
  Settings				&settings;
  QVBoxLayout			*mainLayout;
  QCheckBox				*locationSwitch;
  QComboBox				*temperatureUnit;
  QComboBox				*windSpeedUnit;
  QComboBox				*precipitationUnit;
  WidgetsManager		*listWidget;
  QHBoxLayout			*buttonLayout;
  QPushButton			*save;
  QPushButton			*cancel;
  QList<GeoLocationData> widgetOrder;
  QPixmap				 trashCan;
  QPixmap				 orderCan;
  QIcon					 trashIcon;
  QIcon					 orderIcon;

  void setupUi();
  auto eventFilter(QObject *obj, QEvent *event) -> bool override;

  const QString trashIconPath = "../Resources/trashCan/redTrash.png";
};

#endif // SETTINGSDIALOG_H
