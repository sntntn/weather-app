#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSharedPointer>

#include "Page.h"

class WeatherWidget;
class WeatherData;
class MainWindow;

class HomePage : public Page
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

public slots:
    void addNewWidget(QSharedPointer<WeatherData>) override;

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
};

#endif // HOMEPAGE_H
