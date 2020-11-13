#include "insertdatawidget.h"
#include "person.h"
//#include "database.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
//#include <QLineEdit>
//#include <QRadioButton>
//#include <QSpinBox>
//#include <QComboBox>
//#include <QDateEdit>
//#include <QCheckBox>
#include <QPushButton>

#include <QMessageBox>
#include <QDebug>
#include <fstream> //readEthnicGroups
#include <algorithm> //readEthnicGroups
#include <stdexcept>//исключения

InsertDataWidget::InsertDataWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Информация о человеке: ввод данных");//Название окна

    /*{//temp
        qDebug()<<"Testing Person";
        Person p;
        p.TestCheckName();
    }*/

    QVBoxLayout * vLayout = new QVBoxLayout(this);

    QGroupBox * dataGroupBox = new QGroupBox("Введите информацию");
    vLayout->addWidget(dataGroupBox);

    QVBoxLayout * dataLayout = new QVBoxLayout();
    dataGroupBox->setLayout(dataLayout);

    int spacingSize = 0;//Пробелы между сгруппироваными полями QLabel - ...
    //Можно сделать через setSpacing, но тогда надо группировать попарно элементы в QVBoxLayout

    {
        //Имя без разделения на ФИО
        //Максимум 200 символов (не будут же сюда писать свои титулы)

        QLabel * nameLabel = new QLabel("Имя");
        dataLayout->addWidget(nameLabel);

        nameLineEdit = new QLineEdit();
        dataLayout->addWidget(nameLineEdit);
        nameLineEdit->setMaxLength(200);
        /*
        QString validCharacters = "A";
        //nameLineEdit->setInputMask(validCharacters);//Посимвольная маска не подходит
        nameLineEdit->setValidator(validCharacters);
        */
    }

    dataLayout->addSpacing(spacingSize);

    {
        //Пол (без вертолётов и возможности не указывать)

        QLabel * genderLabel = new QLabel("Пол");
        dataLayout->addWidget(genderLabel);

        QHBoxLayout * genderLayout = new QHBoxLayout();
        dataLayout->addLayout(genderLayout);

        maleRadioButton = new QRadioButton("M");
        genderLayout->addWidget(maleRadioButton);
        femaleRadioButton = new QRadioButton("Ж");
        genderLayout->addWidget(femaleRadioButton);

        //Можно создать для кнопок QButtonGroup, чтобы они не влияли на другие возможные кнопки
        //Или так:
        maleRadioButton->setAutoExclusive(true);
        femaleRadioButton->setAutoExclusive(true);

        maleRadioButton->setChecked(true);
    }

    dataLayout->addSpacing(spacingSize);

    {
        //Возраст
        //От 0 до 150
        //При наличии даты рождения и текущего времени - сомнительное удовольствие
        //Как его проверять и зачем он нужен?
        //Окей, допустим, что это - возраст в какой-то определённый момент. Например,
        //возраст, в котором человек последний раз участвовал в шахматном турнире.
        //Дополнительный вариант решения - его "внутренний возраст" аля самочувствие
        //Или же как с юбилеями писателей - может идти на сотни лет

        //Для проверок - возраст сейчас или в прошедший для человека момент времени

        QLabel * ageLabel = new QLabel("Возраст");
        dataLayout->addWidget(ageLabel);

        ageSpinBox = new QSpinBox();
        dataLayout->addWidget(ageSpinBox);
        ageSpinBox->setRange(0, 150);
        ageSpinBox->setValue(20);
    }

    dataLayout->addSpacing(spacingSize);

    {
        //Рост
        //От 40 см до 280 см (от младенца до самого высокого человека + чуть-чуть)

        QLabel * hightLabel = new QLabel("Рост, см");
        dataLayout->addWidget(hightLabel);

        hightSpinBox = new QSpinBox();
        dataLayout->addWidget(hightSpinBox);
        hightSpinBox->setRange(40, 280);
        hightSpinBox->setValue(170);
    }

    dataLayout->addSpacing(spacingSize);

    {
        //Вес
        //От 2 кг до 1000 кг (ого, вес Кэрол Ягер был 927 кг)

        QLabel * weightLabel = new QLabel("Вес, кг");
        dataLayout->addWidget(weightLabel);

        weightSpinBox = new QSpinBox();
        dataLayout->addWidget(weightSpinBox);
        weightSpinBox->setRange(2, 1000);
        weightSpinBox->setValue(45);
    }

    dataLayout->addSpacing(spacingSize);

    {
        //Национальность (народность)
        QLabel * ethnicLabel = new QLabel("Национальность");
        dataLayout->addWidget(ethnicLabel);

        ethnicComboBox = new QComboBox();
        dataLayout->addWidget(ethnicComboBox);

        QStringList ethnicGroups = readEthnicGroups();
        if (ethnicGroups.empty()){
            QMessageBox::warning(this, tr("InsertDataWidget"),
                                 tr("readEthnicGroups() returned empty QStringList\n"
                                    "Aborting..."));
            Q_ASSERT(false);
        }
        ethnicComboBox->addItems(ethnicGroups);
    }

    dataLayout->addSpacing(spacingSize);

    {
        //Дата рождения
        //От 1900 года до 2100
        //Как вариант - до текущего дня. Вот только время на компьютере может стоять неправильное
        QLabel * birthDateLabel = new QLabel("Дата рождения (день, месяц, год)");
        dataLayout->addWidget(birthDateLabel);

        birthDateEdit = new QDateEdit();//Ещё вариант - ввод в виде строки (в различных форматах)
        dataLayout->addWidget(birthDateEdit);
        birthDateEdit->setMinimumDate(QDate(1900,1,1));//QDate(int y, int m, int d)
        birthDateEdit->setMaximumDate(QDate(2100,1,1));//QDate(int y, int m, int d)

        birthDateEdit->setDate(QDate(2000,1,1));//QDate(int y, int m, int d)
    }

    dataLayout->addSpacing(spacingSize);

    {
        //Дата cмерти
        //Настройка аналогично дате рождения
        QHBoxLayout * deathLabelLayout = new QHBoxLayout();
        dataLayout->addLayout(deathLabelLayout);

        QLabel * deathDateLabel = new QLabel("Дата смерти (опционально)");
        deathLabelLayout->addWidget(deathDateLabel);

        deathCheckBox = new QCheckBox();
        deathLabelLayout->addWidget(deathCheckBox);

        deathDateEdit = new QDateEdit();
        dataLayout->addWidget(deathDateEdit);
        deathDateEdit->setMinimumDate(QDate(1900,1,1));//QDate(int y, int m, int d)
        deathDateEdit->setMaximumDate(QDate(2100,1,1));//QDate(int y, int m, int d)

        deathDateEdit->setDate(QDate(2000,1,1));//QDate(int y, int m, int d)

        deathCheckBox->setChecked(false);
        deathDateEdit->setEnabled(false);
        connect(deathCheckBox,SIGNAL(toggled(bool)),deathDateEdit,SLOT(setEnabled(bool)));
    }


    {
        //Кнопки управления
        QHBoxLayout * buttonsLayout = new QHBoxLayout();
        vLayout->addLayout(buttonsLayout);

        QPushButton * saveDataPushButton = new QPushButton("Сохранить информацию\n"
                                                           "о человеке");
        buttonsLayout->addWidget(saveDataPushButton);
        connect(saveDataPushButton, SIGNAL(clicked()),SLOT(saveDataPushButtonClicked()));

        QPushButton * closePushButton = new QPushButton("Вернуться к выбору действий");
        buttonsLayout->addWidget(closePushButton);
        connect(closePushButton, SIGNAL(clicked()),SLOT(closePushButtonClicked()));

        //Для одинакового размера кнопок
        saveDataPushButton->setMinimumWidth(170);
        closePushButton->setMinimumWidth(170);

        saveDataPushButton ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        closePushButton ->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    }





}

