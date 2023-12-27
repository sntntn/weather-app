#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStackedWidget;
class QGeoPositionInfo;
class Settings;
class WeatherData;
class GeoLocationData;
class WeatherWidget;
class HomePage;
class DetailedWeatherPage;
class UserLocation;
class GeoLocationData;
class WeatherAPI;

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
    void showDetailedWeatherPage(const GeoLocationData &data);
    void getLocationData(const GeoLocationData &location);
    void refreshPages();

signals:
    void detailedWeatherPageShown(const GeoLocationData &data);
    void deletePageWidgets();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    Settings &settings;
    HomePage *homePage;
    DetailedWeatherPage *detailedWeather;
    QStackedWidget *stackedWidget;
    UserLocation *userLocation;
    WeatherAPI *weatherApi;

    void getSavedLocationsData();
    void requestUserLocationData();
    void serializeData();

};
#endif // MAINWINDOW_H
