#include "interface.h"

TInterface::TInterface(QWidget *parent)
          : QWidget(parent)
{
    t1 = new QLabel("Chance to break Z1:",this);
    t1->setGeometry(20,30,150,25);

    t2 = new QLabel("Chance to break Z2:",this);
    t2->setGeometry(220,30,150,25);

    t3 = new QLabel("Time to solve R1:",this);
    t3->setGeometry(20,70,150,25);

    t4 = new QLabel("Time to solve R2:",this);
    t4->setGeometry(220,70,150,25);


    z1_param = new QLineEdit("z1",this);
    z1_param->setGeometry(155,30,40,25);

    z2_param = new QLineEdit("z2",this);
    z2_param->setGeometry(355,30,40,25);


    r1_param = new QLineEdit("r1",this);
    r1_param->setGeometry(155,70,40,25);

    r2_param = new QLineEdit("r2",this);
    r2_param->setGeometry(355,70,40,25);

    ///////////////////////////////////

    t5 = new QLabel("Set the scale of time: ",this);
    t5->setGeometry(160,120,150,25);


    radio1 = new QRadioButton("1sec = 1hour",this);

    radio1->setGeometry(20,160,110,25);

    radio2 = new QRadioButton("1sec = 1day ",this);

    radio2->setGeometry(150,160,110,25);

    radio3 = new QRadioButton("1sec = 10days",this);

    radio3->setGeometry(280,160,110,25);

    radio1->setChecked(true);





    btn = new QPushButton("Start",this);
    btn->setGeometry(5,210,100,30);



    btn3 = new QPushButton("Clear",this);
    btn3->setGeometry(310,210,100,30);

    t6 = new QLabel("Mechanic ready to work: ",this);
    t6->setGeometry(20,240,170,25);

    t7 = new QLabel("MechanicSenior: ",this);
    t7->setGeometry(20,275,160,25);

    t8 = new QLabel("MechanicLight: ",this);
    t8->setGeometry(20,315,160,25);

    t9 = new QLabel("MechanicHeavy: ",this);
    t9->setGeometry(20,355,160,25);

    lineEditIntStatusInfoMechanicSenior = new QLineEdit(this);
    lineEditIntStatusInfoMechanicSenior->setGeometry(130,275,55,25);
    lineEditIntStatusInfoMechanicSenior->setReadOnly(true);

    lineEditIntStatusInfoMechanicLightVehicle = new QLineEdit(this);
    lineEditIntStatusInfoMechanicLightVehicle->setGeometry(130,315,55,25);
    lineEditIntStatusInfoMechanicLightVehicle->setReadOnly(true);

    lineEditIntStatusInfoMechanicHeavyVehicle = new QLineEdit(this);
    lineEditIntStatusInfoMechanicHeavyVehicle->setGeometry(130,355,55,25);
    lineEditIntStatusInfoMechanicHeavyVehicle->setReadOnly(true);

    t10 = new QLabel("Vehicle ready to work: ",this);
    t10->setGeometry(250,240,170,25);

    t11 = new QLabel("FirstLight: ",this);
    t11->setGeometry(250,270,160,25);

    t12 = new QLabel("SecondLight: ",this);
    t12->setGeometry(250,300,160,25);

    t13 = new QLabel("FirstHeavy: ",this);
    t13->setGeometry(250,330,160,25);

    t14 = new QLabel("SecondHeavy: ",this);
    t14->setGeometry(250,360,160,25);

    lineEditIntStatusFirstLightVehicle = new QLineEdit(this);
    lineEditIntStatusFirstLightVehicle->setGeometry(340,270,55,25);
    lineEditIntStatusFirstLightVehicle->setReadOnly(true);

    lineEditIntStatusSecondLightVehicle = new QLineEdit(this);
    lineEditIntStatusSecondLightVehicle->setGeometry(340,300,55,25);
    lineEditIntStatusSecondLightVehicle->setReadOnly(true);

    lineEditIntStatusFirstHeavyVehicle = new QLineEdit(this);
    lineEditIntStatusFirstHeavyVehicle->setGeometry(340,330,55,25);
    lineEditIntStatusFirstHeavyVehicle->setReadOnly(true);

    lineEditIntStatusSecondHeavyVehicle = new QLineEdit(this);
    lineEditIntStatusSecondHeavyVehicle->setGeometry(340,360,55,25);
    lineEditIntStatusSecondHeavyVehicle->setReadOnly(true);

    t23 = new QLabel("Vehicle in repair or not: ",this);
    t23->setGeometry(150,390,150,25);

    t24 = new QLabel("FirstLight: ",this);
    t24->setGeometry(20,420,150,25);

    lineIntInRepairOrNotFirstLightVehicle = new QLineEdit(this);
    lineIntInRepairOrNotFirstLightVehicle->setGeometry(130,420,55,25);
    lineIntInRepairOrNotFirstLightVehicle->setReadOnly(true);

    t25 = new QLabel("SecondLight: ",this);
    t25->setGeometry(20,450,150,25);

    lineIntInRepairOrNotSecondLightVehicle = new QLineEdit(this);
    lineIntInRepairOrNotSecondLightVehicle->setGeometry(130,450,55,25);
    lineIntInRepairOrNotSecondLightVehicle->setReadOnly(true);


    t26 = new QLabel("FirstHeavy: ",this);
    t26->setGeometry(250,420,150,25);

    lineIntInRepairOrNotFirstHeavyVehicle = new QLineEdit(this);
    lineIntInRepairOrNotFirstHeavyVehicle->setGeometry(340,420,55,25);
    lineIntInRepairOrNotFirstHeavyVehicle->setReadOnly(true);


    t27 = new QLabel("SecondHeavy: ",this);
    t27->setGeometry(250,450,150,25);

    lineIntInRepairOrNotSecondHeavyVehicle = new QLineEdit(this);
    lineIntInRepairOrNotSecondHeavyVehicle->setGeometry(340,450,55,25);
    lineIntInRepairOrNotSecondHeavyVehicle->setReadOnly(true);



    t15 = new QLabel("Counts of crashes: ",this);
    t15->setGeometry(170,490,150,25);

    t16 = new QLabel("FirstLight: ",this);
    t16->setGeometry(20,520,150,25);

    lineEditIntCountFirstLightVehicle = new QLineEdit(this);
    lineEditIntCountFirstLightVehicle->setGeometry(130,520,55,25);
    lineEditIntCountFirstLightVehicle->setReadOnly(true);

    t17 = new QLabel("SecondLight: ",this);
    t17->setGeometry(20,550,150,25);

    lineEditIntCountSecondLightVehicle = new QLineEdit(this);
    lineEditIntCountSecondLightVehicle->setGeometry(130,550,55,25);
    lineEditIntCountSecondLightVehicle->setReadOnly(true);

    t18 = new QLabel("FirstHeavy: ",this);
    t18->setGeometry(250,520,150,25);

    lineEditIntCountFirstHeavyVehicle = new QLineEdit(this);
    lineEditIntCountFirstHeavyVehicle->setGeometry(340,520,55,25);
    lineEditIntCountFirstHeavyVehicle->setReadOnly(true);

    t19 = new QLabel("SecondHeavy: ",this);
    t19->setGeometry(250,550,150,25);

    lineEditIntCountSecondHeavyVehicle = new QLineEdit(this);
    lineEditIntCountSecondHeavyVehicle->setGeometry(340,550,55,25);
    lineEditIntCountSecondHeavyVehicle->setReadOnly(true);

    t20 = new QLabel("Statistics: ",this);
    t20->setGeometry(190,580,150,25);

    t19 = new QLabel("Expected Value: ",this);
    t19->setGeometry(20,610,150,25);

    lineEditIntExpectedValue = new QLineEdit(this);
    lineEditIntExpectedValue->setGeometry(130,610,55,25);
    lineEditIntExpectedValue->setReadOnly(true);

    t22 = new QLabel("Standard Deviation: ",this);
    t22->setGeometry(220,610,150,25);

    lineEditIntStandardDeviation = new QLineEdit(this);
    lineEditIntStandardDeviation->setGeometry(340,610,55,25);
    lineEditIntStandardDeviation->setReadOnly(true);





    connect(btn,SIGNAL(pressed()),this,SLOT(slotButton0()));

    connect(btn3,SIGNAL(pressed()),this,SLOT(slotButton3()));

    setWindowTitle("Working hard ver 1.0");
    setFixedSize(415,650);
}

