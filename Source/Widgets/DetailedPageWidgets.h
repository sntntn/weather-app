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
    static const int iconWidth = 80;
    static const int iconHeight = 80;
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

    QString getDaySuffix(const int day);
    QString weatherCodeToDescription(const int weatherCode);
public:
    BasicInfoWidget(QWidget *parent = nullptr);
    void updateData(const int weatherCode, const bool isDay, const QTimeZone &timezone, const int temperature,
                    const int apparentTemperature);
};

class MinMaxTempWidget : public QWidget
{
    QHBoxLayout *mainLayout;

    class MinMaxTempWidgetItem : public QWidget{

        static const int iconWidth = 10;
        static const int iconHeight = 15;
        QHBoxLayout *mainLayout;
        QPixmap *infoIcon;
        QLabel *infoIconLabel;
        QLabel *infoLabel;
        QLabel *info;

    public:
        MinMaxTempWidgetItem(const QString iconPath, const QString infoName, QWidget *parent = nullptr);
        void updateData(const int value, const QString unit);
    };

public:
    MinMaxTempWidget(QWidget *parent = nullptr);
    void updateData(const int minTempValue, const int maxTempValue);
};

class SunWidget : public QWidget
{
    QHBoxLayout *mainLayout;

    class SunWidgetItem : public QWidget{

        static const int iconWidth = 40;
        static const int iconHeight = 40;
        QHBoxLayout *mainLayout;
        QVBoxLayout *timeLayout;
        QPixmap *infoIcon;
        QLabel *infoIconLabel;
        QLabel *infoLabel;
        QLabel *info;
        QLabel *additionalinfo;

    public:
        SunWidgetItem(const QString iconPath, const QString infoName, QWidget *parent = nullptr);
        void updateData(const QTimeZone &timezone, const QVector<QString> value);
    };

public:
    SunWidget(QWidget *parent = nullptr);
    void updateData(const QTimeZone &timezone, const QVector<QString> sunriseValue, const QVector<QString> sunsetValue);
};

class singleWidgetItem : public QWidget{

    static const int iconWidth = 35;
    static const int iconHeight = 35;
    QVBoxLayout *mainLayout;
    QHBoxLayout *lowerLayout;
    QPixmap *infoIcon;
    QLabel *infoIconLabel;
    QLabel *infoLabel;
    QLabel *info;

public:
    singleWidgetItem(const QString iconPath, const QString infoName, QWidget *parent = nullptr);
    void updateData(const int value, const QString unit);
};

class HumidityUvRainWidget : public QWidget
{
    QHBoxLayout *mainLayout;
    singleWidgetItem *humidity;
    singleWidgetItem *uvIndex;
    singleWidgetItem *rain;

    QString uvIndextoDescription(const int uvIndex);
public:
    HumidityUvRainWidget(QWidget *parent = nullptr);
    void updateData(const int humidity, const int uvIndex, const int rain);
};

class VisibilityPressureSnowWidget : public QWidget
{
    QHBoxLayout *mainLayout;
    singleWidgetItem *visibility;
    singleWidgetItem *pressure;
    singleWidgetItem *snow;

public:
    VisibilityPressureSnowWidget(QWidget *parent = nullptr);
    void updateData(const int visibilityValue, const int pressureValue, double snowValue);
};

class WindInfoWidget : public QWidget
{
    static const int iconWidth = 60;
    static const int iconHeight = 60;
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

public:
    WindInfoWidget(QWidget *parent = nullptr);
    void updateData(const int windSpeed, const int windGusts, const int windDirection);
};

class HourlyWeatherWidget : public QWidget
{
    static const int hoursPerDay = 24;
    static const int iconWidth = 25;
    static const int iconHeight = 25;
    static const int widgetItemWidth = 70;
    static const int widgetItemHeight = 100;
    QVBoxLayout *mainLayout;
    QScrollArea *hourlyWeatherArea;
    QWidget *hourlyWeatherContents;
    QHBoxLayout *itemsLayout;

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
    static const int daysPerWeek = 7;
    static const int iconWidth = 35;
    static const int iconHeight = 35;
    static const int dayNameLabelWidth = 100;
    static const int padding = 20;
    static const int dailyMaxLabelWidth = 60;
    QGridLayout *mainLayout;

    class DailyWidgetItem : public QWidget
    {
        static const int border = 15;
        QHBoxLayout *dailyLayout;
        QLabel *dayNameLabel;
        QPixmap dayWeatherIcon;
        QLabel *dayWeatherIconLabel;
        QLabel *dailyminTempLabel;
        QPixmap temperatureIcon;
        QLabel *temperatureIconLabel;
        QLabel *dailymaxTempLabel;

    protected:
        void paintEvent(QPaintEvent *event) override;

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
