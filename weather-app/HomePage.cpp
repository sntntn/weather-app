#include "HomePage.h"

#include "MainWindow.h"
#include "WeatherData.h"
#include "WeatherWidget.h"

#include <QShortcut>
#include <QCompleter>
#include <QStringListModel>

HomePage::HomePage(QWidget *parent)
    : Page{parent}
    , mainLayout(new QVBoxLayout(this))
    , searchBar(new QLineEdit())
    , scrollArea(new QScrollArea())
    , scrollLayout(new QHBoxLayout())
    , scrollAreaContents(new QWidget())
    , leftWidget(new QWidget())
    , rightWidget(new QWidget())
    , leftVBox(new QVBoxLayout())
    , rightVBox(new QVBoxLayout())
    , completer(new CustomCompleter(this))
    , debounceTimer(new QTimer(this))
{
    searchBar->setPlaceholderText("Enter location...");
    searchBar->setCompleter(completer);

    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    debounceTimer->setInterval(timerInterval);
    debounceTimer->setSingleShot(true);

    scrollLayout->setContentsMargins(leftMargin, topMargin, rightMargin, bottomMargin);
    scrollAreaContents->setLayout(scrollLayout);
    scrollArea->setWidget(scrollAreaContents);
    scrollArea->setWidgetResizable(true);

    mainLayout->addWidget(searchBar);
    mainLayout->addWidget(scrollArea);

    leftVBox->setAlignment(Qt::AlignTop);
    rightVBox->setAlignment(Qt::AlignTop);

    leftWidget->setLayout(leftVBox);
    rightWidget->setLayout(rightVBox);

    leftWidget->setProperty("inserttoLeft", true);

    scrollLayout->addWidget(leftWidget);
    scrollLayout->addWidget(rightWidget);

    styleSheetsSetup();

    connect(&geocodingApi, &GeocodingAPI::geocodingDataUpdated, this, &HomePage::updateCompleter);
    connect(completer, QOverload<const QString&>::of(&QCompleter::activated), this, &HomePage::onCompletionActivated);
    connect(searchBar, &QLineEdit::textChanged, this, [this]() { debounceTimer->start(); });
    connect(debounceTimer, &QTimer::timeout, this, &HomePage::onSearchBarTextChanged);
//    connect(searchBar, &QLineEdit::textChanged, this, &HomePage::onSearchBarTextChanged);
    connect(this, &HomePage::searchBarPressed, &geocodingApi, &GeocodingAPI::testCityFunction);
    connect(this, &HomePage::locationObjectSelected, mainWindow, &MainWindow::showDetailedWeatherPage);
}

void HomePage::addNewWidget(const QSharedPointer<Data> &data)
{
    auto *widget = new WeatherWidget(qSharedPointerCast<WeatherData>(data), scrollAreaContents);
    m_widgets.push_back(widget);

    connect(widget, &WeatherWidget::clicked, this->mainWindow, &MainWindow::showDetailedWeatherPage);

    bool inserttoLeft = leftWidget->property("inserttoLeft").toBool();
    inserttoLeft ? leftVBox->addWidget(widget) : rightVBox->addWidget(widget);

    widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    leftWidget->setProperty("inserttoLeft", !inserttoLeft);
}

void HomePage::onSearchBarTextChanged()
{
    completer->complete();
    emit searchBarPressed(searchBar->text());
    //completer->setCompletionPrefix(text);
    completer->complete(); // todo?
}

void HomePage::updateCompleter(const QList<GeoLocationData>& locations)
{
    this->locations = locations;
    QStringList places;
    qDebug()<<"----------------------------------"<< locations.size();
    for (const auto& location : locations) {
        //qDebug() << "Selected Place:" << location.getPlace() << "Latitude:" << location.getCoordinates().latitude() << "Longitude:" << location.getCoordinates().longitude();
        places.append(location.getPlace());
    }

    completer->setModel(new QStringListModel(places, completer)); // todo leak
    completer->complete();
}

void HomePage::onCompletionActivated(const QString& text)
{
    for (const auto& location : locations) {
        if (location.getPlace() == text) {
            emit locationObjectSelected(location);
            qDebug() << "------------emitovano----------------";
            break;
        }
    }
}

void HomePage::styleSheetsSetup()
{
    searchBar->setStyleSheet(
        "QLineEdit {"
        "    border: 3px solid gray;"
        "    border-radius: 4px;"
        "    padding: 0 8px;"
        "    background-color: rgb(28, 28, 28);"
        "    selection-background-color: darkgray;"
        "    color: white;"
        "}"
        "QLineEdit:focus {"
        "    border-color: rgb(28, 28, 28);"
        "    background-color: rgb(40, 40, 40);"
        "}"
        );

    scrollArea->setStyleSheet(
        "QScrollBar:vertical {"
        "    width: 7px;"
        "    border-radius: 30px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: gray;"
        "    min-height: 20px;"
        "    border-radius: 30px;"
        "}"
        );
}
