#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>

#include "Settings.h"


class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    QString temperatureUnitToString(TemperatureUnit unit);
    QString windSpeedUnitToString(WindSpeedUnit unit);
    QString precipitationUnitToString(PrecipitationUnit unit);
    SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog() = default;
    void changeSettings();

//TODO : make a function in mainWindow that reacts to this signal
signals:
    void settingsChanged();

private:
    Settings &settings;
    QVBoxLayout *mainLayout;
    QCheckBox *locationSwitch;
    QComboBox *temperatureUnit;
    QComboBox *windSpeedUnit;
    QComboBox *precipitationUnit;
    QHBoxLayout *buttonLayout;
    QPushButton *save;
    QPushButton *cancel;


    void setupUi();


};

#endif // SETTINGSDIALOG_H
