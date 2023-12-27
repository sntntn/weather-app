#include "ApiHandler.h"

ApiHandler::ApiHandler(QObject *parent)
    : QThread{parent}
    , networkManager(new QNetworkAccessManager())
{
    networkManager->moveToThread(this);
}

ApiHandler::~ApiHandler()
{
    delete networkManager;
}
