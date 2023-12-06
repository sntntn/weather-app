#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class WeatherData;
class GeoLocationData;
class WeatherWidget;
class QStackedWidget;
class HomePage;
class DetailedWeatherPage;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void showHomePage();
    void showDetailedWeatherPage(const GeoLocationData &data); // todo sharedptr
    void saveNewLocation(const GeoLocationData& location); // todo sharedptr
    void handleLocationObjectSelected(const GeoLocationData& locationData);
    void getLocationData(const GeoLocationData &location);

signals:
    void detailedWeatherPageShown(const GeoLocationData &data); // todo sharedptr

private:
    Ui::MainWindow *ui;
    HomePage *homePage;
    DetailedWeatherPage *detailedWeather;
    QStackedWidget *stackedWidget;

    double m_lastLongitude; // todo?
    double m_lastLatitude;

    void getSavedLocationsData();
    void refreshPages();

public:
    QVector<GeoLocationData> savedLocations; // todo sharedptr

};
#endif // MAINWINDOW_H
