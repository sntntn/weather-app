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
    , widgetOrder(settings.savedLocations)
    , trashCan("../Resources/redTrash.png")
    , trashIcon(trashCan)
{
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    locationSwitch->setChecked(settings.shareLocation);
    mainLayout->addWidget(locationSwitch);

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

    listWidget->setDragDropMode(QAbstractItemView::InternalMove);

    for (const auto& location : settings.savedLocations) {

        auto *listItem = new QListWidgetItem();
        listItem->setData(Qt::UserRole, QVariant::fromValue(location));
        listWidget->addItem(listItem);

        auto *customWidget = new QWidget();
        auto *layout = new QHBoxLayout(customWidget);

        auto *label = new QLabel(location.getRenamedPlace());
        auto *deleteButton = new QPushButton();
        deleteButton->setIcon(trashIcon);

        layout->addWidget(label, 1);
        layout->addWidget(deleteButton);

        connect(deleteButton, &QPushButton::clicked, this, [this, listItem]() {
            widgetOrder.removeOne(listItem->data(Qt::UserRole).value<GeoLocationData>());
            delete listItem;
        });

        listWidget->setItemWidget(listItem, customWidget);
        listItem->setSizeHint(customWidget->minimumSizeHint());
    }

    // todo bug fix
    connect(listWidget, &WidgetsManager::itemsRearranged, this, [this](){
        widgetOrder.clear();

        for (int i = 0; i < listWidget->count(); i++) {
            auto location = listWidget->item(i)->data(Qt::UserRole).value<GeoLocationData>();
            widgetOrder.append(location);
        }
    });

    mainLayout->addWidget(listWidget);

    connect(save, &QPushButton::clicked, this, &SettingsDialog::changeSettings);
    //TODO fix grandparent
    connect(this, &SettingsDialog::settingsChanged, qobject_cast<MainWindow*>(this->parent()->parent()->parent()), &MainWindow::refreshPages);
    connect(cancel, &QPushButton::clicked, this, &SettingsDialog::resetOrder);
    connect(cancel, &QPushButton::clicked, this, &SettingsDialog::close);

    buttonLayout->addWidget(save);
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancel);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void SettingsDialog::changeSettings(){
    Settings::TemperatureUnit selectedTempUnit = static_cast<Settings::TemperatureUnit>(temperatureUnit->itemData(temperatureUnit->currentIndex()).toInt());
    Settings::WindSpeedUnit selectedWindUnit= static_cast<Settings::WindSpeedUnit>(windSpeedUnit->itemData(windSpeedUnit->currentIndex()).toInt());
    Settings::PrecipitationUnit selectedPrecUnit = static_cast<Settings::PrecipitationUnit>(precipitationUnit->itemData(precipitationUnit->currentIndex()).toInt());

    //TODO maybe impelement setters
    settings.temperatureUnit = selectedTempUnit;
    settings.windSpeedUnit = selectedWindUnit;
    settings.precipitationUnit = selectedPrecUnit;
    settings.shareLocation = locationSwitch->isChecked();
    settings.savedLocations = widgetOrder;

    emit settingsChanged();
    this->close();
}

void SettingsDialog::resetOrder(){
    widgetOrder = settings.savedLocations;
}
