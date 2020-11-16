#ifndef DISPLAYDATAWIDGET_H
#define DISPLAYDATAWIDGET_H

#include <QWidget>
//#include <QSql>
#include <QSqlRelationalTableModel>
#include <QTableView>

class DisplayDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayDataWidget(QWidget *parent = nullptr);
private:
    void closeEvent(QCloseEvent*);
    QString setTableView();

    QTableView * tableView;
    QSqlRelationalTableModel * sqlRelationalTableModel;
    QSqlQueryModel * sqlQueryModel;

signals:
    void firstWindow();  // Сигнал для первого окна на открытие
};

#endif // DISPLAYDATAWIDGET_H
