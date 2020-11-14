#include "dialogwidget.h"
#include "temptestwidget.h"//temp!!!!!!!!!!!!!!!!!!!!

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //tempTestWidget w;
    DialogWidget w;
    w.resize(370,100);
    w.show();
    return a.exec();
}
