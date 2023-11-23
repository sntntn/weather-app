#include "HomePage.h"

#include "WeatherData.h"
#include "WeatherWidget.h"

HomePage::HomePage(QWidget *parent)
    : QWidget{parent},
    mainLayout(new QVBoxLayout(this)),
    searchBar(new QLineEdit()),
    scrollArea(new QScrollArea()),
    scrollLayout(new QHBoxLayout()),
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

    QWidget *scrollAreaContents = new QWidget(); // Container widget for the scroll area
    scrollAreaContents->setLayout(scrollLayout);
    scrollArea->setWidget(scrollAreaContents);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(
                  "QScrollBar:vertical {"
                  "    width: 7px;"
                  "    border-radius: 30px;"  // Rounded corners for the scroll bar
                  "}"
                  "QScrollBar::handle:vertical {"
                  "    background: gray;"
                  "    min-height: 20px;"
                  "    border-radius: 30px;"  // Rounded corners for the handle
        "}");

    mainLayout->addWidget(scrollArea); // Add scroll area to the main layout

    // Setting layouts for left and right widgets
    leftVBox->setAlignment(Qt::AlignTop);
    leftWidget->setLayout(leftVBox);
    leftWidget->setProperty("inserttoLeft", true);

    rightVBox->setAlignment(Qt::AlignTop);
    rightWidget->setLayout(rightVBox);

    // Adding widgets to the horizontal layout inside scroll area
    scrollLayout->addWidget(leftWidget);
    scrollLayout->addWidget(rightWidget);
}

void HomePage::addNewWidget(WeatherData* data)
{

    bool inserttoLeft = leftWidget->property("inserttoLeft").toBool();

    if(inserttoLeft){
        WeatherWidget* tile = new WeatherWidget(leftWidget, data);
        tile->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        this->m_widgets.push_back(tile);

        leftVBox->addWidget(tile);
    }
    else {
        WeatherWidget* tile = new WeatherWidget(rightWidget, data);
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

