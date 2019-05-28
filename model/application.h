#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>

#include "communicator.h"



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

class TApplication : public QCoreApplication
{
    Q_OBJECT

    TCommunicator *comm;


    volatile int buttonPressed;

public:



    TApplication(int, char**);
    void printLogInfo(QTextStream&);
    void modelingTheSituation(TInterfaceMessage, QTextStream&);
    int processTheCfg(TCommParams*);
    void sendInfoToClient(TModelMessage*);
signals:

    void toCommunicator(QByteArray);

public slots:

    void fromCommunicator(QByteArray);

};

#endif // APPLICATION_H