QStringList InsertDataWidget::readEthnicGroups(){
    using namespace std;
    ifstream fin("Ethnic_groups_in_Russia.txt");
    if (!fin.is_open()){
        QMessageBox::warning(this, tr("InsertDataWidget"),
                             tr("readEthnicGroups() cannot open file\n"
                                "Aborting..."));
        Q_ASSERT(false);
        //Другие варианты:
        /*
        std::string errorString= "InsertDataWidget::readEthnicGroups() cannot open file";
        throw std::runtime_error(errorString);
        */
        /*
        Q_ASSERT_X(false, "InsertDataWidget",
                   "readEthnicGroups() cannot open file");
        */
        //abort();
    }
    //Не уверен, что лучше делать: продолжать ограниченную работу (например, выводу данных) или нет
    //Плюс говорят, что в Qt исключениями обычно не пользуются.

    QStringList answer;
    string tempString;

    while (getline(fin, tempString)){
        answer += QString::fromStdString(tempString);
    }

    //Сортировка по алфавиту всех элементов кроме первого (самый часто встречающийся - "Русские")
    //и последнего ("Прочие")
    if (answer.size()>2){
        sort(next(answer.begin()), prev(answer.end()));
    }

    return answer;
}

void InsertDataWidget::resetFieldsToDefault(){
    nameLineEdit->clear();

    maleRadioButton->setChecked(true);

    ageSpinBox->setValue(20);

    hightSpinBox->setValue(170);

    weightSpinBox->setValue(45);

    ethnicComboBox->setCurrentIndex(0);

    birthDateEdit->setDate(QDate(2000,1,1));//QDate(int y, int m, int d)

    deathDateEdit->setDate(QDate(2000,1,1));//QDate(int y, int m, int d)
    deathCheckBox->setChecked(false);
    deathDateEdit->setEnabled(false);
}

