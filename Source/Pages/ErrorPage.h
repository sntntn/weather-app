#ifndef ERRORPAGE_H
#define ERRORPAGE_H

#include "Page.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>

class ErrorPage : public Page
{
  Q_OBJECT

public:
  ErrorPage(QWidget *parent = nullptr);
  ~ErrorPage() override = default;

  public slots:
  void setErrMsg(const QString &errMsg);

  // todo widgets scroll area like in DetailedWeatherPage
  void addNewWidget(const QSharedPointer<WeatherData> /*data*/) override {}
  void addErrorWidget(const QString & /*errMsg*/) override {}

  private:
  QVBoxLayout *mainLayout;
  QHBoxLayout *upperLayout;
  QLabel	  *errorLabel;
  QPushButton *homeButton;
};

#endif // ERRORPAGE_H
