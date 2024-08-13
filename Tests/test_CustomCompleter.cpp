#include "CustomCompleter.h"
#include "catch.hpp"
#include <QKeyEvent>
#include <QLineEdit>
#include <QTest>

// zato sto je CustomCompleter protected pa moramo da se dovijemo pomocu CustomCompleterTestHelper-a koji ga nasledjuje
class CustomCompleterTestHelper : public CustomCompleter
{
public:
  CustomCompleterTestHelper(QLineEdit *lineEdit) : CustomCompleter(lineEdit)
  {
  }
  using CustomCompleter::eventFilter;
};

TEST_CASE("CustomCompleter event filter")
{
  QLineEdit					lineEdit;
  CustomCompleterTestHelper completer(&lineEdit);

  lineEdit.installEventFilter(&completer);

  SECTION("Filter out Up key event")
  {
	QKeyEvent upKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
	bool	  eventFiltered = QTest::qWaitFor([&]() { return completer.eventFilter(&lineEdit, &upKeyEvent); });
	REQUIRE(eventFiltered);
	REQUIRE(upKeyEvent.isAccepted() == true);
  }

  SECTION("Filter out Down key event")
  {
	QKeyEvent downKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
	bool	  eventFiltered = QTest::qWaitFor([&]() { return completer.eventFilter(&lineEdit, &downKeyEvent); });
	REQUIRE(eventFiltered);
	REQUIRE(downKeyEvent.isAccepted() == true);
  }
}
