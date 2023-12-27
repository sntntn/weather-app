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
    QPixmap weatherIcon;
    QLabel *iconLabel;
    QLabel *weatherDescriptionLabel;
    QLabel *dateLabel;
    QLabel *timeLabel;
    QLabel *temperatureLabel;
    QLabel *feelsLikeLabel;

    static const int iconWidth = 100;
    static const int iconHeight = 100;

public:
    BasicInfoWidget(QWidget *parent = nullptr);
    void updateData(const int weatherCode, const bool isDay, const QTimeZone &timezone, const int temperature,
                    const int apparentTemperature);
    QString getDaySuffix(const int day);
    QString weatherCodeToDescription(const int weatherCode);
};

class HourlyWeatherWidget : public QWidget
{
    QVBoxLayout *mainLayout;
    QScrollArea *hourlyWeatherArea;
    QWidget *hourlyWeatherContents;
    QHBoxLayout *itemsLayout;

    static const int hoursPerDay = 24;
    static const int iconWidth = 25;
    static const int iconHeight = 25;
    static const int widgetItemWidth = 70;
    static const int widgetItemHeight = 100;

    class HourlyWidgetItem : public QWidget{
        QVBoxLayout *hourLayout;
        QLabel *hourLabel;
        QPixmap hourWeatherIcon;
        QLabel *hourWeatherIconLabel;
        QLabel *hourTempLabel;

    public:
        HourlyWidgetItem(QWidget *parent = nullptr);
        void updateData(const int tempText, const int weatherCode, const bool isDay, const QString &timeStamp);
    };

public:
    HourlyWeatherWidget(QWidget *parent = nullptr);
    void updateData(const QVector<int> &temperatures, const QVector<int> &weatherCodes,
                    const QVector<bool> &isDays, const QVector<QString> &timeStamps);
};

class DailyWeatherWidget : public QWidget
{
    QGridLayout *mainLayout;

    static const int daysPerWeek = 7;
    static const int iconWidth = 30;
    static const int iconHeight = 30;
    static const int dayNameLabelWidth = 80;

    class DailyWidgetItem : public QWidget
    {
        QHBoxLayout *dailyLayout;
        QLabel *dayNameLabel;
        QPixmap dayWeatherIcon;
        QLabel *dayWeatherIconLabel;
        QLabel *dailyminTempLabel;
        QPixmap temperatureIcon;
        QLabel *temperatureIconLabel;
        QLabel *dailymaxTempLabel;

    public:
        DailyWidgetItem(QWidget *parent = nullptr);
        void updateData(const QString &dayName, const int weatherCode,
                        const int minTemp, const int maxTemp);
    };

public:
    DailyWeatherWidget(QWidget *parent = nullptr);
    void updateData(const QVector<QString> &dayNames, const QVector<int> &weatherCodes,
                    const QVector<int> &minTemps, const QVector<int> &maxTemps);

};





#endif // DETAILEDPAGEWIDGETS_H
