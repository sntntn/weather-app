#ifndef DETAILEDWEATHERPAGE_H
#define DETAILEDWEATHERPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QVector>
#include <QPushButton>
#include <QSharedPointer>


#include "Page.h"

class WeatherData;
class MainWindow;
class WeatherWidget;

class DetailedWeatherPage : public Page
{
    Q_OBJECT

public:
    explicit DetailedWeatherPage(QWidget *parent = nullptr);
    ~DetailedWeatherPage();

    void resizeEvent(QResizeEvent *event) override;


public slots:
    void setData(const QSharedPointer<WeatherData> &data);
    void addNewWidget(const QSharedPointer<WeatherData> &data) override;

private:
    QHBoxLayout *mainLayout;
    QScrollArea *widgetsScrollArea;
    QScrollArea *weatherScrollArea;
    QWidget *widgetsScrollAreaContents;
    QWidget *weatherScrollAreaContents;
    QVBoxLayout *widgetsLayout;
    QVBoxLayout *weatherLayout;
    QHBoxLayout *buttonsLayout;
    QPushButton *returnToHomePage;
    QPushButton *addToSavedLocations;
};

#endif // DETAILEDWEATHERPAGE_H
