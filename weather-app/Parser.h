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
    static QSharedPointer<WeatherData> parseWeatherData(const QString& jsonData, const GeoLocationData &geoLocation);
    static QSharedPointer<DetailedWeatherData> parseDetailedWeatherData(const QString& jsonData, const GeoLocationData &geoLocation);

};

#endif // PARSER_H
