#include "database.h"

#include <QtSql>
#include <QDebug>

QString createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("person.db");

    if (!db.open()){
        qDebug()<<db.lastError().text();
        return db.lastError().text();
    }
    return {};
}

QString closeConnection(){
    //db.close();

    return {};
}

QString initDbForWrite(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("person.db");

    if (!db.open()){
        qDebug()<<db.lastError().text();
        return db.lastError().text();
    }

    QStringList tables = db.tables();
    if (!tables.contains("persons", Qt::CaseInsensitive)){

    }

    const auto BOOKS_SQL = QLatin1String(R"(
        create table persons(id integer primary key, title varchar, author integer,
                           genre integer, year integer, rating integer)
        )");

    QSqlQuery q;
    if (!q.exec(BOOKS_SQL))
        return q.lastError().text();





    return {};
}
