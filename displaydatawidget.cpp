#include "displaydatawidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QSqlError>
#include <QMessageBox>

#include <QDebug>

DisplayDataWidget::DisplayDataWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("Информация о человеке: вывод данных");//Название окна
    resize(650, 300);

    QVBoxLayout * vLayout = new QVBoxLayout(this);

    tableView = new QTableView();
    vLayout->addWidget(tableView);

    QString errorMessage = setTableView();
    if (!errorMessage.isEmpty()){
        QMessageBox::warning(this, tr("Внимание"),
                             "Невозможно сохранить информацию\n\n" + errorMessage);
    }

    QPushButton * closePushButton = new QPushButton("Вернуться к выбору действий");
    vLayout->addWidget(closePushButton);
    connect(closePushButton, &QPushButton::clicked, this, &DisplayDataWidget::close);
}

void DisplayDataWidget::closeEvent(QCloseEvent*){
    //qDebug()<<"DisplayDataWidget::closeEvent";
    emit firstWindow();
}

QString DisplayDataWidget::setTableView(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("person.db");

    if (!db.open()){
        qDebug()<<db.lastError().text();
        return db.lastError().text();
    }

    sqlQueryModel = new QSqlQueryModel(this);
    sqlQueryModel->setQuery("SELECT name as Имя,"

                            "CASE WHEN male=0 THEN 'Ж'"
                            "WHEN male=1 THEN 'М'"
                            "END         as Пол,"

                            "age         as Возраст,"
                            "hight       as 'Рост, см',"
                            "weight      as 'Вес, кг',"
                            "ethnicGroup as Национальность,"
                            "birthDate   as 'Дата рождения',"

                            "CASE WHEN isAlive=0 THEN (SELECT deathDate)"
                            "END         as 'Дата смерти'"

                            " FROM persons;");
    if (sqlQueryModel->lastError().isValid()){
        return sqlQueryModel->lastError().text();
    }

    tableView->setModel(sqlQueryModel);
    tableView->resizeColumnsToContents();

    return {};
}
