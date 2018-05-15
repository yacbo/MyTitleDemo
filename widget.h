#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "titlebar.h"
#include <QVBoxLayout>
#include <QResizeEvent>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    void resizeEvent(QResizeEvent *event);
    static void setStyle(const QString &style);

private:
    Ui::Widget *ui;
    TitleBar *titleBar;
};

#endif // WIDGET_H
