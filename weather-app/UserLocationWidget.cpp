#include "UserLocationWidget.h"

UserLocationWidget::UserLocationWidget(const QSharedPointer<WeatherData> &data, QWidget *parent)
    : WeatherWidget(data, parent)
    , active(true)
{

}
