#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>

#include "interface.h"
#include "communicator.h"
#include <libconfig.h++>

class TApplication : public QApplication
{
    Q_OBJECT

    TCommunicator *comm;
    TInterface    *interface;

public:
    int processTheCfg(TCommParams*);
    TApplication(int, char**);

signals:

    void toInterface(TModelMessage);
    void toCommunicator(QByteArray);

public slots:

    void fromInterface(TInterfaceMessage);
    void fromCommunicator(QByteArray);

};

#endif // APPLICATION_H
