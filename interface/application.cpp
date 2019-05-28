#include "application.h"

#include <QDebug>

int TApplication::processTheCfg(TCommParams* pars)
{
    using namespace libconfig;
    Config cfg;

        // Read the file. If there is an error, report it and exit.
        try
        {
            cfg.readFile("asd.cfg");
        }
        catch(const FileIOException &fioex)
        {
            std::cerr << "I/O error while reading file." << std::endl;
            return(EXIT_FAILURE);
        }
        catch(const ParseException &pex)
        {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
            << " - " << pex.getError() << std::endl;
            return(EXIT_FAILURE);
        }

        // Get the rHost name.
        try
        {
            std::string rHostCFG = cfg.lookup("rHost");
            pars->rHost = QHostAddress(QString::fromStdString(rHostCFG));
            std::cout << "rHost: " << rHostCFG << std::endl;
        }
        catch(const SettingNotFoundException &nfex)
        {
            std::cerr << "No 'rHost' setting in configuration file." << std::endl;
        }

        // Get the sHost name.

        try
        {
            std::string sHostCFG = cfg.lookup("sHost");
            pars->sHost = QHostAddress(QString::fromStdString(sHostCFG));
            std::cout << "sHost: " << sHostCFG << std::endl;
        }
        catch(const SettingNotFoundException &nfex)
        {
            std::cerr << "No 'sHost' setting in configuration file." << std::endl;
        }


        // Get the rPort.
        try
        {
            uint rPortCFG = cfg.lookup("rPort");
            pars->rPort = rPortCFG;
            std::cout << "rPort: " << rPortCFG << std::endl;
        }
        catch(const SettingNotFoundException &nfex)
        {
            std::cerr << "No 'rPort' setting in configuration file." << std::endl;
        }

        // Get the sPort.
        try
        {
            uint sPortCFG = cfg.lookup("sPort");
            pars->sPort = sPortCFG;
            std::cout << "sPort: " << sPortCFG << std::endl;
        }
        catch(const SettingNotFoundException &nfex)
        {
            std::cerr << "No 'sPort' setting in configuration file." << std::endl;
        }

        return(EXIT_SUCCESS);
}


TApplication::TApplication(int argc, char *argv[])
            : QApplication(argc,argv)
{

    TCommParams* pars = new TCommParams;

    int statusError = processTheCfg(pars);

    if(statusError == 1)
    {
       delete pars;
       throw 1;
    }

   // TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
     //                    QHostAddress("127.0.0.1"), 10001};
    comm = new TCommunicator(*pars, this);
    interface = new TInterface();
    interface->show();

    connect(interface,SIGNAL(send(TInterfaceMessage)),
            this,SLOT(fromInterface(TInterfaceMessage)));
    connect(this,SIGNAL(toCommunicator(QByteArray)),comm,SLOT(send(QByteArray)));
    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(fromCommunicator(QByteArray)));
    connect(this,SIGNAL(toInterface(TModelMessage)),
            interface,SLOT(recieve(TModelMessage)));
}

void TApplication::fromInterface(TInterfaceMessage msg)
{
    QByteArray data;

    data.append(QByteArray().setNum(msg.intRadioButton.toInt()));
    data.append(";");
    data.append(QByteArray().setNum(msg.intDataR1.toInt()));
    data.append(";");
    data.append(QByteArray().setNum(msg.intDataR2.toInt()));
    data.append(";");
    data.append(QByteArray().setNum(msg.intDataZ1.toDouble()));
    data.append(";");
    data.append(QByteArray().setNum(msg.intDataZ2.toDouble()));

    emit toCommunicator(data);
}

void TApplication::fromCommunicator(QByteArray msg)
{
    int temp = 0;
    int pos = msg.indexOf(";");
    if (pos > 0)
    {
        TModelMessage data;
        QByteArray arr;

        //decode
        data.intStatusInfoMechanicSenior = QString(msg.left(pos));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intStatusInfoMechanicLightVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);


        data.intStatusInfoMechanicHeavyVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intCountFirstLightVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intCountSecondLightVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);


        data.intCountFirstHeavyVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intCountSecondHeavyVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intStatusFirstLightVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);


        data.intStatusSecondLightVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intStatusFirstHeavyVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intStatusSecondHeavyVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intInRepairOrNotFirstLightVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);


        data.intInRepairOrNotSecondLightVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intInRepairOrNotFirstHeavyVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intInRepairOrNotSecondHeavyVehicle = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intExpectedValue = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intStandardDeviation = QString(msg.mid(temp + 1, pos - temp - 1));

      emit toInterface(data);
    }
}
