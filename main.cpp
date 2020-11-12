#include "dialogwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogWidget w;
    w.resize(370,100);
    w.show();
    return a.exec();
}
