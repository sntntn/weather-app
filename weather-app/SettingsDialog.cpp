#include "SettingsDialog.h"

#include <QListView>
#include <QListWidget>

#include "MainWindow.h"
#include "HomePage.h"
#include "WidgetsManager.h"

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
    , widgetOrder(settings.locationNames)
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

    for (const QString& location : settings.locationNames) {

        QListWidgetItem* listItem = new QListWidgetItem();
        listWidget->addItem(listItem);

        QWidget* customWidget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout(customWidget);

        QLabel* label = new QLabel(location);
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setIcon(trashIcon);
        //deleteButton->setStyleSheet("background-color: transparent;");

        layout->addWidget(label, 1);
        layout->addWidget(deleteButton);

        connect(deleteButton, &QPushButton::clicked, this, [this, listWidget, listItem]() {

            QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(listWidget->itemWidget(listItem)->layout());
            QLabel* label = qobject_cast<QLabel*>(layout->itemAt(0)->widget());
            QString itemText = label->text();

            delete listItem;
            widgetOrder.removeAll(itemText);
        });

        listWidget->setItemWidget(listItem, customWidget);
        listItem->setSizeHint(customWidget->minimumSizeHint());
    }

    connect(listWidget, &WidgetsManager::itemsRearranged, this, [this, listWidget](){
        widgetOrder.clear();

        for (int i = 0; i < listWidget->count(); ++i) {
            QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(listWidget->itemWidget(listWidget->item(i))->layout());
            QLabel* label = qobject_cast<QLabel*>(layout->itemAt(0)->widget());
            widgetOrder.append(label->text());
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
    settings.locationNames = widgetOrder;

    emit settingsChanged();
    this->close();
}

void SettingsDialog::changeOrder(const QList<QString> &newOrder){
    widgetOrder = newOrder;
}

void SettingsDialog::resetOrder(){
    widgetOrder = settings.locationNames;
}
