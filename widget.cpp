#include "widget.h"
#include "ui_widget.h"
#include "commonhelper.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    // 设置无边框
    this->setWindowFlags(Qt::FramelessWindowHint);

    // 背景透明
   //this-> setAttribute(Qt::WA_TranslucentBackground, true);

    titleBar = new TitleBar(this);
    titleBar->setWindowIcon("pic/123.png");
    titleBar->setWindowTitle("日月星辰");

    CommonHelper::setStyle("qss/white.qss");
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
