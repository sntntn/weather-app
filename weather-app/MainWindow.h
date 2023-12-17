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
    void getLocationData(const GeoLocationData &location);
    void refreshPages();

signals:
    void detailedWeatherPageShown(const GeoLocationData &data); // todo sharedptr
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

    void getSavedLocationsData();
    void requestUserLocationData();
    void serializeData();

};
#endif // MAINWINDOW_H
