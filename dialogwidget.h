#ifndef WIDGET_H
#define WIDGET_H

#include "insertdatawidget.h"
#include "displaydatawidget.h"

#include <QWidget>

class DialogWidget : public QWidget
{
    Q_OBJECT

public:
    DialogWidget(QWidget *parent = nullptr);
    ~DialogWidget();
private:
    InsertDataWidget *insertDataWidget;
    DisplayDataWidget * displayDataWidget;
    bool isInsertDataWidgetOpened = false;
    bool isDisplayDataWidgetOpened = false;
private slots:
    void insertPushButtonClicked();
    void displayPushButtonClicked();
    void backFromInsertDataWidget();//Как слот - публичный, как функция - приватная. Если бы не эта фича,
    void backFromDisplayDataWidget();//надо было бы объявить перед их как public slots
};
#endif // WIDGET_H
