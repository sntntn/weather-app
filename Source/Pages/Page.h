#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QSharedPointer>

class WeatherWidget;
class Data;
class MainWindow;

class Page : public QWidget
{
    Q_OBJECT
public:
    virtual ~Page() = default;

public slots:
    virtual void addNewWidget(const QSharedPointer<Data> &data) = 0;
    virtual void addErrorWidget(const QString &errMsg) = 0;
    void deleteWidgets();

protected:
    explicit Page(QWidget *parent = nullptr);

    QVector<WeatherWidget*> m_widgets;
    MainWindow *mainWindow;
};

#endif // PAGE_H
