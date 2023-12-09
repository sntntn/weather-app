#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Settings;
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
    void refreshPages();

signals:
    void detailedWeatherPageShown(const GeoLocationData &data); // todo sharedptr
    void deletePageWidgets();

private:
    Ui::MainWindow *ui;
    Settings &settings;
    HomePage *homePage;
    DetailedWeatherPage *detailedWeather;
    QStackedWidget *stackedWidget;

    void getSavedLocationsData();
};
#endif // MAINWINDOW_H
