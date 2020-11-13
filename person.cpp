#include "person.h"
#include "test_runner.h"

#include <QRegExpValidator>

#include <QDebug>

Person::Person()
{

}

QStringList Person::validate(QString name, bool male, int age, int hight, int weight, QString ethnicGroup,
                             QDate birthDate, QDate deathDate, bool isAlive){
    QStringList errors;

    QString checkResult = checkName(name);
    if (!checkResult.isEmpty()){
        errors+=checkResult;
    }

    checkResult = checkBody(hight, weight);



    /*errors += "testError1";
    errors += "testError2";*/

    return errors;
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
                    return "Некорректная последовательность: " + name[i-1] + name[i];
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

void Person::TestCheckName(){
    //ASSERT - функция из "test_runner.h"

    {
        QString name = "";
        QString error = checkName(name);
        ASSERT(!error.isEmpty());
    }

    {//244 символа
        QString name = "ЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦ"
                       "ЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦ"
                       "ЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦ"
                       "ЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦЦ";
        QString error = checkName(name);
        ASSERT(!error.isEmpty());
    }

    {
        QString name = "Вася";
        QString error = checkName(name);
        ASSERT(error.isEmpty());
    }

    {
        QString name = "Yasya";
        QString error = checkName(name);
        ASSERT(!error.isEmpty());
    }

    {
        QString name = "вАсЯ";
        QString error = checkName(name);
        ASSERT(error.isEmpty());
    }

    {
        QString name = "Василий Петров-Чет";
        QString error = checkName(name);
        ASSERT(error.isEmpty());
    }

    {
        QString name = "М'Айк Лжец";
        QString error = checkName(name);
        ASSERT(error.isEmpty());
    }

    {
        QString name = "Я";
        QString error = checkName(name);
        ASSERT(error.isEmpty());
    }

    {
        QString name = "Иоганн фон Нейман";
        QString error = checkName(name);
        ASSERT(error.isEmpty());
    }

    {
        QString name = "Дональд Трамп Мл.";
        QString error = checkName(name);
        ASSERT(!error.isEmpty());
    }

    {
        QString name = "аАуа";
        QString error = checkName(name);
        ASSERT(error.isEmpty());
    }

    {
        QString name = "А б В г-д";
        QString error = checkName(name);
        ASSERT(error.isEmpty());
    }

    {
        QString name = "Вася  Пробелы";
        QString error = checkName(name);
        ASSERT(!error.isEmpty());
    }

    {
        QString name = "Вася'-Василий";
        QString error = checkName(name);
        ASSERT(!error.isEmpty());
    }

    {
        QString name = "Вася`Василий";
        QString error = checkName(name);
        ASSERT(!error.isEmpty());
    }
}

bool Person::isOkAlphabet(QChar c){
    return (c>=L'а' && c<=L'я') || (c>=L'А' && c<=L'Я') || c==L'ё' || c==L'Ё';
}

bool Person::isOkNotAlphabet(QChar c){
    return c==L'-' || c==L' ' || c==L'\'';
}
