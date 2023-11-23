#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "WeatherWidget.h"
#include "WeatherData.h"

class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = nullptr);

signals:

public slots:
    void addNewWidget(WeatherData* data);

private:
    QVBoxLayout *mainLayout;
    QLineEdit *searchBar;
    QScrollArea *scrollArea;
    QHBoxLayout *scrollLayout;
    QWidget *leftWidget;
    QWidget *rightWidget;
    QVBoxLayout *leftVBox;
    QVBoxLayout *rightVBox;

    QVector<WeatherWidget*> m_widgets;
};

#endif // HOMEPAGE_H
