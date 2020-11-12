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
private slots:
    void insertPushButtonClicked();
    void displayPushButtonClicked();
};
#endif // WIDGET_H
