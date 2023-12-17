#include "UserLocationWidget.h"

#include "Settings.h"

UserLocationWidget::UserLocationWidget(WeatherWidget *weatherWidget, QWidget *parent)
    : QWidget{parent}
    , weatherWidget(weatherWidget)
    , stackedWidget(new QStackedWidget(this))
    , errWidget(new QWidget())
    , errWidgetLayout(new QVBoxLayout())
    , errLabel(new QLabel())
    , settingsButton(new QPushButton("Settings"))
{
    errWidget->setLayout(errWidgetLayout);
    errWidgetLayout->addWidget(errLabel);
    errWidgetLayout->addWidget(settingsButton);

    stackedWidget->addWidget(weatherWidget);
    stackedWidget->addWidget(errWidget);

    Settings::instance().shareLocation() ? showWeather()
                                         : showLocationDisabledMessage();
}

void UserLocationWidget::showWeather()
{
    stackedWidget->setCurrentWidget(weatherWidget);
}

void UserLocationWidget::showErrorMessage()
{
    stackedWidget->setCurrentWidget(errWidget);
    settingsButton->setVisible(false);
    errLabel->setText("Unable to load user location data.");
}

void UserLocationWidget::showLocationDisabledMessage()
{
    stackedWidget->setCurrentWidget(errWidget);
    settingsButton->setVisible(true);
    errLabel->setText("Enable location sharing in settings.");
}
