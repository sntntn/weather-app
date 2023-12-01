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
    , completer(new QCompleter(this))
{
    //fiksirao sam boje jer u suprotnom vidljivost teksta zavisi od teme koja je ukljucena u Qt Creator-u
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
    searchBar->setPlaceholderText("Enter location...");
    searchBar->setCompleter(completer);
    mainLayout->addWidget(searchBar);

    int leftMargin = 25;
    int rightMargin = 25;
    int topMargin = 0;
    int bottomMargin = 0;
    scrollLayout->setContentsMargins(leftMargin, topMargin, rightMargin, bottomMargin);

    scrollAreaContents->setLayout(scrollLayout);
    scrollArea->setWidget(scrollAreaContents);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(
        "QScrollBar:vertical {"
        "    width: 7px;"
        "    border-radius: 30px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: gray;"
        "    min-height: 20px;"
        "    border-radius: 30px;"
        "}");

    mainLayout->addWidget(scrollArea);

    leftVBox->setAlignment(Qt::AlignTop);
    leftWidget->setLayout(leftVBox);
    leftWidget->setProperty("inserttoLeft", true);

    rightVBox->setAlignment(Qt::AlignTop);
    rightWidget->setLayout(rightVBox);

    scrollLayout->addWidget(leftWidget);
    scrollLayout->addWidget(rightWidget);

    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(shortcut, &QShortcut::activated, this, &HomePage::searchBarEnter);
    connect(&geocodingApi, &GeocodingAPI::geocodingDataUpdated, this, &HomePage::updateCompleter);
    connect(completer, QOverload<const QString&>::of(&QCompleter::activated), this, &HomePage::onCompletionActivated);


    connect(this, &HomePage::searchBarPressed, &geocodingApi, &GeocodingAPI::testCityFunction);
}

HomePage::~HomePage()
{
    delete mainLayout;
    delete searchBar;
    delete scrollArea;
    delete scrollLayout;
    delete leftWidget;
    delete rightWidget;
    delete leftVBox;
    delete rightVBox;

    for (auto *widget : m_widgets){
        delete widget;
    }
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

void HomePage::searchBarEnter() {
    QString location = searchBar->text();
    emit searchBarPressed(location);
    //completer->setCompletionPrefix(location);   //pocinje tek nakon unosa odredjenog broja karaktera
    completer->complete();      //prikazivanje padajuce liste odmah nakon unosa
}



void HomePage::updateCompleter(const QList<LocationData>& locations) {
    this->locations = locations;
    QStringList places;
    qDebug()<<"----------------------------------"<< locations.size();
    for (const auto& location : locations) {
        qDebug() << "Selected Place:" << location.place << "Latitude:" << location.latitude << "Longitude:" << location.longitude;
        places.append(location.place);
    }

    completer->setModel(new QStringListModel(places, completer));
    //qDebug() << "Updated completer with places:" << places;
}
void HomePage::onCompletionActivated(const QString& text) {
    for (const auto& location : locations) {
        if (location.place == text) {
            double latitude = location.latitude;
            double longitude = location.longitude;

            //TO DO -> ovde implementiram sta ce da se desi kada kliknemo predlog
            //qDebug() << "Selected Place:" << text << "Latitude:" << latitude << "Longitude:" << longitude;
            break;
        }
    }
}
