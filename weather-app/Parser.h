#ifndef PARSER_H
#define PARSER_H

#include "WeatherData.h"

class Parser
{
public:
    explicit Parser();
    WeatherData* parseWeatherData(const QString& jsonData);

};

#endif // PARSER_H
