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

#include "GeoLocationData.h"

class WeatherData;
class MainWindow;
class WeatherWidget;
class GeoLocationData;
class DetailedWeatherData;

class DetailedWeatherPage : public Page
{
    Q_OBJECT

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
    void locationSaved(const GeoLocationData &data);

private:
    static const int spacerWidth = 40;
    static const int iconWidth = 100;
    static const int iconHeight = 100;

    GeoLocationData data; // todo sharedptr
    QHBoxLayout *mainLayout;
    QScrollArea *widgetsScrollArea;
    QScrollArea *weatherScrollArea;
    QWidget *widgetsScrollAreaContents;
    QWidget *weatherScrollAreaContents;
    QGridLayout *widgetsLayout;
    QVBoxLayout *weatherLayout;
    QHBoxLayout *basicInfoLayout;
    QVBoxLayout *leftBasicInfo;
    QVBoxLayout *rightBasicInfo;
    QHBoxLayout *buttonsLayout;
    QPushButton *returnToHomePage;
    QSpacerItem *horizontalSpacer;
    QPushButton *addToSavedLocations;
    QTimer *scrollTimer;
    QLabel *locationLabel;
    QLabel *temperatureLabel;
    QLabel *minmaxTemperature;
    QLabel *weatherDescriptionLabel;
    QLabel *iconLabel;
    QPixmap *weatherIcon;
    QLabel *dateLabel;
    QLabel *timeLabel;
    QLabel *feelsLikeLabel;
    QLabel *compassLabel;
    QPixmap *initialCompassIcon;
    QPixmap *arrowIcon;
    WeatherWidget *selectedWidget;

    void highlightWidget();
    QString getDaySuffix(const int day);
    QString weatherCodeToDescription(const int weatherCode);
    QString weatherCodeToIcon(const int weatherCode, const bool isDay);
};

#endif // DETAILEDWEATHERPAGE_H
