#ifndef DETAILEDWEATHERPAGE_H
#define DETAILEDWEATHERPAGE_H

#include "Page.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QVector>
#include <QPushButton>
#include <QSharedPointer>
#include <QScrollBar>
#include <QTimer>
#include <QLabel>
#include <QTimeZone>

#include "GeoLocationData.h"

class WeatherData;
class MainWindow;
class WeatherWidget;
class GeoLocationData;
class DetailedWeatherData;

class DetailedWeatherPage : public Page
{
    Q_OBJECT

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
        QVBoxLayout *hourLayout;
        QLabel *hourLabel;
        QPixmap *hourWeatherIcon;
        QLabel *hourWeatherIconLabel;
        QLabel *hourTempLabel;

    public:
        HourlyWeatherWidget(QWidget *parent = nullptr);
        void updateData(const int tempText, const int weatherCode, const bool isDay, const QString timeStamp);
    };

    class DailyWeatherWidget : public QWidget
    {
        QHBoxLayout *dailyLayout;
        QLabel *dayNameLabel;
        QPixmap *dayWeatherIcon;
        QLabel *dayWeatherIconLabel;
        QLabel *dailyminTempLabel;
        QLabel *dailymaxTempLabel;

    public:
        DailyWeatherWidget(QWidget *parent = nullptr);
        void updateData(const QString dayName, const int weatherCode, const int minTemp, const int maxTemp);
    };

public:
    explicit DetailedWeatherPage(QWidget *parent = nullptr);
    ~DetailedWeatherPage() = default;

    void resizeEvent(QResizeEvent *event) override;

public slots:
    void addNewWidget(const QSharedPointer<Data> &data) override;
    void setData(const GeoLocationData &data); // todo shared ptr
    void showData(const QSharedPointer<Data> &data);

private slots:
    void addButtonClicked();
    void homeButtonClicked();

signals:
    void locationSaved(const QSharedPointer<Data> &data);

private:
    static const int spacerWidth = 40;
    static const int iconWidth = 100;
    static const int iconHeight = 100;

    QSharedPointer<DetailedWeatherData> data;
    QHBoxLayout *mainLayout;
    QScrollArea *widgetsScrollArea;
    QScrollArea *weatherScrollArea;
    QWidget *widgetsScrollAreaContents;
    QWidget *weatherScrollAreaContents;
    QGridLayout *widgetsLayout;
    QVBoxLayout *weatherLayout;
    QHBoxLayout *buttonsLayout;
    QPushButton *returnToHomePage;
    QSpacerItem *horizontalSpacer;
    QPushButton *addToSavedLocations;
    QTimer *scrollTimer;
    QLabel *locationLabel;
    BasicInfoWidget *basicInfo;
    QLabel *minmaxTemperature;
    QLabel *compassLabel;
    QPixmap *initialCompassIcon;
    QPixmap *arrowIcon;
    QScrollArea *hourlyWeatherArea;
    QWidget *hourlyWeatherContents;
    QHBoxLayout *hourlyLayout;
    QGridLayout *dailyLayout;
    WeatherWidget *selectedWidget;

    void highlightWidget();
};

#endif // DETAILEDWEATHERPAGE_H