void InsertDataWidget::closePushButtonClicked(){
    this->close();
    emit firstWindow();
}

void InsertDataWidget::saveDataPushButtonClicked(){
    Person person;

    /*
    if (!true){//Тестовый вывод
        qDebug()<<"Name:"<<nameLineEdit->text();
        qDebug()<<"Male:"<<maleRadioButton->isChecked();
        qDebug()<<"Age:"<<ageSpinBox->value();
        qDebug()<<"Hight:"<<hightSpinBox->value();
        qDebug()<<"Weight:"<<weightSpinBox->value();
        qDebug()<<"EthnicGroup:"<<ethnicComboBox->currentText();
        qDebug()<<"BirthDate:"<<birthDateEdit->date();
        qDebug()<<"DeathDat:"<<deathDateEdit->date();
        qDebug()<<"IsAlive:"<<!deathCheckBox->isChecked();

    }*/

    /*QStringList validate(QString name, bool male, int age, int hight, int weight, QString ethnicGroup,
                         QDate birthDate, QDate deathDate, bool isAlive);*/
    QStringList errors = person.validate(
                nameLineEdit->text(),
                maleRadioButton->isChecked(),
                ageSpinBox->value(),
                hightSpinBox->value(),
                weightSpinBox->value(),
                ethnicComboBox->currentText(),
                birthDateEdit->date(),
                deathDateEdit->date(),
                !deathCheckBox->isChecked()
                );

    if (errors.empty()){

        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Подтверждение сохранения");
        msgBox.setText("Проверьте правильность информации:");
        msgBox.setInformativeText(person.toQString());
        msgBox.setIcon(QMessageBox::Question);
        msgBox.addButton(tr("Сохранить"), QMessageBox::AcceptRole);
        msgBox.addButton(tr("Отмена"), QMessageBox::RejectRole);

        //int result = msgBox.exec();
        if (msgBox.exec() == QMessageBox::AcceptRole){
            bool writeDbResult = person.writeInDb();
            if (writeDbResult){
                resetFieldsToDefault();
            } else {
                //temp
                //Вывести ошибку? Или она будет выведена при попытке записать в базу?!!!!!!!!!!!!!!
            }
        }//Иначе просто возвращаемся в окно ввода

    } else {

        QString errorMessage("Невозможно сохранить информацию\n\n");
        auto it = errors.begin();
        while (it != std::prev(errors.end())){
            errorMessage += *it;
            errorMessage += '\n';//Добавляем строки ошибок с переводом строки
            it = std::next(it);
        }   errorMessage += *it;//Добавляем последнюю строку

        QMessageBox::warning(this, tr("Внимание"),
                             errorMessage);
    }
}
