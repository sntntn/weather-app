#include "SettingsDialog.h"
#include "Settings.h"
#include "MainWindow.h"
#include "HomePage.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , settings(Settings::instance())
    , mainLayout(new QVBoxLayout(this))
    , locationSwitch(new QCheckBox("Share Location", this))
    , temperatureUnit(new QComboBox(this))
    , windSpeedUnit(new QComboBox(this))
    , precipitationUnit(new QComboBox(this))
    , buttonLayout(new QHBoxLayout())
    , save(new QPushButton())
    , cancel(new QPushButton())
{
    //it.key() je odgovarajuca vrednost enuma koja odgovara ovom sto se ispise u datom comboboxu
    for (auto it = Settings::temperatureUnitsNames.cbegin(); it != Settings::temperatureUnitsNames.cend(); ++it) {
        temperatureUnit->addItem(it.value(), QVariant::fromValue(it.key()));
    }
    temperatureUnit->setCurrentText(settings.temperatureUnitName());

    for (auto it = Settings::windSpeedUnitsNames.cbegin(); it != Settings::windSpeedUnitsNames.cend(); ++it) {
        windSpeedUnit->addItem(it.value(), QVariant::fromValue(it.key()));
    }
    windSpeedUnit->setCurrentText(settings.windSpeedUnitName());

    for (auto it = Settings::precipitationUnitsNames.cbegin(); it != Settings::precipitationUnitsNames.cend(); ++it) {
        precipitationUnit->addItem(it.value(), QVariant::fromValue(it.key()));
    }
    precipitationUnit->setCurrentText(settings.precipitationUnitName());

    locationSwitch->setChecked(settings.shareLocation);

    save->setText("Save");
    cancel->setText("Cancel");
    connect(save, &QPushButton::clicked, this, &SettingsDialog::changeSettings);
    //TODO fix grandparent
    connect(this, &SettingsDialog::settingsChanged, qobject_cast<MainWindow*>(this->parent()->parent()->parent()), &MainWindow::getSavedLocationsData);
    buttonLayout->addWidget(save);
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancel);

    mainLayout->addWidget(locationSwitch);
    mainLayout->addWidget(temperatureUnit);
    mainLayout->addWidget(windSpeedUnit);
    mainLayout->addWidget(precipitationUnit);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

//MainWindow* SettingsDialog::getMainWindow() {
//    QObject* parentObj = this->parent();

//    if (HomePage* homePage = qobject_cast<HomePage*>(parentObj)) {
//        QObject* grandparentObj = homePage->parent();
//        return qobject_cast<MainWindow*>(grandparentObj);
//    }
//    //return qobject_cast<MainWindow*>(this->parent()->parent());
//    return nullptr;
//}

void SettingsDialog::changeSettings(){
    TemperatureUnit selectedTempUnit = static_cast<TemperatureUnit>(temperatureUnit->itemData(temperatureUnit->currentIndex()).toInt());
    WindSpeedUnit selectedWindUnit= static_cast<WindSpeedUnit>(windSpeedUnit->itemData(windSpeedUnit->currentIndex()).toInt());
    PrecipitationUnit selectedPrecUnit = static_cast<PrecipitationUnit>(precipitationUnit->itemData(precipitationUnit->currentIndex()).toInt());

    //TODO maybe impelement setters
    settings.temperatureUnit = selectedTempUnit;
    settings.windSpeedUnit = selectedWindUnit;
    settings.precipitationUnit = selectedPrecUnit;
    settings.shareLocation = locationSwitch->isChecked();

    // test
    // qDebug() << temperatureUnitToString(settings.temperatureUnit)
    //         << windSpeedUnitToString(settings.windSpeedUnit)
    //         << precipitationUnitToString(settings.precipitationUnit)
    //         << settings.shareLocation;


    emit settingsChanged();
    this->close();
}

//test
//QString SettingsDialog::temperatureUnitToString(TemperatureUnit unit) {
//    switch (unit) {
//    case TemperatureUnit::CELSIUS: return "Celsius";
//    case TemperatureUnit::FAHRENHEIT: return "Fahrenheit";
//    default: return "Unknown";

//    }
//}

//QString SettingsDialog::windSpeedUnitToString(WindSpeedUnit unit) {
//    switch (unit) {
//    case WindSpeedUnit::KMH: return "Kilometres per hour";
//    case WindSpeedUnit::MPH: return "Miles per hour";
//    case WindSpeedUnit::MS: return "Metres per second";
//    case WindSpeedUnit::KNOTS: return "Knots";
//    default: return "Unknown";
//    }
//}

//QString SettingsDialog::precipitationUnitToString(PrecipitationUnit unit) {
//    switch (unit) {
//    case PrecipitationUnit::MILLIMETRES: return "Millimetres";
//    case PrecipitationUnit::INCHES: return "Inches";
//    default: return "Unknown";
//    }
//}




