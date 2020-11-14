#include "temptestwidget.h"
#include <QHBoxLayout>
#include <QPushButton>

tempTestWidget::tempTestWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout * l = new QHBoxLayout(this);
    dialogWidget = new DialogWidget();
    l->addWidget(dialogWidget);
    QPushButton * pb = new QPushButton("push to delete");
    l->addWidget(pb);
    connect(pb, SIGNAL(clicked()), this, SLOT(deleteDialogWidget()));
}

void tempTestWidget::deleteDialogWidget(){
    delete dialogWidget;
    //dialogWidget->deleteLater();
}
