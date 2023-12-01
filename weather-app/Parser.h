#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QSharedPointer>

class WeatherData;

class Parser
{
public:
    explicit Parser();
    static QSharedPointer<WeatherData> parseWeatherData(const QString& jsonData);
    static QSharedPointer<WeatherData> parseDetailedWeatherData(const QString& jsonData);
    static QSharedPointer<WeatherData> parseGeoLocationData(const QString& jsonData);


};

#endif // PARSER_H
