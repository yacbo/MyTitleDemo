#include "titlebar.h"
#include <QStyle>
#include <QHBoxLayout>
#include <QDebug>
#include <QListView>
#include "commonhelper.h"
/*************************** 构造函数 ***************************/
TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    // 不继承父组件的背景色
    //setAutoFillBackground(true);
    // 使用 Highlight 作为背景色
    //setBackgroundRole(QPalette::Highlight);

    //最大化按钮设置图标
    QPixmap pixMap = this->style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
    maxButton = new QPushButton(this);
    maxButton->setIcon(pixMap);

    //最小化按钮设置图标
    pixMap = this->style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    minButton = new QPushButton(this);
    minButton->setIcon(pixMap);

    //关闭按钮设置图标
    pixMap = this->style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    closeButton = new QPushButton(this);
    closeButton->setIcon(pixMap);

    //换肤按钮
    pixMap.load(":/pic/color3.png");
    //pixMap = this->style()->standardPixmap(QStyle::SP_DialogHelpButton);
    skinButton = new QPushButton(this);
    skinButton->setIcon(pixMap);

    //设置标签
    imgLabel = new QLabel(this);
    titleLabel = new QLabel(this);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    //titleLabel->setStyleSheet("color:white");
    titleLabel->setStyleSheet("QLabel {color: white;font-size: 25px;font-family:华文新魏}");
    //设置控件大小
    imgLabel->setFixedSize(CONTROLWIDTH, CONTROLWIDTH);
    imgLabel->setScaledContents(true);

    //设置控件大小
    minButton->setFixedSize(CONTROLWIDTH, CONTROLWIDTH);
    maxButton->setFixedSize(CONTROLWIDTH, CONTROLWIDTH);
    closeButton->setFixedSize(CONTROLWIDTH, CONTROLWIDTH);
    skinButton->setFixedSize(CONTROLWIDTH, CONTROLWIDTH);

    //设置布局
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addWidget(imgLabel);
    hBoxLayout->addSpacing(5);
    hBoxLayout->addWidget(titleLabel);
    hBoxLayout->addWidget(skinButton);
    hBoxLayout->addWidget(minButton);
    hBoxLayout->addWidget(maxButton);
    hBoxLayout->addWidget(closeButton);
    hBoxLayout->setSpacing(0);
    hBoxLayout->setContentsMargins(5, 0, 5, 0);
    this->setLayout(hBoxLayout);

    //设置背景色
    QPalette paletteColor(palette());
    paletteColor.setColor(QPalette::Background, QColor(200, 200, 200));
    this->setAutoFillBackground(true);
    this->setPalette(paletteColor);

//    this->setAutoFillBackground(true);
//    QPalette palette;
//    QPixmap pixmap(":/pic/qianlan1.png");
//    palette.setBrush(QPalette::Window, QBrush(pixmap));
//    this->setPalette(palette);


    //重置窗口大小
    this->resize(parent->width(), TITLEBARHEIGHT);

    //设置父类窗口
    parentWidget = parent;

    this->initValue();
}

/*************************** 设置标题 ***************************/
void TitleBar::setWindowTitle(const QString &title)
{
    titleLabel->setText(title);
}

/*************************** 设置图标 ***************************/
void TitleBar::setWindowIcon(const QString &icon)
{
    imgLabel->setPixmap(QPixmap(icon));
}

/*************************** 设置按钮 ***************************/
void TitleBar::subWindowButton(const int &type)
{
    if(type == TITLEBAR::MINWIDGET)
    {
        SAFEDELETE(minButton);
    }
    else if(type == TITLEBAR::MAXWIDGET)
    {
        SAFEDELETE(maxButton);
    }
    else if(type == TITLEBAR::MAXMINWIDGET)
    {
        SAFEDELETE(minButton);
        SAFEDELETE(maxButton);
    }
}

/*************************** 初始化 ***************************/
void TitleBar::initValue()
{
    //设置样式表
    closeButton->setStyleSheet("QPushButton{background-color:transparent;}""QPushButton:hover{background-color:rgb(169, 169, 169);}");
    closeButton->setToolTip("关闭");
    minButton->setStyleSheet("QPushButton{background-color:transparent;}""QPushButton:hover{background-color:rgb(169, 169, 169);}");
    minButton->setToolTip("最小化");
    maxButton->setStyleSheet("QPushButton{background-color:transparent;}""QPushButton:hover{background-color:rgb(169, 169, 169);}");
    maxButton->setToolTip("最大化");
    imgLabel->setStyleSheet("background-color:transparent;");
    skinButton->setStyleSheet("QPushButton{background-color:transparent;}""QPushButton:hover{background-color:rgb(169, 169, 169);}");
    skinButton->setToolTip("换肤");


    //连接信号与槽
    connect(minButton, SIGNAL(clicked(bool)), this, SLOT(showMin()));
    connect(maxButton, SIGNAL(clicked(bool)), this, SLOT(showMax()));
    connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(showClose()));
    connect(skinButton, SIGNAL(clicked(bool)), this, SLOT(changeSkin()));

    //按钮点击标志位
    mousePress = false;

    //将该窗口添加到父类窗口中
    QVBoxLayout *vBoxLayout = new QVBoxLayout(parentWidget);

    vBoxLayout->addWidget(this);
    vBoxLayout->addStretch(0);
    vBoxLayout->setSpacing(0);
    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    parentWidget->setLayout(vBoxLayout);
}

/*************************** 最大化 ***************************/
void TitleBar::showMax()
{
    static int count = 0;
    if(count % 2 == 0)
    {
        QPixmap normalPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
        maxButton->setIcon(normalPix);
        maxButton->setToolTip("还原");
        parentWidget->showMaximized();
    }
    else
    {
        QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
        maxButton->setIcon(maxPix);
        maxButton->setToolTip("最大化");
        parentWidget->showNormal();
    }
    count ++;
}

/*************************** 最小化 ***************************/
void TitleBar::showMin()
{
    parentWidget->showMinimized();
}

/*************************** 关闭 ***************************/
void TitleBar::showClose()
{
    parentWidget->close();
}

/*************************** 鼠标点击 ***************************/
void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mousePress = true;
    }
    movePoint = event->globalPos() - parentWidget->pos();
    QWidget::mousePressEvent(event);
}

/************************** 鼠标释放 ***************************/
void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    mousePress = false;
    QWidget::mouseReleaseEvent(event);
}

/************************** 鼠标移动 **************************/
void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePress)
    {
        QPoint movePos = event->globalPos();
        parentWidget->move(movePos - movePoint);
    }
    QWidget::mouseMoveEvent(event);
}

/************************** 鼠标双击 **************************/
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        showMax();
    }
}

//更换皮肤
void TitleBar::changeSkin()
{
    static int clothesCnt = 0;
    switch (clothesCnt) {
    case 0:
        CommonHelper::setStyle(":/qss/white.qss");
        clothesCnt = 1;
        break;
    case 1:
        CommonHelper::setStyle(":/qss/black.qss");
        clothesCnt = 2;
        break;
    case 2:
        CommonHelper::setStyle(":/qss/blank.qss");
        clothesCnt = 0;
        break;
    default:
        break;
    }

}

void TitleBar::hideSkinButton()
{
    skinButton->hide();
}
