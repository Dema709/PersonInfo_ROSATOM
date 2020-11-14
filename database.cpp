#include "database.h"

#include <QtSql>
#include <QDebug>

QString initDbForWrite(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("persondb");

    if (!db.open()){
        qDebug()<<db.lastError().text();
        return db.lastError().text();
    }
/*
    QStringList tables = db.tables();
    if (tables.contains("books", Qt::CaseInsensitive)
        && tables.contains("authors", Qt::CaseInsensitive))
        return QSqlError();*/
    return {};
}
