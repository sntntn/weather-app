#ifndef DETAILEDWEATHERPAGE_H
#define DETAILEDWEATHERPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QVector>

class WeatherData;


class DetailedWeatherPage : public QWidget
{
    Q_OBJECT

public:
    explicit DetailedWeatherPage(QWidget *parent = nullptr);
    void setData(WeatherData* data);
    void getLocations(QVector<WeatherData*> m_locations);
    void drawWidgets(QVector<WeatherData*> m_locations);


signals:

private:
    QVector<WeatherData*> m_locations;
    QHBoxLayout *mainLayout;
    QScrollArea *widgetsScrollArea;
    QScrollArea *weatherScrollArea;
    QWidget *widgetsScrollAreaContents;
    QWidget *weatherScrollAreaContents;
    QVBoxLayout *widgetsLayout;
    QVBoxLayout *weatherLayout;

};

#endif // DETAILEDWEATHERPAGE_H
