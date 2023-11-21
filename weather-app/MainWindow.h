#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WeatherData.h"
#include "WeatherWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addNewWidget(WeatherData* data);

private:
    Ui::MainWindow *ui;
    QVector<WeatherWidget*> m_widgets;
    static const QString OPEN_CAGE_API_KEY; //TO DO CONFIG FILE
};
#endif // MAINWINDOW_H
