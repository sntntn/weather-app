#ifndef PAGE_H
#define PAGE_H

#include <QSharedPointer>
#include <QWidget>

class BasicWidget;
class MainWindow;
class WeatherData;

class Page : public QWidget
{
  Q_OBJECT

public:
    ~Page() override = default;

    [[nodiscard]] inline auto numWidgets() const -> int { return m_widgets.size(); }

public slots:
    virtual void addNewWidget(QSharedPointer<WeatherData> data) = 0;
    virtual void addErrorWidget(const QString &errMsg) = 0;
    void deleteWidgets();

protected:
  explicit Page(QWidget *parent = nullptr);

  QVector<BasicWidget *> m_widgets;
  MainWindow			*mainWindow;
};

#endif // PAGE_H
