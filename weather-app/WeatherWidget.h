#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

class WeatherData;

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherWidget(const QSharedPointer<WeatherData> &data_, QWidget *parent = nullptr);
    ~WeatherWidget();
    void mousePressEvent(QMouseEvent *event) override;

    const QSharedPointer<WeatherData> data;

signals:
    void clicked(const QSharedPointer<WeatherData> &data);

private:
    QHBoxLayout *hBox;
    QVBoxLayout *leftVBox;
    QVBoxLayout *rightVBox;
    QLabel* locationLabel;
    QLabel* temperatureLabel;
    QLabel* timeLabel;
    QLabel* iconLabel;
    QPixmap weatherIcon;
};

#endif // WEATHERWIDGET_H
