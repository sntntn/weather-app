#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>

#include "Settings.h"

class GeoLocationData;
class MainWindow;
class WidgetsManager;

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    MainWindow* getMainWindow();
    SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog() = default;
    void changeSettings();

signals:
    void settingsChanged();

public slots:
    void resetOrder();

private:
    Settings &settings;
    QVBoxLayout *mainLayout;
    QCheckBox *locationSwitch;
    QComboBox *temperatureUnit;
    QComboBox *windSpeedUnit;
    QComboBox *precipitationUnit;
    WidgetsManager *listWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *save;
    QPushButton *cancel;
    QList<GeoLocationData> widgetOrder;
    QPixmap trashCan;
    QIcon trashIcon;

    void setupUi();

    const QString trashIconPath = "../Resources/trashCan/redTrash.png";
};

#endif // SETTINGSDIALOG_H
