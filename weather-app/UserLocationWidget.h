#ifndef USERLOCATIONWIDGET_H
#define USERLOCATIONWIDGET_H

#include <QStackedWidget>
#include <QPushButton>

#include "WeatherWidget.h"

class UserLocationWidget : public QWidget
{
public:
    UserLocationWidget(WeatherWidget *weatherWidget, QWidget *parent);
    void showWeather();
    void showErrorMessage();
    void showLocationDisabledMessage();

private:
    WeatherWidget *weatherWidget;
    QStackedWidget *stackedWidget;
    QWidget *errWidget;
    QVBoxLayout *errWidgetLayout;
    QLabel *errLabel;
    QPushButton *settingsButton;
};

#endif // USERLOCATIONWIDGET_H
