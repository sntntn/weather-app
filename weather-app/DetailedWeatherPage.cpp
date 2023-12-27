#include "DetailedWeatherPage.h"

#include "MainWindow.h"
#include "WeatherData.h"
#include "WeatherWidget.h"
#include "GeoLocationData.h"
#include "Settings.h"
#include "DetailedWeatherAPI.h"
#include "DetailedWeatherData.h"

#include <iostream>
#include <QStackedWidget>
#include <QTimer>
#include <QPainter>
#include <QTransform>
#include <QFrame>

DetailedWeatherPage::DetailedWeatherPage(QWidget *parent)
    : Page{parent}
    , mainLayout(new QHBoxLayout(this))
    , widgetsScrollArea(new QScrollArea())
    , weatherScrollArea(new QScrollArea())
    , widgetsScrollAreaContents(new QWidget())
    , weatherScrollAreaContents(new QWidget())
    , widgetsLayout(new QGridLayout())
    , weatherLayout(new QVBoxLayout())
    , buttonsLayout(new QHBoxLayout())
    , returnToHomePage(new QPushButton("< Home"))
    , horizontalSpacer(new QSpacerItem(spacerWidth, 0, QSizePolicy::Expanding, QSizePolicy::Minimum))
    , addToSavedLocations(new QPushButton("Add"))
    , scrollTimer(new QTimer(this))
    , locationLabel(new QLabel(this))
    , basicInfo(new BasicInfoWidget(this))
    , minmaxTemperature(new QLabel(this))
    , compassLabel(new QLabel(this))
    , initialCompassIcon(new QPixmap("../Resources/wind/whiteCompass.png"))
    , arrowIcon(new QPixmap("../Resources/wind/whiteArrow.png"))
    , hourlyLabel(new QLabel("Hourly"))
    , hourlyWidget(new HourlyWeatherWidget(this))
    , dailyLabel(new QLabel("7-DAY FORECAST"))
    , dailyWidget(new DailyWeatherWidget(this))
    , selectedWidget(nullptr)
{
    widgetsScrollAreaContents->setLayout(widgetsLayout);
    widgetsLayout->setAlignment(Qt::AlignTop);

    widgetsScrollArea->setWidget(widgetsScrollAreaContents);
    widgetsScrollArea->setWidgetResizable(true);
    widgetsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    buttonsLayout->addWidget(returnToHomePage);
    buttonsLayout->addItem(horizontalSpacer);
    buttonsLayout->addWidget(addToSavedLocations);

    weatherLayout->setAlignment(Qt::AlignTop);
    weatherLayout->addLayout(buttonsLayout);

    locationLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    weatherLayout->addWidget(locationLabel, 0, Qt::AlignHCenter);
    weatherLayout->addWidget(basicInfo);
    basicInfo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    minmaxTemperature->setStyleSheet("font-size: 16px;");
    weatherLayout->addWidget(minmaxTemperature, 0, Qt::AlignHCenter);

    hourlyLabel->setStyleSheet("font: bold 15px;");
    weatherLayout->addWidget(hourlyLabel);
    weatherLayout->addWidget(hourlyWidget);

    dailyLabel->setStyleSheet("font: bold 15px; margin: 10px;");
    dailyLabel->setAlignment(Qt::AlignHCenter);
    weatherLayout->addWidget(dailyLabel);
    weatherLayout->addWidget(dailyWidget);

    weatherLayout->addWidget(compassLabel);

    weatherScrollAreaContents->setLayout(weatherLayout);
    weatherScrollArea->setWidget(weatherScrollAreaContents);
    weatherScrollArea->setWidgetResizable(true);

    mainLayout->addWidget(widgetsScrollArea);
    mainLayout->addWidget(weatherScrollArea);

    connect(returnToHomePage, &QPushButton::clicked, this->mainWindow, &MainWindow::showHomePage);
    connect(returnToHomePage, &QPushButton::clicked, this, &DetailedWeatherPage::homeButtonClicked);
    connect(addToSavedLocations, &QPushButton::clicked, this, &DetailedWeatherPage::addButtonClicked);
    connect(this, &DetailedWeatherPage::locationSaved, this->mainWindow, &MainWindow::saveNewLocation);
}

