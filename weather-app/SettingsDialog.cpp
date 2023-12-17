#include "SettingsDialog.h"

#include <QListView>
#include <QListWidget>

#include "MainWindow.h"
#include "HomePage.h"
#include "WidgetsManager.h"
#include "GeoLocationData.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , settings(Settings::instance())
    , mainLayout(new QVBoxLayout(this))
    , locationSwitch(new QCheckBox("Share Location", this))
    , temperatureUnit(new QComboBox(this))
    , windSpeedUnit(new QComboBox(this))
    , precipitationUnit(new QComboBox(this))
    , listWidget(new WidgetsManager(this))
    , buttonLayout(new QHBoxLayout())
    , save(new QPushButton("Save"))
    , cancel(new QPushButton("Cancel"))
    , widgetOrder(settings.savedLocations())
    , trashCan("../Resources/trashCan/redTrash.png") // todo
    , trashIcon(trashCan)
{
    locationSwitch->setChecked(settings.m_shareLocation);
    mainLayout->addWidget(locationSwitch);

    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setDragDropMode(QAbstractItemView::InternalMove);

    for (const auto& name : Settings::temperatureUnitsNames) {
        auto unit = Settings::temperatureUnitsNames.key(name);
        temperatureUnit->addItem(name, QVariant::fromValue(unit));
    }
    temperatureUnit->setCurrentText(settings.temperatureUnitName());

    for (const auto& name : Settings::windSpeedUnitsNames) {
        auto unit = Settings::windSpeedUnitsNames.key(name);
        windSpeedUnit->addItem(name, QVariant::fromValue(unit));
    }
    windSpeedUnit->setCurrentText(settings.windSpeedUnitName());

    for (const auto& name : Settings::precipitationUnitsNames) {
        auto unit = Settings::precipitationUnitsNames.key(name);
        precipitationUnit->addItem(name, QVariant::fromValue(unit));
    }
    precipitationUnit->setCurrentText(settings.precipitationUnitName());

    mainLayout->addWidget(temperatureUnit);
    mainLayout->addWidget(windSpeedUnit);
    mainLayout->addWidget(precipitationUnit);

    for (const auto& location : settings.savedLocations()) {

        auto *listItem = new QListWidgetItem();
        listItem->setData(Qt::UserRole, location.toVariant());
        listWidget->addItem(listItem);

        auto *customWidget = new QWidget();
        auto *layout = new QHBoxLayout(customWidget);
        auto *label = new QLabel(location.getRenamedPlace());
        auto *deleteButton = new QPushButton();
        deleteButton->setIcon(trashIcon);

        layout->addWidget(label, 1);
        layout->addWidget(deleteButton);

        connect(deleteButton, &QPushButton::clicked, this, [this, listItem]() {
            auto locationMap = listItem->data(Qt::UserRole).toMap();
            const auto geoLocation = GeoLocationData::fromVariantMap(locationMap);
            widgetOrder.removeOne(geoLocation);

            delete listItem;
        });

        listWidget->setItemWidget(listItem, customWidget);
        listItem->setSizeHint(customWidget->minimumSizeHint());
    }

    connect(listWidget, &WidgetsManager::itemsRearranged, this, [this](){
        widgetOrder.clear();

        for (int i = 0; i < listWidget->count(); i++) {
            auto locationMap = listWidget->item(i)->data(Qt::UserRole).toMap();
            const auto geoLocation = GeoLocationData::fromVariantMap(locationMap);
            widgetOrder.append(geoLocation);
        }
    });

    mainLayout->addWidget(listWidget);

    buttonLayout->addWidget(save);
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancel);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(save, &QPushButton::clicked, this, &SettingsDialog::changeSettings);
    //TODO fix grandparent
    connect(this, &SettingsDialog::settingsChanged, qobject_cast<MainWindow*>(this->parent()->parent()->parent()), &MainWindow::refreshPages);
    connect(cancel, &QPushButton::clicked, this, &SettingsDialog::resetOrder);
    connect(cancel, &QPushButton::clicked, this, &SettingsDialog::close);
}

void SettingsDialog::changeSettings(){
    Settings::TemperatureUnit selectedTempUnit = static_cast<Settings::TemperatureUnit>(temperatureUnit->itemData(temperatureUnit->currentIndex()).toInt());
    Settings::WindSpeedUnit selectedWindUnit= static_cast<Settings::WindSpeedUnit>(windSpeedUnit->itemData(windSpeedUnit->currentIndex()).toInt());
    Settings::PrecipitationUnit selectedPrecUnit = static_cast<Settings::PrecipitationUnit>(precipitationUnit->itemData(precipitationUnit->currentIndex()).toInt());

    //TODO maybe impelement setters
    settings.m_temperatureUnit = selectedTempUnit;
    settings.m_windSpeedUnit = selectedWindUnit;
    settings.m_precipitationUnit = selectedPrecUnit;
    settings.m_shareLocation = locationSwitch->isChecked();
    settings.m_savedLocations = widgetOrder;

    emit settingsChanged();
    this->close();
}

void SettingsDialog::resetOrder(){
    widgetOrder = settings.savedLocations();
}
