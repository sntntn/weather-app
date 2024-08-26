#ifndef DETAILEDWEATHERPAGE_H
#define DETAILEDWEATHERPAGE_H

#include "Page.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QSharedPointer>
#include <QTimeZone>
#include <QTimer>
#include <QVBoxLayout>
#include <QVector>
#include <QWidget>

#include "DetailedPageWidgets.h"
#include "DetailedWeatherAPI.h"
#include "GeoLocationData.h"

class WeatherData;
class MainWindow;
class WeatherWidget;
class GeoLocationData;
class DetailedWeatherData;

class DetailedWeatherPage : public Page
{
  Q_OBJECT

public:
  explicit DetailedWeatherPage(QWidget *parent = nullptr);
  ~DetailedWeatherPage() override = default;

  void resizeEvent(QResizeEvent *event) override;

  QSharedPointer<DetailedWeatherData> data;
  DetailedWeatherAPI				 *api;

public slots:
    void addNewWidget(QSharedPointer<WeatherData> data) override;
    void addErrorWidget(const QString &errMsg) override;
    void getData(const GeoLocationData &data);
    void setData(QSharedPointer<DetailedWeatherData> data);

private slots:
    void addButtonClicked();
    void homeButtonClicked();

signals:
  void locationSaved(const GeoLocationData &data);
  void errorOccurred(const QString &errMsg);
  void detailedDataFetched();

private:
  static const int spacerWidth = 40;

  QHBoxLayout				   *mainLayout;
  QScrollArea				   *widgetsScrollArea;
  QScrollArea				   *weatherScrollArea;
  QWidget					   *widgetsScrollAreaContents;
  QWidget					   *weatherScrollAreaContents;
  QGridLayout				   *widgetsLayout;
  QVBoxLayout				   *weatherLayout;
  QHBoxLayout				   *buttonsLayout;
  QPushButton				   *returnToHomePage;
  QSpacerItem				   *horizontalSpacer;
  QPushButton				   *addToSavedLocations;
  QTimer					   *scrollTimer;
  LocationInfoWidget		   *locationInfo;
  BasicInfoWidget			   *basicInfo;
  HumidityUvRainWidget		   *humidityUvRain;
  VisibilityPressureSnowWidget *visibilityPressureSnow;
  WindInfoWidget			   *windInfo;
  HourlyWeatherWidget		   *hourlyWidget;
  DailyWeatherWidget		   *dailyWidget;
  WeatherWidget				   *selectedWidget;
  MinMaxTempWidget			   *minmaxWidget;
  SunWidget					   *sunWidget;

  void highlightWidget();
};

#endif // DETAILEDWEATHERPAGE_H
