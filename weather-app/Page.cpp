#include "Page.h"
#include "MainWindow.h"

Page::Page(QWidget *parent)
    : QWidget{parent}
    , mainWindow(qobject_cast<MainWindow*>(this->parent()))
{

}
