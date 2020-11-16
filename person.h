#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>

class Person
{
public:
    //При прохождении проверок заполняет поля класса
    //Возвращает список с ошибками при проверке на правдоподобность
    QStringList validate(QString name, bool male, int age, int hight, int weight, QString ethnicGroup,
                         QDate birthDate, QDate deathDate, bool isAlive);
    QString toQString();
    QString writeInDb();

    //Если бы не было тестов, эти функции могли бы быть private:
    //Или же private slots: (если тестировать Qt-шными тестами)
    QString checkName(QString& name);
    QString checkBody(int hight, int weight);
    QString checkEthnicGroup(QString& ethnicGroup);
    QString checkDates(QDate birthDate, QDate deathDate, bool isAlive, int age);



private:
    bool isInitialized = false;//Для предотвращения выдачи незабитой информации

    QString name_;
    bool male_;
    int age_;
    int hight_;
    int weight_;
    QString ethnicGroup_;
    QDate birthDate_;
    QDate deathDate_;
    bool isAlive_;

    bool isOkAlphabet(QChar c);
    bool isOkNotAlphabet(QChar c);
};

#endif // PERSON_H
