#ifndef DETAILEDWEATHERPAGE_H
#define DETAILEDWEATHERPAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QVector>
#include <QPushButton>

class WeatherData;
class MainWindow;

class DetailedWeatherPage : public QWidget
{
    Q_OBJECT

public:
    explicit DetailedWeatherPage(MainWindow* mainWindow, QWidget *parent = nullptr);
    ~DetailedWeatherPage();

    void setData(QString location);
    void getLocations(QVector<WeatherData*> m_locations);
    void drawWidgets(QVector<WeatherData*> m_locations);
    void resizeEvent(QResizeEvent *event) override;

signals:

private slots:
    void setLocation(QString location);

private:
    QVector<WeatherData*> m_locations;
    MainWindow *m_mainWindow;
    QHBoxLayout *mainLayout;
    QScrollArea *widgetsScrollArea;
    QScrollArea *weatherScrollArea;
    QWidget *widgetsScrollAreaContents;
    QWidget *weatherScrollAreaContents;
    QVBoxLayout *widgetsLayout;
    QVBoxLayout *weatherLayout;
    QPushButton *returnToHomePage;
    QPushButton *addToSavedLocations;


};

#endif // DETAILEDWEATHERPAGE_H
