#include "customcompleter.h"

CustomCompleter::CustomCompleter(QObject *parent) : QCompleter(parent) {}

bool CustomCompleter::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down) {
            // Blokiraj strelice gore i dole
            return true;
        }
    }

    return QCompleter::eventFilter(obj, event);
}
