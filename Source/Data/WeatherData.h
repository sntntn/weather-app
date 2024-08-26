#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include "Data.h"

#include <QString>
#include <QTimeZone>

#include "GeoLocationData.h"

class WeatherData : public Data
{
public:
    WeatherData(const GeoLocationData &location,
                int temperature,
                int highestTemperature,
                int lowestTemperature,
                int weatherCode,
                bool isDay,
                QTimeZone timezone);

    [[nodiscard]] inline auto location() const -> GeoLocationData { return m_location; }

    [[nodiscard]] inline auto temperature() const -> int { return m_temperature; }

    [[nodiscard]] inline auto highestTemperature() const -> int { return m_highestTemperature; }

    [[nodiscard]] inline auto lowestTemperature() const -> int { return m_lowestTemperature; }

    [[nodiscard]] inline auto weatherCode() const -> int { return m_weatherCode; }

    [[nodiscard]] inline auto isDay() const -> bool { return m_isDay; }

    [[nodiscard]] inline auto timezone() const -> QTimeZone { return m_timezone; }

private:
  GeoLocationData m_location;
  int			  m_temperature;
  int			  m_highestTemperature;
  int			  m_lowestTemperature;
  int			  m_weatherCode;
  bool			  m_isDay;
  QTimeZone		  m_timezone;
};

#endif // WEATHERDATA_H
