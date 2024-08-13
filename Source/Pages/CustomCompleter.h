#ifndef CUSTOMCOMPLETER_H
#define CUSTOMCOMPLETER_H

#include <QCompleter>
#include <QKeyEvent>

class CustomCompleter : public QCompleter
{
  Q_OBJECT
public:
  CustomCompleter(QObject *parent = nullptr);

protected:
  bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // CUSTOMCOMPLETER_H
