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
    void onWeatherWidgetClicked(WeatherData* data);
    void addNewWidget(WeatherData* data);

private:
    Ui::MainWindow *ui;
    QVector<WeatherData*> m_locations;
    QStackedWidget *stackedWidget;
    HomePage *homePage;
    DetailedWeatherPage *detailedWeather;
    static const QString OPEN_CAGE_API_KEY; //TO DO CONFIG FILE
};
#endif // MAINWINDOW_H
