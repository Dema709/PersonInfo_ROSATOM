#include "dialogwidget.h"

#include <QApplication>

#include "test_runner.h"

int main(int argc, char *argv[])
{
    //По идее, в релизе программы тесты уже не нужны
    //И в нём объявляется QT_NO_DEBUG
    //Ну или вообще удаляются файлы/подключения тестов (убрать лишний вес)
    #ifndef QT_NO_DEBUG
    {
        TestRunner runner;
        RUN_TEST(runner, Test_Person_checkName);
        RUN_TEST(runner, Test_Person_checkBody);
        RUN_TEST(runner, Test_Person_checkEthnicGroup);
        RUN_TEST(runner, Test_Person_checkDates);
    }
    #endif

    QApplication a(argc, argv);
    DialogWidget w;
    w.resize(370,100);
    w.show();
    return a.exec();
}
