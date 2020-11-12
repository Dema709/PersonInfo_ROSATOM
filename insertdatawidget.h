#ifndef INSERTDATAWIDGET_H
#define INSERTDATAWIDGET_H

#include <QWidget>

class InsertDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InsertDataWidget(QWidget *parent = nullptr);

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    void closePushButtonClicked();
};

#endif // INSERTDATAWIDGET_H
