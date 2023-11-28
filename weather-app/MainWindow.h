#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class WeatherData;
class WeatherWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<WeatherWidget*> m_widgets;
};
#endif // MAINWINDOW_H
