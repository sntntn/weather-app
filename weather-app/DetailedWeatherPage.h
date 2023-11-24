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
class WeatherWidget;

class DetailedWeatherPage : public QWidget
{
    Q_OBJECT

public:
    explicit DetailedWeatherPage(MainWindow* mainWindow, QWidget *parent = nullptr);
    ~DetailedWeatherPage();

    void setData(const QString& location);
    void getLocations(const QVector<WeatherData*>& m_locations);
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
    QHBoxLayout *buttonsLayout;
    QPushButton *returnToHomePage;
    QPushButton *addToSavedLocations;

    QVector<WeatherWidget *> m_widgets;


};

#endif // DETAILEDWEATHERPAGE_H
