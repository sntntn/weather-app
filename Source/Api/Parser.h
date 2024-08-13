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
  static WeatherData *parseWeatherData(const QString &jsonData, const GeoLocationData &geoLocation);
  static QSharedPointer<DetailedWeatherData> parseDetailedWeatherData(const QString			&jsonData,
																	  const GeoLocationData &geoLocation);
  static void parseGeocodingData(const QJsonArray &resultsArray, QList<GeoLocationData> &locations);
};

#endif // PARSER_H