void DetailedWeatherPage::addNewWidget(const QSharedPointer<Data> &data)
{
    QSharedPointer<WeatherData> weatherData = qSharedPointerCast<WeatherData>(data);

    auto *widget = new WeatherWidget(weatherData, widgetsScrollAreaContents);
    connect(widget, &WeatherWidget::clicked, this, &DetailedWeatherPage::setData);

    widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    widget->setMaximumWidth(widgetsScrollArea->viewport()->width());

    int position = static_cast<int>(Settings::instance().savedLocations().indexOf(widget->data->location()));

    if(Settings::instance().shareLocation())
        position++;

    position == -1 ? widgetsLayout->addWidget(widget, 0, 0, 1, 1) // User location widget
                   : widgetsLayout->addWidget(widget, position, 0, 1, 1);

    m_widgets.emplaceBack(widget);

    QStackedWidget* stackedWidget = qobject_cast<QStackedWidget*>(this->parent());
    if (stackedWidget->currentWidget() == this) {
        QTimer::singleShot(100, this, &DetailedWeatherPage::highlightWidget);
    }
}

void DetailedWeatherPage::setData(const GeoLocationData &data) // todo sharedptr
{
    widgetsScrollArea->verticalScrollBar()->setValue(0);

    bool showAddbutton = data.getRenamedPlace() != "My location" &&
                         Settings::instance().savedLocations().indexOf(data) == -1;

    showAddbutton ? this->addToSavedLocations->setVisible(true)
                  : this->addToSavedLocations->setVisible(false);

    //isto ko za MainWindow, saljemo data da postavi a onda u fetchData saljemo koordinate
    auto* api = new DetailedWeatherAPI(data, this);
    //todo ceo data umesto koordinata
    api->fetchData(data.getCoordinates());
    connect(api, &DetailedWeatherAPI::dataFetched, this, &DetailedWeatherPage::showData);
}

void DetailedWeatherPage::showData(const QSharedPointer<Data> &data){
    //todo izbrisi SharedPointer
    QSharedPointer<DetailedWeatherData> detailedData = qSharedPointerCast<DetailedWeatherData>(data);
    this->data = detailedData;
    highlightWidget();

    locationLabel->setText(detailedData->location().getRenamedPlace());
    //todo (need country from api)countryLabel->setText(detailedData->location.get)

    basicInfo->updateData(this->data->weatherCode(), this->data->isDay(), this->data->timezone(),
                          this->data->temperature(), this->data->apparentTemperature());

    minmaxTemperature->setText("H:" + QString::number(detailedData->weeklyMaxTemp()[0]) + "°  L:"
                               + QString::number(detailedData->weeklyMinTemp()[0]) + "°");

    hourlyWidget->updateData(this->data->hourlyTemperature(), this->data->hourlyCode(),
                             this->data->hourlyIsDay(), this->data->hourlyTimeStamp());

    dailyWidget->updateData(this->data->weeklyDayName(), this->data->weeklyCode(),
                            this->data->weeklyMinTemp(), this->data->weeklyMaxTemp());

    QPixmap compassIcon = initialCompassIcon->copy();
    QPainter painter(&compassIcon);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPoint center(compassIcon.width() / 2, compassIcon.height() / 2);

    painter.translate(center);
    painter.rotate(detailedData->windDirection() - 180);
    painter.translate(-center);

    painter.drawPixmap(center.x() - arrowIcon->width() / 2,
                       center.y() - arrowIcon->height() / 2,
                       *arrowIcon);
    painter.end();

    compassLabel->setPixmap(compassIcon.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void DetailedWeatherPage::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    int newWidth = this->width() / 3;
    widgetsScrollArea->setFixedWidth(newWidth);
}

void DetailedWeatherPage::addButtonClicked()
{
    emit locationSaved(this->data);
    this->addToSavedLocations->setVisible(false);
    Settings::instance().savedLocations().push_back(this->data->location());
}

void DetailedWeatherPage::homeButtonClicked()
{
    if(selectedWidget){
        selectedWidget->resetHighlight();
    }

    selectedWidget = nullptr;
}

void DetailedWeatherPage::highlightWidget()
{
    if(selectedWidget){
        selectedWidget->resetHighlight();
    }

    auto newSelectedWidget = std::find_if(m_widgets.begin(), m_widgets.end(), [this](const auto* widget) {
        return widget->data->location() == this->data->location();
    });

    if (newSelectedWidget != m_widgets.end()) {
        selectedWidget = *newSelectedWidget;
        widgetsScrollArea->ensureWidgetVisible(selectedWidget);
        selectedWidget->setHighlight();
    }
}
