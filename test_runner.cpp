#include "test_runner.h"
#include "person.h"

void Test_Person_checkName(){
    Person person;

    {
        QString name = "";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {//244 символа
        QString name = "ЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦ"
                       "ЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦ"
                       "ЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦ"
                       "ЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦ";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {
        QString name = "Вася";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QString name = "Yasya";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {
        QString name = "вАсЯ";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QString name = "Василий Петров-Чет";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QString name = "М'Айк Лжец";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QString name = "Я";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QString name = "Иоганн фон Нейман";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QString name = "Дональд Трамп Мл.";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {
        QString name = "аАуа";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QString name = "А б В г-д";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QString name = "Вася  Пробелы";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {
        QString name = "Вася'-Василий";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {
        QString name = "Вася`Василий";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), false);
    }
}

void Test_Person_checkBody(){
    Person person;
    //QString checkBody(int hight, int weight);

    {
        int hight = 0;
        int weight = 0;
        QString error = person.checkBody(hight, weight);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {
        int hight = 40;
        int weight = 2;
        QString error = person.checkBody(hight, weight);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        int hight = 280;
        int weight = 1000;
        QString error = person.checkBody(hight, weight);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        int hight = 180;
        int weight = 60;
        QString error = person.checkBody(hight, weight);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        int hight = -10;
        int weight = 60;
        QString error = person.checkBody(hight, weight);
        ASSERT_EQUAL(error.isEmpty(), false);
    }
}

void Test_Person_checkEthnicGroup(){
    Person person;

    {
        QString name = "";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {
        QString name = "Прочие";
        QString error = person.checkName(name);
        ASSERT_EQUAL(error.isEmpty(), true);
    }
}

void Test_Person_checkDates(){
    //Тесты рассчитаны на isComputerTimeOk=true;
    //Без проверок по нижней границу дат рождения/смерти (аля 1200 год)

    Person person;
    //QString Person::checkDates(QDate birthDate, QDate deathDate, bool isAlive, int age);
    //QDate(int y, int m, int d)

    {
        QDate birthDate(1800, 1, 1);
        QDate deathDate(1900, 1, 1);
        bool isAlive = false;
        int age = 20;
        QString error = person.checkDates(birthDate, deathDate, isAlive, age);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QDate birthDate(1800, 1, 1);
        QDate deathDate(1900, 1, 1);
        bool isAlive = false;
        int age = 0;
        QString error = person.checkDates(birthDate, deathDate, isAlive, age);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {
        QDate birthDate(2000, 1, 1);
        QDate deathDate(1900, 1, 1);
        bool isAlive = true;
        int age = 20;//Сработает при текущей дате > 1 янв. 2020 года (и до 2150)
        //Не уверен, что программы (куски кода) так долго живут
        QString error = person.checkDates(birthDate, deathDate, isAlive, age);
        ASSERT_EQUAL(error.isEmpty(), true);
    }

    {//200 лет
        QDate birthDate(1800, 1, 1);
        QDate deathDate(2000, 1, 1);
        bool isAlive = false;
        int age = 20;
        QString error = person.checkDates(birthDate, deathDate, isAlive, age);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {//Некорректный возраст
        QDate birthDate(1800, 1, 1);
        QDate deathDate(1900, 1, 1);
        bool isAlive = false;
        int age = -50;
        QString error = person.checkDates(birthDate, deathDate, isAlive, age);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {//Дата рождения - больше 150 лет назад (жив.)
        QDate birthDate(1800, 1, 1);
        QDate deathDate(1900, 1, 1);
        bool isAlive = true;
        int age = 50;
        QString error = person.checkDates(birthDate, deathDate, isAlive, age);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {//Некорректный возраст
        QDate birthDate(1800, 1, 1);
        QDate deathDate(1900, 1, 1);
        bool isAlive = false;
        int age = 120;
        QString error = person.checkDates(birthDate, deathDate, isAlive, age);
        ASSERT_EQUAL(error.isEmpty(), false);
    }

    {//Некорректная дата смерти
        QDate birthDate(1901, 1, 1);
        QDate deathDate(1900, 1, 1);
        bool isAlive = false;
        int age = 0;
        QString error = person.checkDates(birthDate, deathDate, isAlive, age);
        ASSERT_EQUAL(error.isEmpty(), false);
    }
}
