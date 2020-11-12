#include "insertdatawidget.h"

#include <QVBoxLayout>
//#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

#include <QMessageBox>
#include <QDebug>
#include <fstream> //readEthnicGroups
#include <algorithm> //readEthnicGroups
#include <stdexcept>//исключения

InsertDataWidget::InsertDataWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Информация о человеке: ввод данных");//Название окна

    QVBoxLayout * hLayout = new QVBoxLayout(this);

    QGroupBox * dataGroupBox = new QGroupBox("Введите информацию");
    hLayout->addWidget(dataGroupBox);

    QVBoxLayout * dataLayout = new QVBoxLayout();
    dataGroupBox->setLayout(dataLayout);

    int spacingSize = 0;//Пробелы между сгруппироваными полями QLabel - ...
    //Можно сделать через setSpacing, но тогда надо группировать попарно элементы в QVBoxLayout

    {
        //Имя без разделения на ФИО
        //Максимум 200 символов (не будут же сюда писать свои титулы)

        QLabel * nameLabel = new QLabel("Имя");
        dataLayout->addWidget(nameLabel);

        QLineEdit * nameLineEdit = new QLineEdit();
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

        QRadioButton * maleRadioButton = new QRadioButton("M");
        genderLayout->addWidget(maleRadioButton);
        QRadioButton * femaleRadioButton = new QRadioButton("Ж");
        genderLayout->addWidget(femaleRadioButton);

        //Можно создать для кнопок QButtonGroup, чтобы они не влияли на другие возможные кнопки
        //Или так:
        maleRadioButton->setAutoExclusive(true);
        femaleRadioButton->setAutoExclusive(true);
    }

    dataLayout->addSpacing(spacingSize);

    {
        //Возраст
        //От 0 до 150
        //При наличии даты рождения и текущего времени - сомнительное удовольствие
        //Как его проверять и зачем он нужен?
        //Окей, допустим, что это - возраст в какой-то определённый момент. Например,
        //возраст, в котором человек последний раз участвовал в шахматном турнире
        //или его "внутренний возраст" аля самочувствие

        QLabel * ageLabel = new QLabel("Возраст");
        dataLayout->addWidget(ageLabel);

        QSpinBox * ageSpinBox = new QSpinBox();
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

        QSpinBox * hightSpinBox = new QSpinBox();
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

        QSpinBox * weightSpinBox = new QSpinBox();
        dataLayout->addWidget(weightSpinBox);
        weightSpinBox->setRange(2, 1000);
        weightSpinBox->setValue(45);
    }

    dataLayout->addSpacing(spacingSize);

    {
        //Национальность (народность)
        QLabel * ethnicLabel = new QLabel("Национальность");
        dataLayout->addWidget(ethnicLabel);

        QComboBox * ethnicComboBox = new QComboBox();
        dataLayout->addWidget(ethnicComboBox);

        QStringList ethnicGroups = readEthnicGroups();
        if (ethnicGroups.empty()){
            QMessageBox::warning(this, tr("InsertDataWidget"),
                                 tr("readEthnicGroups() returned empty QStringList"));
            Q_ASSERT(false);
        }
        ethnicComboBox->addItems(ethnicGroups);
    }



    //hLayout->addStretch(1);

    QPushButton * closePushButton = new QPushButton("Вернуться к выбору действий");
    hLayout->addWidget(closePushButton);
    connect(closePushButton, SIGNAL(clicked()),SLOT(closePushButtonClicked()));



    /*
    имя
    пол, возраст, рост, вес,
    национальность(выбор из внутреннего списка, например, подмножество
    https://tinyurl.com/q73okuc ), дата рождения,  дата смерти (может отсутствовать,
    ситуация должна быть корректно обработана).
    */
}

void InsertDataWidget::closePushButtonClicked(){
    this->close();
    emit firstWindow();
}

QStringList InsertDataWidget::readEthnicGroups(){
    using namespace std;
    ifstream fin("Ethnic_groups_in_Russia.txt");
    if (!fin.is_open()){
        QMessageBox::warning(this, tr("InsertDataWidget"),
                             tr("readEthnicGroups() cannot open file"));
        Q_ASSERT(false);
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

    if (answer.size()>2){
        sort(next(answer.begin()), prev(answer.end()));
    }

    return answer;
}