TInterface::~TInterface()
{

}

void TInterface::sendEvent(int pushButton)
{
    TInterfaceMessage msg;
    int radioButton = 0;

    if(this->radio1->isChecked()) radioButton = 0;
    if(this->radio2->isChecked()) radioButton = 1;
    if(this->radio3->isChecked()) radioButton = 2;

    if (pushButton == 3)
    {
        //clear the Info
        z1_param->setText("");
        z2_param->setText("");
        r1_param->setText("");
        r2_param->setText("");

        lineEditIntStatusInfoMechanicSenior->setText("");
        lineEditIntStatusInfoMechanicLightVehicle->setText("");
        lineEditIntStatusInfoMechanicHeavyVehicle->setText("");
        lineEditIntCountFirstLightVehicle->setText("");
        lineEditIntCountSecondLightVehicle->setText("");

        lineEditIntCountFirstHeavyVehicle->setText("");
        lineEditIntCountSecondHeavyVehicle->setText("");
        lineEditIntStatusFirstLightVehicle->setText("");
        lineEditIntStatusSecondLightVehicle->setText("");

        lineEditIntStatusFirstHeavyVehicle->setText("");
        lineEditIntStatusSecondHeavyVehicle->setText("");
        lineEditIntExpectedValue->setText("");
        lineEditIntStandardDeviation->setText("");

        lineIntInRepairOrNotFirstHeavyVehicle->setText("");
        lineIntInRepairOrNotSecondHeavyVehicle->setText("");
        lineIntInRepairOrNotFirstLightVehicle->setText("");
        lineIntInRepairOrNotSecondLightVehicle->setText("");

        lineEditIntExpectedValue->setText("");
        lineEditIntStandardDeviation->setText("");

    }


    else
    {
    msg.intRadioButton = QString::number(radioButton);
    msg.intDataZ1 = z1_param->text();
    msg.intDataZ2 = z2_param->text();
    msg.intDataR1 = r1_param->text();
    msg.intDataR2 = r2_param->text();
    emit send(msg);
    }
}

