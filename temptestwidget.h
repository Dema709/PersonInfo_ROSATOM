#ifndef TEMPTESTWIDGET_H
#define TEMPTESTWIDGET_H

#include <QWidget>

#include "dialogwidget.h"

class tempTestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit tempTestWidget(QWidget *parent = nullptr);
private:
    DialogWidget * dialogWidget;
private slots:
    void deleteDialogWidget();
signals:

};

#endif // TEMPTESTWIDGET_H
