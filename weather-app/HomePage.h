#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSharedPointer>

#include "Page.h"
#include "geocodingapi.h"

class WeatherWidget;
class WeatherData;
class MainWindow;

class HomePage : public Page
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

signals:
    void searchBarPressed(const QString& location);
public slots:
    void addNewWidget(const QSharedPointer<Data> &data) override;
    void searchBarEnter();

private:

    QVBoxLayout *mainLayout;
    QLineEdit *searchBar;
    QScrollArea *scrollArea;
    QHBoxLayout *scrollLayout;
    QWidget *scrollAreaContents;
    QWidget *leftWidget;
    QWidget *rightWidget;
    QVBoxLayout *leftVBox;
    QVBoxLayout *rightVBox;

    GeocodingAPI geocodingApi;
};

#endif // HOMEPAGE_H
