#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

class WeatherWidget;
class WeatherData;
class MainWindow;

class Page : public QWidget
{
    Q_OBJECT
public:
    virtual ~Page() = default;

public slots:
    virtual void addNewWidget(WeatherData*) = 0;

protected:
    explicit Page(QWidget *parent = nullptr);

    QVector<WeatherWidget*> m_widgets;
    MainWindow *mainWindow;
};

#endif // PAGE_H
