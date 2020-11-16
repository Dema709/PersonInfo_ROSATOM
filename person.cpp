#include "person.h"

#include <QtSql>
#include <QDebug>

QStringList Person::validate(QString name, bool male, int age, int hight, int weight, QString ethnicGroup,
                             QDate birthDate, QDate deathDate, bool isAlive){
    QStringList errors;

    QString checkResult = checkName(name);
    if (!checkResult.isEmpty()){
        errors+=checkResult;
    }

    checkResult = checkBody(hight, weight);
    if (!checkResult.isEmpty()){
        errors+=checkResult;
    }

    checkResult = checkEthnicGroup(ethnicGroup);
    if (!checkResult.isEmpty()){
        errors+=checkResult;
    }

    checkResult = checkDates(birthDate, deathDate, isAlive, age);
    if (!checkResult.isEmpty()){
        errors+=checkResult;
    }

    //Здесь может быть проверка на ethnicGroup. Её нет, так как пока что данные вводятся только
    //из одного места, где все возможные варианты правильны.
    //Поэтому же и некоторые реализованные проверки излишни

    if (errors.empty()){
        //Заполнение структуры
        name_ = name;
        male_ = male;
        age_ = age;
        hight_ = hight;
        weight_ = weight;
        ethnicGroup_ = ethnicGroup;
        birthDate_ = birthDate;
        deathDate_ = deathDate;
        isAlive_ = isAlive;

        isInitialized = true;
    }

    return errors;
}

QString Person::toQString(){
    if (!isInitialized) return {};

    QString output;
    output += "Имя: " + name_ + '\n';
    output += "Пол: " + (male_ ? QString("Мужской") : QString("Женский")) + '\n';
    output += "Возраст: " + QString::number(age_) + '\n';
    output += "Рост: " + QString::number(hight_) + " см\n";
    output += "Вес: " + QString::number(weight_) + " кг\n";
    output += "Национальность: " + ethnicGroup_ + '\n';
    output += "Дата рождения: " + birthDate_.toString("dd.MM.yyyy");
    if (!isAlive_){
        output += "\nДата cмерти: " + deathDate_.toString("dd.MM.yyyy");
    }

    return output;
}

QString Person::writeInDb(){
    if (!isInitialized) return "Person is not initialized";

    //Не уверен, нужно ли вызывать db.close() вручную, потому что:
    //QSqlDatabase::~QSqlDatabase()
    //Note: When the last connection is destroyed, the destructor implicitly calls close() to release the database connection.

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("person.db");

    if (!db.open()){
        qDebug()<<db.lastError().text();
        return db.lastError().text();
    }

    const auto PERSONS_SQL = QLatin1String(R"(
        create table persons(id integer primary key,
                                         name        varchar,
                                         male        boolean,
                                         age         integer,
                                         hight       integer,
                                         weight      integer,
                                         ethnicGroup varchar,
                                         birthDate   date,
                                         deathDate   date,
                                         isAlive     boolean)
        )");

    QSqlQuery q;

    //Если такой таблицы нет, создаём её
    QStringList tables = db.tables();
    if (!tables.contains("persons", Qt::CaseInsensitive)){
        if (!q.exec(PERSONS_SQL)){
            //db.close();
            return q.lastError().text();
        }
    }

    const auto INSERT_REPSON_SQL = QLatin1String(R"(
        insert into persons(name, male, age, hight, weight, ethnicGroup, birthDate, deathDate, isAlive)
                          values(:name, :male, :age, :hight, :weight, :ethnicGroup, :birthDate, :deathDate, :isAlive)
        )");

    if (!q.prepare(INSERT_REPSON_SQL)){
        //db.close();
        return q.lastError().text();
    }

    q.bindValue(":name", name_);
    q.bindValue(":male", male_);
    q.bindValue(":age", age_);
    q.bindValue(":hight", hight_);
    q.bindValue(":weight", weight_);
    q.bindValue(":ethnicGroup", ethnicGroup_);
    q.bindValue(":birthDate", birthDate_);
    q.bindValue(":deathDate", deathDate_);
    q.bindValue(":isAlive", isAlive_);

    if (!q.exec()){
        //db.close();
        return q.lastError().text();
    }

    //db.close();

    return {};
}

