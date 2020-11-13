#include "dialogwidget.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>

#include <QDebug>


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
}

DialogWidget::~DialogWidget()
{
    if (isInsertDataWidgetOpened){
        delete insertDataWidget;
    }
    if (isDisplayDataWidgetOpened){
        delete displayDataWidget;
    }
}

void DialogWidget::insertPushButtonClicked(){
    this->hide();    // Скрываем основное окно

    insertDataWidget = new InsertDataWidget();
    //Подключение отображения окна выбора действий при закрытии ввода/вывода по кнопке
    connect(insertDataWidget, SIGNAL(firstWindow()), this, SLOT(backFromInsertDataWidget()));

    insertDataWidget->show();
}

void DialogWidget::displayPushButtonClicked(){
    this->hide();    // Скрываем основное окно

    displayDataWidget = new DisplayDataWidget();
    connect(displayDataWidget, SIGNAL(firstWindow()), this, SLOT(backFromDisplayDataWidget()));

    displayDataWidget->show();
}

void DialogWidget::backFromInsertDataWidget(){
    insertDataWidget->deleteLater();
    isInsertDataWidgetOpened = false;
    this->show();
}

void DialogWidget::backFromDisplayDataWidget(){
    displayDataWidget->deleteLater();
    isDisplayDataWidgetOpened = false;
    this->show();
}
