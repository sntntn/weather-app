#ifndef DETAILEDPAGEWIDGETS_H
#define DETAILEDPAGEWIDGETS_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QTimeZone>
#include <QGridLayout>
#include <QScrollArea>

class BasicInfoWidget : public QWidget
{
    QHBoxLayout *basicInfoLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QPixmap *weatherIcon;
    QLabel *iconLabel;
    QLabel *weatherDescriptionLabel;
    QLabel *dateLabel;
    QLabel *timeLabel;
    QLabel *temperatureLabel;
    QLabel *feelsLikeLabel;

public:
    BasicInfoWidget(QWidget *parent = nullptr);
    void updateData(const int weatherCode, const bool isDay, const QTimeZone timezone, const int temperature,
                    const int apparentTemperature);
    QString getDaySuffix(const int day);
    QString weatherCodeToDescription(const int weatherCode);
};

class HourlyWeatherWidget : public QWidget
{
    QScrollArea *hourlyWeatherArea;
    QWidget *hourlyWeatherContents;
    QHBoxLayout *mainLayout;

    class HourlyWidgetItem : public QWidget{
        QVBoxLayout *hourLayout;
        QLabel *hourLabel;
        QPixmap *hourWeatherIcon;
        QLabel *hourWeatherIconLabel;
        QLabel *hourTempLabel;

        HourlyWidgetItem(QWidget *parent = nullptr);
        void updateData(const int tempText, const int weatherCode, const bool isDay, const QString timeStamp);
    };

public:
    HourlyWeatherWidget(QWidget *parent = nullptr);
    void updateData(const QVector<int> tempText, const QVector<int> weatherCode,
                    const QVector<bool> isDay, const QVector<QString> timeStamp);
};

class DailyWeatherWidget : public QWidget
{
    QHBoxLayout *dailyLayout;
    QLabel *dayNameLabel;
    QPixmap *dayWeatherIcon;
    QLabel *dayWeatherIconLabel;
    QLabel *dailyminTempLabel;
    QPixmap *temperatureIcon;
    QLabel *temperatureIconLabel;
    QLabel *dailymaxTempLabel;

public:
    DailyWeatherWidget(QWidget *parent = nullptr);
    void updateData(const QString dayName, const int weatherCode, const int minTemp, const int maxTemp);
};

#endif // DETAILEDPAGEWIDGETS_H
