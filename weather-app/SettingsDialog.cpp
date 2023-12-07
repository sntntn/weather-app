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
    , buttonLayout(new QHBoxLayout())
    , save(new QPushButton("Save"))
    , cancel(new QPushButton("Cancel"))
    , widgetOrder(settings.savedLocations)
    , trashCan("../Resources/redTrash.png")
    , trashIcon(trashCan)
{
    locationSwitch->setChecked(settings.shareLocation);
    mainLayout->addWidget(locationSwitch);

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

    mainLayout->addWidget(temperatureUnit);
    mainLayout->addWidget(windSpeedUnit);
    mainLayout->addWidget(precipitationUnit);

    WidgetsManager* listWidget = new WidgetsManager(this);
    listWidget->setDragDropMode(QAbstractItemView::InternalMove);

    for (const auto& location : settings.savedLocations) {

        QListWidgetItem* listItem = new QListWidgetItem();
        listItem->setData(Qt::UserRole, QVariant::fromValue(location));
        listWidget->addItem(listItem);

        QWidget* customWidget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(customWidget);

        QLabel* label = new QLabel(location.getRenamedPlace());
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setIcon(trashIcon);

        layout->addWidget(label, 1);
        layout->addWidget(deleteButton);

        connect(deleteButton, &QPushButton::clicked, this, [this, listWidget, listItem]() {
            widgetOrder.removeOne(listItem->data(Qt::UserRole).value<GeoLocationData>());
            delete listItem;
        });

        listWidget->setItemWidget(listItem, customWidget);
        listItem->setSizeHint(customWidget->minimumSizeHint());
    }

    connect(listWidget, &WidgetsManager::itemsRearranged, this, [this, listWidget](){

        widgetOrder.clear();

        for (int i = 0; i < listWidget->count(); i++) {
            GeoLocationData location = listWidget->item(i)->data(Qt::UserRole).value<GeoLocationData>();
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
    TemperatureUnit selectedTempUnit = static_cast<TemperatureUnit>(temperatureUnit->itemData(temperatureUnit->currentIndex()).toInt());
    WindSpeedUnit selectedWindUnit= static_cast<WindSpeedUnit>(windSpeedUnit->itemData(windSpeedUnit->currentIndex()).toInt());
    PrecipitationUnit selectedPrecUnit = static_cast<PrecipitationUnit>(precipitationUnit->itemData(precipitationUnit->currentIndex()).toInt());

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
