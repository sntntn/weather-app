#ifndef DETAILEDWEATHERDATA_H
#define DETAILEDWEATHERDATA_H

#include "WeatherData.h"

class GeoLocationData;

class DetailedWeatherData : public WeatherData
{
public:
    explicit DetailedWeatherData(const GeoLocationData &location,
                                 int temperature,
                                 int weatherCode,
                                 bool isDay,
                                 const QTimeZone &timezone,
                                 int windSpeed,
                                 int windGusts,
                                 int windDirection,
                                 int apparentTemperature,
                                 int precipitation,
                                 double snowDepth,
                                 int uvIndex,
                                 int humidity,
                                 int visibility,
                                 int pressure,
                                 const QVector<int> &hourlyTemperature,
                                 const QVector<int> &fullHourlyTemperature,
                                 const QVector<int> &hourlyCode,
                                 const QVector<bool> &hourlyIsDay,
                                 const QVector<QString> &hourlyTimeStamp,
                                 const QVector<int> &weeklyMaxTemp,
                                 const QVector<int> &weeklyMinTemp,
                                 const QVector<int> &weeklyCode,
                                 const QVector<QString> &sunrise,
                                 const QVector<QString> &sunset,
                                 const QVector<QString> &weeklyDayName);

    [[nodiscard]] inline auto location() const -> GeoLocationData { return m_location; }
    [[nodiscard]] inline auto temperature() const -> int { return m_temperature; }
    [[nodiscard]] inline auto weatherCode() const -> int { return m_weatherCode; }
    [[nodiscard]] inline auto isDay() const -> bool { return m_isDay; }
    [[nodiscard]] inline auto timezone() const -> QTimeZone { return m_timezone; }
    [[nodiscard]] inline auto windSpeed() const -> int { return m_windSpeed; }
    [[nodiscard]] inline auto windGusts() const -> int { return m_windGusts; }
    [[nodiscard]] inline auto windDirection() const -> int { return m_windDirection; }
    [[nodiscard]] inline auto apparentTemperature() const -> int { return m_apparentTemperature; }
    [[nodiscard]] inline auto precipitation() const -> int { return m_precipitation; }
    [[nodiscard]] inline auto snowDepth() const -> double { return m_snowDepth; }
    [[nodiscard]] inline auto uvIndex() const -> int { return m_uvIndex; }
    [[nodiscard]] inline auto humidity() const -> int { return m_humidity; }
    [[nodiscard]] inline auto visibility() const -> int { return m_visibility; }
    [[nodiscard]] inline auto pressure() const -> int { return m_pressure; }
    [[nodiscard]] inline auto hourlyTemperature() const -> QVector<int>
    {
        return m_hourlyTemperature;
  }
  [[nodiscard]] inline auto fullHourlyTemperature() const -> QVector<int>
  {
	return m_fullHourlyTemperature;
  }
  [[nodiscard]] inline auto hourlyCode() const -> QVector<int> { return m_hourlyCode; }
  [[nodiscard]] inline auto hourlyIsDay() const -> QVector<bool> { return m_hourlyIsDay; }
  [[nodiscard]] inline auto hourlyTimeStamp() const -> QVector<QString>
  {
	return m_hourlyTimeStamp;
  }
  [[nodiscard]] inline auto weeklyMaxTemp() const -> QVector<int> { return m_weeklyMaxTemp; }
  [[nodiscard]] inline auto weeklyMinTemp() const -> QVector<int> { return m_weeklyMinTemp; }
  [[nodiscard]] inline auto weeklyCode() const -> QVector<int> { return m_weeklyCode; }
  [[nodiscard]] inline auto sunrise() const -> QVector<QString> { return m_sunrise; }
  [[nodiscard]] inline auto sunset() const -> QVector<QString> { return m_sunset; }
  [[nodiscard]] inline auto weeklyDayName() const -> QVector<QString> { return m_weeklyDayName; }

  private:
  GeoLocationData  m_location;
  int			   m_temperature;
  int			   m_weatherCode;
  bool			   m_isDay;
  QTimeZone		   m_timezone;
  int			   m_windSpeed;
  int			   m_windGusts;
  int			   m_windDirection;
  int			   m_apparentTemperature;
  int			   m_precipitation;
  double		   m_snowDepth;
  int			   m_uvIndex;
  int			   m_humidity;
  int			   m_visibility;
  int			   m_pressure;
  QVector<int>	   m_hourlyTemperature;
  QVector<int>	   m_fullHourlyTemperature;
  QVector<int>	   m_hourlyCode;
  QVector<bool>	   m_hourlyIsDay;
  QVector<QString> m_hourlyTimeStamp;
  QVector<int>	   m_weeklyMaxTemp;
  QVector<int>	   m_weeklyMinTemp;
  QVector<int>	   m_weeklyCode;
  QVector<QString> m_sunrise;
  QVector<QString> m_sunset;
  QVector<QString> m_weeklyDayName;
};

#endif // DETAILEDWEATHERDATA_H
