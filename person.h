#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QDate>

class Person
{
public:
    Person();

    //При прохождении проверок заполняет поля класса
    //Возвращает список с ошибками при проверке на правдоподобность
    QStringList validate(QString name, bool male, int age, int hight, int weight, QString ethnicGroup,
                         QDate birthDate, QDate deathDate, bool isAlive);
    QString checkName(QString& name);
    QString checkBody(int hight, int weight);

    void TestCheckName();//Проверка валидности имени


private:
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