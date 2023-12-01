#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QSharedPointer>

class WeatherData;
class DetailedWeatherData;
class GeoLocationData;

class Parser
{
public:
    explicit Parser();
    static QSharedPointer<WeatherData> parseWeatherData(const QString& jsonData);
    static QSharedPointer<DetailedWeatherData> parseDetailedWeatherData(const QString& jsonData);
    static QSharedPointer<GeoLocationData> parseGeoLocationData(const QString& jsonData);


};

#endif // PARSER_H
