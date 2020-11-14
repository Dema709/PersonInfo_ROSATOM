#include "displaydatawidget.h"

#include <QPushButton>
#include <QDebug>

DisplayDataWidget::DisplayDataWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Информация о человеке: вывод данных");//Название окна

    QPushButton * closePushButton = new QPushButton("Вернуться к выбору действий", this);
    connect(closePushButton, &QPushButton::clicked, this, &DisplayDataWidget::close);


}

void DisplayDataWidget::closeEvent(QCloseEvent*){
    qDebug()<<"DisplayDataWidget::closeEvent";
    emit firstWindow();
}
