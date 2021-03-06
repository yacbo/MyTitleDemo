#include "widget.h"
#include "ui_widget.h"
#include "commonhelper.h"
#define MARGIN 5
Widget::Widget(QWidget *parent) :QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 设置无边框
    //this->setWindowFlags(Qt::FramelessWindowHint);
    // 背景透明
    //this-> setAttribute(Qt::WA_TranslucentBackground, true);
    CommonHelper::setStyle(":/qss/blank.qss");


    titleBar = new TitleBar(this);
    titleBar->setWindowIcon(":/pic/power.png");
    titleBar->setWindowTitle("日月星辰");
    ui->verticalLayout_2->setSpacing(0);   //设置控件的边框
    ui->verticalLayout_2->setContentsMargins(1, 40, 1, 3);

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
