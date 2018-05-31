#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QComboBox>
#include <QVBoxLayout>


#ifndef SAFEDELETE
#define SAFEDELETE(pointer) \
{ \
if(pointer) \
{ \
delete pointer; \
} \
pointer = NULL; \
}
#endif

namespace TITLEBAR
{
enum WIDGETBUTTONTYPE
{
MAXWIDGET,
MINWIDGET,
MAXMINWIDGET,
};
}

class TitleBar : public QWidget
{
Q_OBJECT
public:
explicit TitleBar(QWidget *parentWidget = 0);

void setWindowTitle(const QString &title); //设置标题
void setWindowIcon(const QString &icon); //设置图标
void subWindowButton(const int &type); //设置按钮

const static int TITLEBARHEIGHT = 40; //标题栏高度
const static int CONTROLWIDTH = 30; //控件宽度

public slots:
    void showMax(); //最大化窗口
    void showMin(); //最小化窗口
    void showClose(); //关闭窗口
    void changeSkin();

public:
    void initValue(); //初始化值
    void mousePressEvent(QMouseEvent * event); //鼠标点击事件
    void mouseReleaseEvent(QMouseEvent * event); //鼠标释放事件
    void mouseMoveEvent(QMouseEvent * event); //鼠标移动事件
    void mouseDoubleClickEvent(QMouseEvent *event); //双击鼠标事件

private:
    bool mousePress; //按钮点击标志位
    QPoint movePoint; //鼠标移动
    QPushButton *maxButton; //最大化按钮
    QPushButton *minButton; //最小化按钮
    QPushButton *closeButton; //关闭按钮
    QPushButton *skinButton; //换肤按钮
    QLabel *imgLabel; //图片框
    QWidget *parentWidget; //父窗口
    QLabel *titleLabel; //标题名

    QColor m_ColorL;         // 标题栏渐变色
    QColor m_ColorR;         // 标题栏渐变色
    QPoint oldPos;
    bool mouseDown;
    bool left, right, bottom;

    // 标题栏背景色;
    int m_colorR;
    int m_colorG;
    int m_colorB;

public:
    void hideSkinButton();
};

#endif // TITLEBAR_H
