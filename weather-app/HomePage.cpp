#include "HomePage.h"

#include "WeatherData.h"
#include "WeatherWidget.h"
#include "MainWindow.h"

HomePage::HomePage(MainWindow *mainWindow, QWidget *parent)
    : QWidget{parent},
    m_mainWindow(mainWindow),
    mainLayout(new QVBoxLayout(this)),
    searchBar(new QLineEdit()),
    scrollArea(new QScrollArea()),
    scrollLayout(new QHBoxLayout()),
    scrollAreaContents(new QWidget()), // Container widget for the scroll area
    leftWidget(new QWidget()),
    rightWidget(new QWidget()),
    leftVBox(new QVBoxLayout()),
    rightVBox(new QVBoxLayout())
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

void HomePage::addNewWidget(WeatherData* data)
{

    bool inserttoLeft = leftWidget->property("inserttoLeft").toBool();

    if(inserttoLeft){
        WeatherWidget* tile = new WeatherWidget(data, leftWidget);
        connect(tile, &WeatherWidget::clicked, m_mainWindow, &MainWindow::onWeatherWidgetClicked);

        tile->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        this->m_widgets.push_back(tile);

        leftVBox->addWidget(tile);
    }
    else {
        WeatherWidget* tile = new WeatherWidget(data, rightWidget);
        connect(tile, &WeatherWidget::clicked, m_mainWindow, &MainWindow::onWeatherWidgetClicked);

        tile->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        this->m_widgets.push_back(tile);

        rightVBox->addWidget(tile);
    }
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

    for(auto widget : m_widgets){
        delete widget;
    }
}

