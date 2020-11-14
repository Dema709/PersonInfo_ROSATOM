#ifndef DISPLAYDATAWIDGET_H
#define DISPLAYDATAWIDGET_H

#include <QWidget>

class DisplayDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayDataWidget(QWidget *parent = nullptr);
private:
    void closeEvent(QCloseEvent*);

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    //void closePushButtonClicked();
};

#endif // DISPLAYDATAWIDGET_H
