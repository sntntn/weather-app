#ifndef USERLOCATIONWIDGET_H
#define USERLOCATIONWIDGET_H

#include "WeatherWidget.h"

class UserLocationWidget : public WeatherWidget
{
public:
    UserLocationWidget(const QSharedPointer<WeatherData> &data, QWidget *parent);

private:
    bool active;
};

#endif // USERLOCATIONWIDGET_H