QString Person::checkName(QString& name){
    //Длина строки до 200 символов
    //Допустимые символы - буквы русского алфавита (возьмём только ру сегмент для программы),
    //  тире (минус) для двойных фамилий, ' для некоторых имён, пробелы.
    //Имя должно начинаться и заканчиваться на букву
    //В имени не должны идти подряд несколько символов не из русского алфавита (парные пробелы, тире и ')
    //Минимальная длина корректного (по признакам выше имени) - 1 символ (бывают ли такие японцы-китайцы?)

    //Можно добавить проверку на количество слов (будут ли вписывать сюда титулы? ;р)
    //Или же добавить цифры и/или латиницу для имён типа "Раймон VII"
    //Или же проверку на начало имени/слова на заглавную букву (прощайте, "Иоганн фон Нейман")
    //Или же добавить в допустимые символы точку ("Donald Trump Jr.")
    //Или же кроме символа минуса посмотреть все возможные варианты тире

    if (name.size()>200){
        return "Слишком длинное имя";
    } else if (name.isEmpty()){
        return "Имя не задано";
    }

    if (!isOkAlphabet(name[0])){
        return "Имя начинается с некорректного символа";
    }

    if (!isOkAlphabet(name[name.size()-1])){
        return "Имя заканчивается некорректным символом";
    }

    bool lastCharWasNotAlphabet = false;
    for (int i=1; i<name.size()-1; i++){
        if (isOkAlphabet(name[i])){
            lastCharWasNotAlphabet = false;//Буква
        } else {
            if (isOkNotAlphabet(name[i])){
                if (lastCharWasNotAlphabet){//Два небуквенных символа подряд
                    return "Некорректная последовательность: '" + name[i-1] + name[i] + "'";
                } else {
                    lastCharWasNotAlphabet = true;
                }
            } else {
                return "Некорректный символ: " + name[i];
            }
        }
    }

    /*
    //Как вариант - сделать проверку через регулярные выражения
    //Проверка на допустимые символы всей строки:
    QRegExp rx("[а-яА-ЯёЁ '-]+");
    //'+' означает одно или более повторений
    QRegExpValidator nameValidator(rx);
    int pos = 0;

    if (nameValidator.validate(name, pos) != QValidator::Acceptable){
        errors += "Имя содержит недопустимые символы (введите имя на русском)";
        return;
    }
    */

    return {};//Имя корректно
}

QString Person::checkBody(int hight, int weight){
    if (hight < 40 || hight > 280){//От 40 см до 280 см
        return "Неправильный рост";
    }

    if (weight<2 || weight>1000){//От 2 кг до 1000 кг
        return "Неправильный вес";
    }

    return {};
}

QString Person::checkEthnicGroup(QString& ethnicGroup){

    if (ethnicGroup.isEmpty()){
        return "Национальность не задана";
    }

    return {};//Имя корректно
}

QString Person::checkDates(QDate birthDate, QDate deathDate, bool isAlive, int age){
    bool isComputerTimeOk = true;//Так как на некоторых компьютерах не заменяют разряженные батарейки,
            //на них сбрасывается время. В таком случае нет смысла сверять данные с текущей датой

        if (isComputerTimeOk){
            if (birthDate > QDate::currentDate()){
                QString errorString = "Дата рождения некорректна";
                errorString += " (Текущая дата " + QDate::currentDate().toString("dd.MM.yyyy") + ")";
                return errorString;
            }

            if (!isAlive && deathDate > QDate::currentDate()){
                QString errorString = "Дата смерти некорректна";
                errorString += " (Текущая дата " + QDate::currentDate().toString("dd.MM.yyyy") + ")";
                return errorString;
            }

            if (birthDate.addYears(age) > QDate::currentDate()){
                QString errorString = "Возраст некорректен";
                errorString += " (Текущая дата " + QDate::currentDate().toString("dd.MM.yyyy") + ")";
                return errorString;
            }

            //При такой дате рождения возраст будет больше 150 лет
            if (isAlive && birthDate.addYears(150) < QDate::currentDate()){
                QString errorString = "Дата рождения некорректна";
                errorString += " (Текущая дата " + QDate::currentDate().toString("dd.MM.yyyy") + ")";
                return errorString;
            }

            //При такой дате рождения возраст будет больше 150 лет
            if (!isAlive && birthDate.addYears(150) < deathDate){
                QString errorString = "Дата рождения некорректна";
                errorString += " (Текущая дата " + QDate::currentDate().toString("dd.MM.yyyy") + ")";
                return errorString;
            }
        }

        if (!isAlive && birthDate>deathDate){
            return "Даты рождения и смерти не соотносятся";
        }

        if (age<0 || age>150){
            return "Возраст не входит в заданные границы (0 - 150)";
        }

        if (!isAlive && birthDate.addYears(age) > deathDate){
            return "Некорректный возраст (см. дату смерти)";
        }

        return {};
}

bool Person::isOkAlphabet(QChar c){
    return (c>=L'а' && c<=L'я') || (c>=L'А' && c<=L'Я') || c==L'ё' || c==L'Ё';
}

bool Person::isOkNotAlphabet(QChar c){
    return c==L'-' || c==L' ' || c==L'\'';
}
