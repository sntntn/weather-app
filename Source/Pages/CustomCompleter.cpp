#include "CustomCompleter.h"

CustomCompleter::CustomCompleter(QObject *parent) : QCompleter(parent)
{
}

auto CustomCompleter::eventFilter(QObject *obj, QEvent *event) -> bool
{
  if (event->type() == QEvent::KeyPress)
  {
	auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
	if (keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down)
	{
	  // Blokiraj strelice gore i dole
	  return true;
	}
  }

  return QCompleter::eventFilter(obj, event);
}
