#include "insertdatawidget.h"

#include <QPushButton>

InsertDataWidget::InsertDataWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Информация о человеке: ввод данных");//Название окна

    QPushButton * closePushButton = new QPushButton("Вернуться к выбору действий", this);
    connect(closePushButton, SIGNAL(clicked()),SLOT(closePushButtonClicked()));
}

void InsertDataWidget::closePushButtonClicked(){
    this->close();
    emit firstWindow();
}
