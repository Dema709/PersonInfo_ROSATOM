#ifndef DATABASE_H
#define DATABASE_H

#include <QString>

//Функции возвращают строку с ошибкой
QString createConnection();
QString initDbForWrite();

#endif // DATABASE_H
