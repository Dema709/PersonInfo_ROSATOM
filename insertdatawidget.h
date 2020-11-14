#ifndef INSERTDATAWIDGET_H
#define INSERTDATAWIDGET_H

#include <QWidget>

#include <QLineEdit>
#include <QRadioButton>
#include <QSpinBox>
#include <QComboBox>
#include <QDateEdit>
#include <QCheckBox>

class InsertDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InsertDataWidget(QWidget *parent = nullptr);
private:
    void closeEvent(QCloseEvent*);
    QStringList readEthnicGroups();
    void resetFieldsToDefault();

    QLineEdit * nameLineEdit;
    QRadioButton * maleRadioButton;
    QRadioButton * femaleRadioButton;
    QSpinBox * ageSpinBox;
    QSpinBox * hightSpinBox;
    QSpinBox * weightSpinBox;
    QComboBox * ethnicComboBox;
    QDateEdit * birthDateEdit;
    QCheckBox * deathCheckBox;
    QDateEdit * deathDateEdit;

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    void saveDataPushButtonClicked();
};

#endif // INSERTDATAWIDGET_H
