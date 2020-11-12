#include "insertdatawidget.h"

#include <QVBoxLayout>
//#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>

#include <QDebug>

InsertDataWidget::InsertDataWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Информация о человеке: ввод данных");//Название окна

    QVBoxLayout * hLayout = new QVBoxLayout(this);

    QGroupBox * dataGroupBox = new QGroupBox("Введите информацию");
    hLayout->addWidget(dataGroupBox);

    QVBoxLayout * dataLayout = new QVBoxLayout();
    dataGroupBox->setLayout(dataLayout);

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

    dataLayout->addSpacing(10);

    {
        //Пол (без вертолётов и возможности не указывать)

        QLabel * genderLabel = new QLabel("Пол");
        dataLayout->addWidget(genderLabel);

        QHBoxLayout * genderLayout = new QHBoxLayout();
        dataLayout->addLayout(genderLayout);

        //Можно создать для кнопок QButtonGroup, чтобы они не влияли на другие возможные кнопки
        QRadioButton * maleRadioButton = new QRadioButton("M");
        genderLayout->addWidget(maleRadioButton);
        QRadioButton * femaleRadioButton = new QRadioButton("Ж");
        genderLayout->addWidget(femaleRadioButton);
    }

    dataLayout->addSpacing(10);

    {
        //Возраст
        //При наличии даты рождения и текущего времени - сомнительное удовольствие
        //Как его проверять и зачем он нужен?
        //Окей, допустим, что это - возраст в какой-то определённый момент. Например,
        //возраст, в котором человек последний раз участвовал в шахматном турнире
        //или его "внутренний возраст" аля самочувствие
    }

    QPushButton * closePushButton = new QPushButton("Вернуться к выбору действий");
    connect(closePushButton, SIGNAL(clicked()),SLOT(closePushButtonClicked()));
    hLayout->addWidget(closePushButton);



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
