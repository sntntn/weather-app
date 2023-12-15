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
    void afterHomePressed();


private slots:
    void addButtonClicked();

signals:
    void locationSaved(const GeoLocationData &data);

private:
    static const int spacerWidth = 40;

    GeoLocationData data; // todo sharedptr
    QHBoxLayout *mainLayout;
    QScrollArea *widgetsScrollArea;
    QScrollArea *weatherScrollArea;
    QWidget *widgetsScrollAreaContents;
    QWidget *weatherScrollAreaContents;
    QGridLayout *widgetsLayout;
    QGridLayout *weatherLayout;
    QPushButton *returnToHomePage;
    QSpacerItem *horizontalSpacer;
    QPushButton *addToSavedLocations;
    QTimer *scrollTimer;
    QLabel *locationLabel;
    QLabel *temperatureLabel;
    QLabel *minmaxTemperature;
    WeatherWidget *selectedWidget;

    void highlightWidget();
    void scrollToMaximum(); // todo kada se stvarno doda widget u ScrollAreaContenst
};

#endif // DETAILEDWEATHERPAGE_H
