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

    void setHighlight();
    void resetHighlight();

    const QSharedPointer<WeatherData> data;

signals:
    void clicked(const GeoLocationData &data);

private:
    static const int hBoxSpacing = 10;
    static const int hBoxMarginSize = 10;
    static const int locationFontSize = 20;
    static const int timeFontSize = 14;
    static const int temperatureFontSize = 45;
    static const int minmaxTemperatureFontSize = 14;
    static const int iconWidth = 80;
    static const int iconHeight = 80;

    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QLabel* temperatureLabel;
    QLabel* locationLabel;
    QLabel* maxTemperatureLabel;
    QLabel* minTemperatureLabel;
    QLabel* timeLabel;
    QLabel* iconLabel;
    QPixmap weatherIcon;

    QString weatherCodeToIcon(const int weatherCode, const bool isDay);
    int adjustLabelFontSize(const QString &fontName);
};

#endif // WEATHERWIDGET_H
