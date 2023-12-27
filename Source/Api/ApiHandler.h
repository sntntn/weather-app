#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Data;

class ApiHandler : public QThread
{
    Q_OBJECT
public:
    explicit ApiHandler(QObject *parent = nullptr);
    virtual ~ApiHandler();

signals:
    void dataFetched(const QSharedPointer<Data> &data);

protected slots:
    virtual void replyFinished(QNetworkReply* reply) = 0;

protected:
    QNetworkAccessManager* networkManager;
    virtual void run() override = 0;
};

#endif // APIHANDLER_H
