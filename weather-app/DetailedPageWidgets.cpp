#include "DetailedPageWidgets.h"

HourlyWeatherWidget::HourlyWeatherWidget(QWidget *parent)
    : QWidget(parent)
    , hourlyWeatherArea(new QScrollArea())
    , hourlyWeatherContents(new QWidget())
    , mainLayout(new QHBoxLayout())
{
    //todo magic number 24
        for(int i = 0; i < 24; i++){
            HourlyWidgetItem *widget = new HourlyWidgetItem(this);
            widget->setFixedSize(70, 100);
            mainLayout->addWidget(widget);
        }
        hourlyWeatherContents->setLayout(mainLayout);
        hourlyWeatherArea->setWidget(hourlyWeatherContents);
        hourlyWeatherArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        hourlyWeatherArea->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
}

void HourlyWeatherWidget::updateData(const QVector<int> temperatures, const QVector<int> weatherCodes,
                                     const QVector<bool> isDays, const QVector<QString> timeStamps)
{
    for (int i = 0; i < 24; ++i) {
        QLayoutItem* item = mainLayout->itemAt(i);
        //todo dynamic u static
        HourlyWidgetItem* widget = dynamic_cast<HourlyWidgetItem*>(item->widget());
        widget->updateData(temperatures[i], weatherCodes[i],
                           isDays[i], timeStamps[i]);
    }
}

HourlyWeatherWidget::HourlyWidgetItem::HourlyWidgetItem(QWidget *parent)
    : QWidget(parent)
    , hourLayout(new QVBoxLayout(this))
    , hourLabel(new QLabel())
    , hourWeatherIcon(new QPixmap())
    , hourWeatherIconLabel(new QLabel(this))
    , hourTempLabel(new QLabel(this))
{
    hourLabel->setAlignment(Qt::AlignCenter);
    hourTempLabel->setAlignment(Qt::AlignCenter);
    hourWeatherIconLabel->setAlignment(Qt::AlignCenter);

    hourTempLabel->setStyleSheet("font: bold 18px;");

    hourLayout->addWidget(hourWeatherIconLabel);
    hourLayout->addWidget(hourTempLabel);
    hourLayout->addWidget(hourLabel);
}

HourlyWeatherWidget::HourlyWidgetItem::updateData(const int tempText, const int weatherCode,
                                                  const bool isDay, const QString timeStamp)
{
    hourLabel->setText(timeStamp);
    hourWeatherIcon->load(Settings::instance().weatherCodeToIcon(weatherCode, isDay));
    hourWeatherIconLabel->setPixmap(hourWeatherIcon->scaled(25, 25,
                                                            Qt::KeepAspectRatio, Qt::SmoothTransformation));
    hourTempLabel->setText(QString::number(tempText) + "°");
}
