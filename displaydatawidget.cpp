#include "displaydatawidget.h"

#include <QPushButton>

DisplayDataWidget::DisplayDataWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Информация о человеке: вывод данных");//Название окна

    QPushButton * closePushButton = new QPushButton("Вернуться к выбору действий", this);
    connect(closePushButton, SIGNAL(clicked()),SLOT(closePushButtonClicked()));
}

void DisplayDataWidget::closePushButtonClicked(){
    this->close();
    emit firstWindow();
}
