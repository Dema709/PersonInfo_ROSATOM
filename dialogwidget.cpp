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

    QString insertText, displayText;

#ifdef __ANDROID__
    insertText = "Ввод\n"
                 "новых\n"
                 "данных";
    displayText = "Вывод\n"
                  "хранящихся\n"
                  "данных";
#else
    insertText = "Ввод\n"
                 "новых данных";
    displayText = "Вывод\n"
                  "хранящихся данных";
#endif

    QPushButton * insertPushButton = new QPushButton(insertText);
    hLayout->addWidget(insertPushButton);
    QPushButton * displayPushButton = new QPushButton(displayText);
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
        insertDataWidget->close();
    }
    if (isDisplayDataWidgetOpened){
        displayDataWidget->close();
    }
}

void DialogWidget::insertPushButtonClicked(){
    this->hide();    // Скрываем основное окно

    insertDataWidget = new InsertDataWidget();
    //Подключение отображения окна выбора действий при закрытии ввода/вывода по кнопке
    connect(insertDataWidget, SIGNAL(firstWindow()), this, SLOT(backFromInsertDataWidget()));
    isInsertDataWidgetOpened = true;
    insertDataWidget->show();
}

void DialogWidget::displayPushButtonClicked(){
    this->hide();    // Скрываем основное окно

    displayDataWidget = new DisplayDataWidget();
    connect(displayDataWidget, SIGNAL(firstWindow()), this, SLOT(backFromDisplayDataWidget()));
    isDisplayDataWidgetOpened = true;
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
