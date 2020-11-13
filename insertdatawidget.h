#ifndef INSERTDATAWIDGET_H
#define INSERTDATAWIDGET_H

#include <QWidget>

class QPushButton;

class InsertDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InsertDataWidget(QWidget *parent = nullptr);
    //~InsertDataWidget();
private:
    QPushButton * closePushButton;
    std::vector<int> A_temp;

    QStringList readEthnicGroups();
    //void resetToDefault();//Устанавливает значения всех элементов в начальное (например, пустое) состояние



signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    void closePushButtonClicked();
};

#endif // INSERTDATAWIDGET_H
