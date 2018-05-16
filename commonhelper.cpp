#include "commonhelper.h"
int clothesCnt = 0;
void CommonHelper::setStyle(const QString &style) {
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}
