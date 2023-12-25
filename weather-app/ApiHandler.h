#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>

class Data;

class ApiHandler : public QObject
{
    Q_OBJECT

public:
    explicit ApiHandler(QObject *parent = nullptr);
    virtual ~ApiHandler();

protected slots:
    virtual void replyFinished(QNetworkReply* reply) = 0;

protected:
    QNetworkAccessManager* networkManager;
};

#endif // APIHANDLER_H
