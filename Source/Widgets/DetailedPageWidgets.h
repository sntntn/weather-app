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
    QVBoxLayout *dateTimeLayout;
    QPixmap weatherIcon;
    QLabel *iconLabel;
    QLabel *weatherDescriptionLabel;
    QLabel *todayLabel;
    QLabel *dateLabel;
    QLabel *timeLabel;
    QLabel *temperatureLabel;
    QLabel *feelsLikeLabel;

    static const int iconWidth = 80;
    static const int iconHeight = 80;

public:
    BasicInfoWidget(QWidget *parent = nullptr);
    void updateData(const int weatherCode, const bool isDay, const QTimeZone &timezone, const int temperature,
                    const int apparentTemperature);
    QString getDaySuffix(const int day);
    QString weatherCodeToDescription(const int weatherCode);
};

class singleWidgetItem : public QWidget{
    QVBoxLayout *mainLayout;
    QHBoxLayout *lowerLayout;
    QPixmap *infoIcon;
    QLabel *infoIconLabel;
    QLabel *infoLabel;
    QLabel *info;

    static const int iconWidth = 35;
    static const int iconHeight = 35;
public:
    singleWidgetItem(const QString iconPath, const QString infoName, QWidget *parent = nullptr);
    void updateData(const int value, const QString unit);
    QFrame* createLineFrame();
};

class HumidityUvRainWidget : public QWidget
{
    QHBoxLayout *mainLayout;
    singleWidgetItem *humidity;
    singleWidgetItem *uvIndex;
    singleWidgetItem *rain;

public:
    HumidityUvRainWidget(QWidget *parent = nullptr);
    void updateData(const int humidity, const int uvIndex, const int rain);
    QString uvIndextoDescription(const int uvIndex);
};

class VisibilityPressureSnowWidget : public QWidget
{
    QHBoxLayout *mainLayout;
    singleWidgetItem *visibility;
    singleWidgetItem *pressure;
    singleWidgetItem *snow;

public:
    VisibilityPressureSnowWidget(QWidget *parent = nullptr);
    void updateData(const int visibilityValue, const int pressureValue, const int snowValue);
};

class WindInfoWidget : public QWidget
{
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QLabel *windGustsLabel;
    QLabel *windGusts;
    QLabel *windSpeedLabel;
    QLabel *windSpeed;
    QLabel *compassLabel;
    QPixmap initialCompassIcon;
    QPixmap arrowIcon;

    static const int iconWidth = 60;
    static const int iconHeight = 60;

public:
    WindInfoWidget(QWidget *parent = nullptr);
    void updateData(const int windSpeed, const int windGusts, const int windDirection);
};

class SunriseSunsetWidget : public QWidget
{
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QLabel *sunriseLabel;
    QLabel *sunsetLabel;
    QLabel *sunriseIconLabel;
    QLabel *sunsetIconLabel;
    QPixmap sunriseIcon;
    QPixmap sunsetIcon;
    QLabel *sunriseTime;
    QLabel *sunsetTime;

public:
    SunriseSunsetWidget(QWidget *parent = nullptr);
    void updateData(const QString sunrise, const QString sunset);
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
    static const int iconWidth = 35;
    static const int iconHeight = 35;
    static const int dayNameLabelWidth = 100;
    static const int padding = 20;

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
