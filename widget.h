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


private:
    Ui::Widget *ui;
    TitleBar *titleBar;

public:
    int countFlag(QPoint p, int row);
    void setCursorType(int flag);
    int countRow(QPoint p);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    bool _isleftpressed;
    int _curpos;
    QPoint _plast;
};

#endif // WIDGET_H
