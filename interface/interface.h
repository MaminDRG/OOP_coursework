#ifndef TINTERFACE_H
#define TINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <iostream>

struct TInterfaceMessage
{
    QString intRadioButton;
    QString intDataR1;
    QString intDataR2;
    QString intDataZ1;
    QString intDataZ2;

};

struct TModelMessage
{
    QString intStatusInfoMechanicSenior;
    QString intStatusInfoMechanicLightVehicle;
    QString intStatusInfoMechanicHeavyVehicle;

    QString intCountFirstLightVehicle;
    QString intCountSecondLightVehicle;

    QString intCountFirstHeavyVehicle;
    QString intCountSecondHeavyVehicle;

    QString intStatusFirstLightVehicle;
    QString intStatusSecondLightVehicle;
    QString intStatusFirstHeavyVehicle;
    QString intStatusSecondHeavyVehicle;

    QString intInRepairOrNotFirstLightVehicle;
    QString intInRepairOrNotSecondLightVehicle;
    QString intInRepairOrNotFirstHeavyVehicle;
    QString intInRepairOrNotSecondHeavyVehicle;

    QString intExpectedValue;
    QString intStandardDeviation;


};

class TInterface : public QWidget
{
    Q_OBJECT

    QLabel    *t1;
    QLabel    *t2;
    QLabel    *t3;
    QLabel    *t4;
    QLabel    *t5;
    QLabel    *t6;
    QLabel    *t7;
    QLabel    *t8;
    QLabel    *t9;
    QLabel    *t10;
    QLabel    *t11;
    QLabel    *t12;
    QLabel    *t13;
    QLabel    *t14;
    QLabel    *t15;
    QLabel    *t16;
    QLabel    *t17;
    QLabel    *t18;
    QLabel    *t19;
    QLabel    *t20;
    QLabel    *t21;
    QLabel    *t22;
    QLabel    *t23;
    QLabel    *t24;
    QLabel    *t25;
    QLabel    *t26;
    QLabel    *t27;






    QLineEdit *e1;
    QLineEdit *e2;

    QLineEdit *z1_param;
    QLineEdit *z2_param;
    QLineEdit *r1_param;
    QLineEdit *r2_param;

    QRadioButton *radio1;
    QRadioButton *radio2;
    QRadioButton *radio3;


    QPushButton *btn;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;

    QLineEdit *lineEditIntStatusInfoMechanicSenior;
    QLineEdit *lineEditIntStatusInfoMechanicLightVehicle;
    QLineEdit *lineEditIntStatusInfoMechanicHeavyVehicle;

    QLineEdit *lineEditIntCountFirstLightVehicle;
    QLineEdit *lineEditIntCountSecondLightVehicle;
    QLineEdit *lineEditIntCountFirstHeavyVehicle;
    QLineEdit *lineEditIntCountSecondHeavyVehicle;

    QLineEdit *lineEditIntStatusFirstLightVehicle;
    QLineEdit *lineEditIntStatusSecondLightVehicle;
    QLineEdit *lineEditIntStatusFirstHeavyVehicle;
    QLineEdit *lineEditIntStatusSecondHeavyVehicle;

    QLineEdit *lineIntInRepairOrNotFirstLightVehicle;
    QLineEdit *lineIntInRepairOrNotSecondLightVehicle;
    QLineEdit *lineIntInRepairOrNotFirstHeavyVehicle;
    QLineEdit *lineIntInRepairOrNotSecondHeavyVehicle;


    QLineEdit *lineEditIntExpectedValue;
    QLineEdit *lineEditIntStandardDeviation;

public:
    TInterface(QWidget *parent = 0);
    ~TInterface();

signals:

    void send(TInterfaceMessage);

private slots:

    void sendEvent(int);
    void slotButton0();

    void slotButton3();

public slots:

    void recieve(TModelMessage);

};

#endif // TINTERFACE_H
