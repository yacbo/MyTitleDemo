#include "widget.h"
#include "ui_widget.h"
#include "commonhelper.h"
#include <QPainter>
#include <windows.h>
#include <WinUser.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <objidl.h>
#include <gdiplus.h>

#define MARGIN 5
Widget::Widget(QWidget *parent) :QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    QIcon icon(":/pic/123.png");
    setWindowIcon(icon);
    setWindowTitle(QStringLiteral("日月星辰"));
    //this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //this->setWindowFlags(Qt::FramelessWindowHint);// 设置无边框
    //this-> setAttribute(Qt::WA_TranslucentBackground, true);// 背景透明

    CommonHelper::setStyle(":/qss/blank.qss");  //设置全局样式
    //this->setStyleSheet("QWidget{border: 5px solid rgb(50, 50, 50);}");

    titleBar = new TitleBar(this);   //标题栏是子窗口
    titleBar->setWindowIcon(":/pic/123.png");
    titleBar->setWindowTitle("日月星辰");

    //ui->verticalLayout_2->setSpacing(0);   //设置控件的边框
    ui->verticalLayout->setContentsMargins(MARGIN, 40, MARGIN, MARGIN);

    //构造
    this->setMouseTracking(true);
    _isleftpressed = false;
    _curpos = 0;//标记鼠标左击时的位置
    this->setMinimumSize(600, 400);//设置最小尺寸

}

Widget::~Widget()
{
    delete ui;
}

/************************ 改变事件 ************************/
void Widget::resizeEvent(QResizeEvent *event)
{
    titleBar->resize(this->width(), TitleBar::TITLEBARHEIGHT);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    QPoint leftTop(8,40);
    QPoint rightBottom(this->geometry().width()-8,this->geometry().height()-8);
    QRect rect(leftTop,rightBottom);
    if(rect.contains(event->pos()))
    {
        return;
    }
    if (event->button() == Qt::LeftButton)
    {
        this->_isleftpressed = true;
        QPoint temp = event->globalPos();
        _plast = temp;
        _curpos = countFlag(event->pos(), countRow(event->pos()));
        event->ignore();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (_isleftpressed)
        _isleftpressed = false;
    setCursor(Qt::ArrowCursor);
    event->ignore();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (windowState() != Qt::WindowFullScreen)
            setWindowState(Qt::WindowFullScreen);
        else setWindowState(Qt::WindowNoState);//恢复正常模式
    }
    event->ignore();
}

void Widget::mouseMoveEvent(QMouseEvent *event)//鼠标移动事件
{

    int poss = countFlag(event->pos(), countRow(event->pos()));
    setCursorType(poss);
    if (_isleftpressed)//是否左击
    {
        QPoint ptemp = event->globalPos();
        ptemp = ptemp - _plast;
        if (_curpos == 22)//移动窗口
        {
            ptemp = ptemp + pos();
            move(ptemp);
        }
        else
        {
            QRect wid = geometry();
            switch (_curpos)//改变窗口的大小
            {

            case 11:wid.setTopLeft(wid.topLeft() + ptemp); break;//左上角
            case 13:wid.setTopRight(wid.topRight() + ptemp); break;//右上角
            case 31:wid.setBottomLeft(wid.bottomLeft() + ptemp); break;//左下角
            case 33:wid.setBottomRight(wid.bottomRight() + ptemp); break;//右下角
            case 12:wid.setTop(wid.top() + ptemp.y()); break;//中上角
            case 21:wid.setLeft(wid.left() + ptemp.x()); break;//中左角
            case 23:wid.setRight(wid.right() + ptemp.x()); break;//中右角
            case 32:wid.setBottom(wid.bottom() + ptemp.y()); break;//中下角
            }
            setGeometry(wid);
        }

        _plast = event->globalPos();//更新位置
    }
    event->ignore();
}

int Widget::countFlag(QPoint p, int row)//计算鼠标在哪一列和哪一行
{
    if (p.y()<MARGIN)
        return 10 + row;
    else if (p.y()>this->height() - MARGIN)
        return 30 + row;
    else
        return 20 + row;
}

void Widget::setCursorType(int flag)//根据鼠标所在位置改变鼠标指针形状
{
    Qt::CursorShape cursor;
    switch (flag)
    {
    case 11:
    case 33:
        cursor = Qt::SizeFDiagCursor; break;
    case 13:
    case 31:
        cursor = Qt::SizeBDiagCursor; break;
    case 21:
    case 23:
        cursor = Qt::SizeHorCursor; break;
    case 12:
    case 32:
        cursor = Qt::SizeVerCursor; break;
    case 22:
        //cursor = Qt::OpenHandCursor; break;
        cursor = Qt::ArrowCursor; break;
    default:
        cursor = Qt::ArrowCursor; break;
        break;

    }
    setCursor(cursor);
}

int Widget::countRow(QPoint p)//计算在哪一列
{
    return (p.x()<MARGIN) ? 1 : (p.x()>(this->width() - MARGIN) ? 3 : 2);
}

void Widget::paintEvent(QPaintEvent*)//paintEvent函数由系统自动调用，用不着我们人为的去调用。
{
    // QPoint leftTop(MARGIN,40);
    // QPoint rightBottom(this->geometry().width()-8,this->geometry().height()-8);
    // QRect rect(leftTop,rightBottom);
    // QPainter painter(this);
    // painter.setPen(QPen(Qt::blue,1));//设置画笔形式
//     painter.drawLine(20,20,220,220);//画直线
//     painter.drawLine(20,220,220,20);
//     painter.drawEllipse(20,20,200,200);//画圆
    // painter.drawRect(rect);//画矩形

}
