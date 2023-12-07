#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSharedPointer>
#include <QCompleter>
#include <QTimer>
#include <QPushButton>
#include "Page.h"
#include "geocodingapi.h"
#include "Settings.h"
#include "GeoLocationData.h"
#include "customcompleter.h"

struct LocationData;
class WeatherWidget;
class WeatherData;
class MainWindow;

class HomePage : public Page
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage() = default;

signals:
    void searchBarPressed(const QString& location);
    void locationObjectSelected(const GeoLocationData& locationData);

public slots:
    void addNewWidget(const QSharedPointer<Data> &data) override;
    void onSearchBarTextChanged();

private:




private:
    static const int leftMargin = 25;
    static const int rightMargin = 25;
    static const int topMargin = 0;
    static const int bottomMargin = 0;
    static const int timerInterval = 300;

    QVBoxLayout *mainLayout;
    QHBoxLayout *upperLayout;
    QLineEdit *searchBar;
    QPushButton *settingsButton;
    QScrollArea *scrollArea;
    QHBoxLayout *scrollLayout;
    QWidget *scrollAreaContents;
    QWidget *leftWidget;
    QWidget *rightWidget;
    QVBoxLayout *leftVBox;
    QVBoxLayout *rightVBox;
    CustomCompleter *completer;
    QTimer *debounceTimer;
    QPixmap settingsPixmap;
    QIcon settingsIcon;

    QList<GeoLocationData> locations;   //strukturu uzimamo direktno

    void openSettingsDialog();
    void resetInsertToLeft();
    void updateCompleter(const QList<GeoLocationData>& locations);
    void onCompletionActivated(const QString& text);
    void styleSheetsSetup();

    QList<QString> getLocationNames();
    GeocodingAPI geocodingApi;
};

#endif // HOMEPAGE_H
