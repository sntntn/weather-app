#include "HomePage.h"

#include "MainWindow.h"
#include "WeatherData.h"
#include "WeatherWidget.h"

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
{
    searchBar->setStyleSheet(
        "QLineEdit {"
        "    border: 3px solid gray;"
        "    border-radius: 4px;"
        "    padding: 0 8px;"
        "    background-color: rgb(28, 28, 28);"
        "    selection-background-color: darkgray;"
        "}"
        "QLineEdit:focus {"
        "    border-color: rgb(28, 28, 28);"
        "}"
        );
    searchBar->setPlaceholderText("Enter location...");
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
}

void HomePage::addNewWidget(const QSharedPointer<WeatherData> &data)
{
    auto *widget = new WeatherWidget(data, scrollAreaContents);
    m_widgets.push_back(widget);

    connect(widget, &WeatherWidget::clicked, this->mainWindow, &MainWindow::showDetailedWeatherPage);

    bool inserttoLeft = leftWidget->property("inserttoLeft").toBool();
    inserttoLeft ? leftVBox->addWidget(widget) : rightVBox->addWidget(widget);

    widget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    leftWidget->setProperty("inserttoLeft", !inserttoLeft);
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

