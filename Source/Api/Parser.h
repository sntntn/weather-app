#ifndef PARSER_H
#define PARSER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QString>

class WeatherData;
class DetailedWeatherData;
class GeoLocationData;

class Parser
{
public:
  Parser() = default;
  static auto parseWeatherData(const QString &jsonData, const GeoLocationData &geoLocation)
      -> WeatherData *;
  static auto parseDetailedWeatherData(const QString &jsonData, const GeoLocationData &geoLocation)
      -> QSharedPointer<DetailedWeatherData>;
  static void parseGeocodingData(const QJsonArray &resultsArray, QList<GeoLocationData> &locations);
};

#endif // PARSER_H
