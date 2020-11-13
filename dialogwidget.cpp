#include "dialogwidget.h"

//#include "insertdatawidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>

#include <QDebug>

/*
//temp!!!!
#define DEBUG
#define _DEBUG
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
//endtemp!!!
*/

DialogWidget::DialogWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Информация о человеке: выбор действия");//Название окна
    QHBoxLayout * hLayout = new QHBoxLayout(this);
    QPushButton * insertPushButton = new QPushButton("Ввод\n"
                                                     "новых данных");
    hLayout->addWidget(insertPushButton);
    QPushButton * displayPushButton = new QPushButton("Вывод\n"
                                                      "хранящихся данных");
    hLayout->addWidget(displayPushButton);

    //Кнопки открытия виджетов ввода/вывода
    insertPushButton ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    displayPushButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    //Подключение кнопок на открытие других виджетов
    connect(insertPushButton, SIGNAL(clicked()),SLOT(insertPushButtonClicked()));
    connect(displayPushButton, SIGNAL(clicked()),SLOT(displayPushButtonClicked()));

    //insertDataWidget = new InsertDataWidget();
    displayDataWidget = new DisplayDataWidget();

    //Подключение отображения окна выбора действий при закрытии ввода/вывода по кнопке
    //connect(insertDataWidget, &InsertDataWidget::firstWindow, this, &DialogWidget::show);
    connect(displayDataWidget, &DisplayDataWidget::firstWindow, this, &DialogWidget::show);
}

DialogWidget::~DialogWidget()
{
    if (isInsertDataWidgetOpened){
        delete insertDataWidget;
    }
    delete displayDataWidget;
}

void DialogWidget::insertPushButtonClicked(){
    this->hide();    // Скрываем основное окно

    insertDataWidget = new InsertDataWidget();
    isInsertDataWidgetOpened = true;
    connect(insertDataWidget, SIGNAL(firstWindow()), this, SLOT(backFromInsertDataWidget()));

    insertDataWidget->show();
}

void DialogWidget::displayPushButtonClicked(){
    this->hide();    // Скрываем основное окно
    displayDataWidget->show();
}

void DialogWidget::backFromInsertDataWidget(){
    //connect(insertDataWidget, SIGNAL(firstWindow()), this, SLOT(backFromInsertDataWidget()));
    insertDataWidget->deleteLater();
    isInsertDataWidgetOpened = false;
    this->show();
}
/*
void DialogWidget::backFromDisplayDataWidget(){

}*/