void TInterface::recieve(TModelMessage msg)
{

    lineEditIntStatusInfoMechanicSenior->setText(msg.intStatusInfoMechanicSenior);
    lineEditIntStatusInfoMechanicLightVehicle->setText(msg.intStatusSecondLightVehicle);
    lineEditIntStatusInfoMechanicHeavyVehicle->setText(msg.intStatusInfoMechanicHeavyVehicle);
    lineEditIntCountFirstLightVehicle->setText(msg.intCountFirstLightVehicle);
    lineEditIntCountSecondLightVehicle->setText(msg.intCountSecondLightVehicle);
    lineEditIntCountFirstHeavyVehicle->setText(msg.intCountFirstHeavyVehicle);
    lineEditIntCountSecondHeavyVehicle->setText(msg.intCountSecondHeavyVehicle);
    lineEditIntStatusFirstLightVehicle->setText(msg.intStatusFirstLightVehicle);
    lineEditIntStatusSecondLightVehicle->setText(msg.intStatusSecondLightVehicle);
    lineEditIntStatusFirstHeavyVehicle->setText(msg.intStatusFirstHeavyVehicle);
    lineEditIntStatusSecondHeavyVehicle->setText(msg.intStatusSecondHeavyVehicle);
    lineIntInRepairOrNotFirstHeavyVehicle->setText(msg.intInRepairOrNotFirstHeavyVehicle);
    lineIntInRepairOrNotSecondHeavyVehicle->setText(msg.intInRepairOrNotSecondHeavyVehicle);
    lineIntInRepairOrNotFirstLightVehicle->setText(msg.intInRepairOrNotFirstLightVehicle);
    lineIntInRepairOrNotSecondLightVehicle->setText(msg.intInRepairOrNotSecondLightVehicle);
    lineEditIntExpectedValue->setText(msg.intExpectedValue == "-1" ? "Nothing" : msg.intExpectedValue);
    lineEditIntStandardDeviation->setText(msg.intStandardDeviation == "-1" ? "Nothing" : msg.intStandardDeviation);

}

void TInterface::slotButton0()
{
    emit sendEvent(0);
}


void TInterface::slotButton3()
{
    emit sendEvent(3);
}
