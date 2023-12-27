#include "ErrorWidget.h"

ErrorWidget::ErrorWidget(const QString &errorMessage, QWidget *parent)
    : QWidget{parent}
    , mainLayout(new QVBoxLayout(this))
    , errorMessageLabel(new QLabel(errorMessage, this))
{
    mainLayout->addWidget(errorMessageLabel);
    errorMessageLabel->setWordWrap(true);
    this->setLayout(mainLayout);
}
