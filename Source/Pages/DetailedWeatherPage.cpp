#include "DetailedWeatherPage.h"

#include "MainWindow.h"
#include "WeatherData.h"
#include "ErrorWidget.h"
#include "WeatherWidget.h"
#include "GeoLocationData.h"
#include "Settings.h"

#include <iostream>
#include <QStackedWidget>
#include <QTimer>

DetailedWeatherPage::DetailedWeatherPage(QWidget *parent)
    : Page{parent}
    , mainLayout(new QHBoxLayout(this))
    , widgetsScrollArea(new QScrollArea())
    , weatherScrollArea(new QScrollArea())
    , widgetsScrollAreaContents(new QWidget())
    , weatherScrollAreaContents(new QWidget())
    , widgetsLayout(new QGridLayout())
    , weatherLayout(new QGridLayout())
    , returnToHomePage(new QPushButton("< Home"))
    , horizontalSpacer(new QSpacerItem(spacerWidth, 0, QSizePolicy::Expanding, QSizePolicy::Minimum))
    , addToSavedLocations(new QPushButton("Add"))
    , selectedWidget(nullptr)
{
    widgetsScrollAreaContents->setLayout(widgetsLayout);
    widgetsLayout->setAlignment(Qt::AlignTop);

    widgetsScrollArea->setWidget(widgetsScrollAreaContents);
    widgetsScrollArea->setWidgetResizable(true);
    widgetsScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    weatherLayout->addWidget(returnToHomePage, 0, 0);
    weatherLayout->addItem(horizontalSpacer, 0, 1);
    weatherLayout->addWidget(addToSavedLocations, 0, 2);
    weatherLayout->setAlignment(Qt::AlignTop);

    weatherScrollAreaContents->setLayout(weatherLayout);
    weatherScrollArea->setWidget(weatherScrollAreaContents);
    weatherScrollArea->setWidgetResizable(true);

    mainLayout->addWidget(widgetsScrollArea);
    mainLayout->addWidget(weatherScrollArea);

    connect(returnToHomePage, &QPushButton::clicked, this->mainWindow, &MainWindow::showHomePage);
    connect(returnToHomePage, &QPushButton::clicked, this, &DetailedWeatherPage::homeButtonClicked);
    connect(addToSavedLocations, &QPushButton::clicked, this, &DetailedWeatherPage::addButtonClicked);
    connect(this, &DetailedWeatherPage::locationSaved, this->mainWindow, &MainWindow::getLocationData);
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

void DetailedWeatherPage::addErrorWidget(const QString &errMsg)
{
    auto *widget = new ErrorWidget(errMsg);
    widgetsLayout->addWidget(widget, 0, 0, 1, 1);
    m_widgets.emplaceBack(widget);
}

void DetailedWeatherPage::setData(const GeoLocationData &data) // todo sharedptr
{
    widgetsScrollArea->verticalScrollBar()->setValue(0);
    this->data = data;
    // test
    std::cout << data.getRenamedPlace().toStdString() << " "
              << data.getCoordinates().toString().toStdString() << std::endl;

    bool showAddbutton = data.getRenamedPlace() != "My location" &&
                         Settings::instance().savedLocations().indexOf(data) == -1;

    showAddbutton ? this->addToSavedLocations->setVisible(true)
                  : this->addToSavedLocations->setVisible(false);

    highlightWidget();
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
    Settings::instance().savedLocations().push_back(this->data);
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

    auto newSelectedWidget = std::find_if(m_widgets.begin(), m_widgets.end(), [this](const auto* element) {
        const WeatherWidget* widget = dynamic_cast<const WeatherWidget*>(element); // Check if it's not an ErrorWidget
        return (widget != nullptr ? widget->data->location() == this->data : false);
    });

    if (newSelectedWidget != m_widgets.end()) {
        auto newSelectedWeatherWidget = dynamic_cast<WeatherWidget*>(*newSelectedWidget);
        selectedWidget = newSelectedWeatherWidget;
        widgetsScrollArea->ensureWidgetVisible(selectedWidget);
        selectedWidget->setHighlight();
    }
}
