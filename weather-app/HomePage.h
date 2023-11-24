#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>

class WeatherWidget;
class WeatherData;
class MainWindow;

class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();


signals:
    void weatherWidgetClicked(WeatherData* data);

public slots:
    void addNewWidget(WeatherData* data);

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
    QVector<WeatherWidget*> m_widgets;
    MainWindow *mainWindow;
};

#endif // HOMEPAGE_H
