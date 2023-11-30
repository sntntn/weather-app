#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class WeatherData;
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
    void showDetailedWeatherPage(const QSharedPointer<WeatherData> &data);

signals:
    void detailedWeatherPageShown(const QSharedPointer<WeatherData> &data);
private slots:
    void updateGeocodingData(const QString& place, double latitude, double longitude);


private:
    Ui::MainWindow *ui;
    HomePage *homePage;
    DetailedWeatherPage *detailedWeather;
    QStackedWidget *stackedWidget;

    double m_lastLongitude;
    double m_lastLatitude;
};
#endif // MAINWINDOW_H
