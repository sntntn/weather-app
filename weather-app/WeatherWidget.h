#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

class WeatherData;
class GeoLocationData;

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherWidget(const QSharedPointer<WeatherData> &data, QWidget *parent = nullptr);
    ~WeatherWidget() = default;
    void mousePressEvent(QMouseEvent *event) override;

    void setHighlighted();
    void resetHighlight();

    const QSharedPointer<WeatherData> data;

signals:
    void clicked(const GeoLocationData &data);

private:
    static const int hBoxSpacing = 5;
    static const int hBoxMarginSize = 10;
    static const int locationFontSize = 18;
    static const int timeFontSize = 14;
    static const int temperatureFontSize = 24;
    static const int minmaxTemperatureFontSize = 14;
    static const int iconWidth = 50;
    static const int iconHeight = 50;

    QHBoxLayout *hBox;
    QVBoxLayout *leftVBox;
    QVBoxLayout *rightVBox;
    QLabel* temperatureLabel;
    QLabel* locationLabel;
    QLabel* minmaxTemperatureLabel;
    QLabel* timeLabel;
    QLabel* iconLabel;
    QPixmap weatherIcon;

    QString weatherCodeToIcon(int weatherCode, bool isDay);
};

#endif // WEATHERWIDGET_H
