#ifndef PARSER_H
#define PARSER_H

#include <QString>

class WeatherData;

class Parser
{
public:
    explicit Parser();
    WeatherData* parseWeatherData(const QString& jsonData);

};

#endif // PARSER_H
