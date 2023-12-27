#ifndef ERRORWIDGET_H
#define ERRORWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class ErrorWidget : public QWidget
{
public:
    explicit ErrorWidget(const QString &errorMessage, QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
    QLabel *errorMessageLabel;

};

#endif // ERRORWIDGET_H
