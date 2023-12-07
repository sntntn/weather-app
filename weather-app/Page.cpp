#include "Page.h"
#include "MainWindow.h"
#include "WeatherWidget.h"

Page::Page(QWidget *parent)
    : QWidget{parent}
    , mainWindow(qobject_cast<MainWindow*>(this->parent()))
{ }

void Page::deleteWidgets()
{
    for(WeatherWidget *widget : m_widgets){
        delete widget;
        widget = nullptr;
    }

    m_widgets.clear();
}
