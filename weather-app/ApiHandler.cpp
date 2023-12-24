#include "ApiHandler.h"

ApiHandler::ApiHandler(QObject *parent)
    : QObject{parent}
    , networkManager(new QNetworkAccessManager())
{ }

ApiHandler::~ApiHandler()
{
    delete networkManager;
}
