#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QSharedPointer>

class WeatherData;

class Parser
{
public:
    explicit Parser();
    QSharedPointer<WeatherData> parseWeatherData(const QString& jsonData);

};

#endif // PARSER_H
