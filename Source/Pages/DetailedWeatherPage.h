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

#include "GeoLocationData.h"

class WeatherData;
class MainWindow;
class WeatherWidget;

class DetailedWeatherPage : public Page
{
    Q_OBJECT

public:
    explicit DetailedWeatherPage(QWidget *parent = nullptr);
    ~DetailedWeatherPage() = default;

    void resizeEvent(QResizeEvent *event) override;

public slots:
    void addNewWidget(const QSharedPointer<Data> &data) override;
    void addErrorWidget(const QString &errMsg) override;
    void setData(const GeoLocationData &data); // todo shared ptr

private slots:
    void addButtonClicked();
    void homeButtonClicked();

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
    WeatherWidget *selectedWidget;

    void highlightWidget();
};

#endif // DETAILEDWEATHERPAGE_H
