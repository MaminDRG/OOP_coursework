#include "application.h"
#include <QThread>
#include <QTextStream>
#include <mechanicSenior.h>
#include <lightVehicle.h>
#include <heavyVehicle.h>
#include <queue>
#include <libconfig.h++>
#include "tstatistics.h"

int TApplication::processTheCfg(TCommParams* pars)
{
    using namespace libconfig;
    Config cfg;

        // Read the file. If there is an error, report it and exit.
        try
        {
            cfg.readFile("example.cfg");
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
void TApplication::printLogInfo(QTextStream& Qcout)
{
    time_t t;
    time(&t);
    tm *tme = localtime(&t);

 std::string day = std::to_string(tme->tm_mday);
 std::string month = std::to_string(tme->tm_mon);
 std::string year = std::to_string(1900 + tme->tm_year);
 std::string hour = std::to_string(tme->tm_hour);
 std::string min = std::to_string(tme->tm_min);
 std::string sec = std::to_string(tme->tm_sec);

 std::string timeLog = "[" + day + "/" + month + "/" + year + ":" + hour + ":" + min + ":" + sec + "]" + " " ;
 timeLog = "\033[34m" + timeLog + "\033[0m";


 QString qTimeLog = QString::fromStdString(timeLog);


Qcout.setFieldAlignment(QTextStream::AlignLeft);
Qcout.setFieldWidth(31);

Qcout << qTimeLog;

Qcout.setFieldWidth(1);

}


TApplication::TApplication(int argc, char *argv[])
            : QCoreApplication(argc,argv)
{

  TCommParams* pars = new TCommParams;

  buttonPressed = -1;
  int statusError = processTheCfg(pars);

  if(statusError == 1)
  {
     delete pars;
     throw 1;
  }

 //TCommParams parsTT = { QHostAddress(pars->rHost), pars->rPort,
   //                QHostAddress(pars->sHost), pars->sPort};

 //TCommParams parsT = { QHostAddress("127.0.0.1"), 10001,
   //             QHostAddress("127.0.0.1"), 10000};

    comm = new TCommunicator(*pars, this);

    connect(comm,SIGNAL(recieved(QByteArray)),this,SLOT(fromCommunicator(QByteArray)));
    connect(this,SIGNAL(toCommunicator(QByteArray)),comm,SLOT(send(QByteArray)));
    //delete pars;
}

void TApplication::fromCommunicator(QByteArray msg)
{

    int pos = msg.indexOf(";");
    int temp = 0;

    if (pos > 0)
    {

        TInterfaceMessage data;
        //decode
        data.intRadioButton = QString(msg.left(pos));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intDataR1 = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intDataR2 = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);


        data.intDataZ1 = QString(msg.mid(temp + 1, pos - temp - 1));
        temp = pos;
        pos = msg.indexOf(";",pos+1);

        data.intDataZ2 = QString(msg.mid(temp + 1, pos - temp - 1));
/////////////////////////////



       QTextStream Qcout(stdout);
       this->printLogInfo(Qcout);
       Qcout << "\033[36mMessage from interface:\033[0m";
       //Qcout << " (Z1,Z2,R1,R2) = (";
       Qcout << "(" << data.intRadioButton << ",";
       Qcout << data.intDataZ1 << ",";
       Qcout << data.intDataZ2 << ",";
       Qcout << data.intDataR1 << ",";
       Qcout << data.intDataR2 << ")";
       Qcout << "\n";
       Qcout.flush();

//////////////////////////////////////////

        modelingTheSituation(data,Qcout);

//////////////////////////////////////////


    }
}

void TApplication::modelingTheSituation(TInterfaceMessage dataFromClient, QTextStream& Qcout)
{
    ////////////////////////...
    /// Start calculating

       double exp1Vera = dataFromClient.intDataZ1.toDouble();
       double exp2Vera = dataFromClient.intDataZ2.toDouble();



      TModelMessage*  dataToSend = new TModelMessage;
      TMechanic* MechanicSenior = new TMechanicSenior;
      TMechanic* MechanicHeavyVehicle = new THeavyVehicleMechanic;
      TMechanic* MechanicLightVehicle = new TLightVehicleMechanic;


      TCar* FirstLightCar = new TLightVehicle;
      TCar* SecondLightCar = new TLightVehicle;

      TCar* FirstHeavyCar = new THeavyVehicle;
      TCar* SecondHeavyCar = new THeavyVehicle;


      FirstLightCar->setNumber(1);
      SecondLightCar->setNumber(0);

      FirstHeavyCar->setNumber(1);
      SecondHeavyCar->setNumber(0);

      std::queue<TCar*> myQueueOfBrokenCars;
      std::queue<TCar*> myQueueOfCheckedBrokenCars;
      std::queue<TCar*> myQueueOfCarsReadyToRepair;
      std::queue<TMechanic*> myQueueOfMechanicsReadyToRepair;
      std::vector<int> theTimeOfCrashesFromModeling;



      //myQueueOfCars.push(FirstLightCar);
      //myQueueOfCars.push(SecondLightCar);
      //myQueueOfCars.push(FirstHeavyCar);
      //myQueueOfCars.push(SecondHeavyCar);

      //TStatistics
      srand(time(nullptr));

      int modelingTime = 20;//have to set it from interface
      double randValue = 0;
      ////have to calculate from formulas
      /// P(A) = n/m

      // variables to check how long it is being repaired
      int timeInRepairLightCar1 = 0;
      int timeInRepairLightCar2 = 0;
      int timeInRepairHeavyCar1 = 0;
      int timeInRepairHeavyCar2 = 0;
      int numberOfCar = 0;

      // count of crashes

      int countOfCrashesOfLightCar1 = 0;
      int countOfCrashesOfLightCar2 = 0;
      int countOfCrashesOfHeavyCar1 = 0;
      int countOfCrashesOfHeavyCar2 = 0;

      ///time to repair vehicle
      int timeToRepairLightCar = dataFromClient.intDataR1.toInt();
      int timeToRepairHeavyCar = dataFromClient.intDataR2.toInt();

      //who repair the vehicle

      bool IsSeniorRepairingFirstLightVehicle = false;
      bool IsSeniorRepairingSecondLightVehicle = false;

      bool IsSeniorRepairingFirstHeavyVehicle = false;
      bool IsSeniorRepairingSecondHeavyVehicle = false;

      bool IsJuniorRepairingFirstLightVehicle = false;
      bool IsJuniorRepairingSecondLightVehicle = false;

      bool IsJuniorRepairingFirstHeavyVehicle = false;
      bool IsJuniorRepairingSecondHeavyVehicle = false;





      for (int ii = 0; ii < modelingTime; ii++)
      {
          //////

          /////

          // process the queue
          while(!myQueueOfBrokenCars.empty())
          {
             // check if the car is HeavyVehicle
             if (myQueueOfBrokenCars.front()->getWeight())
             {
                 // check what the number of car is (first or second)
                 numberOfCar =  myQueueOfBrokenCars.front()->getNumber();

                 myQueueOfBrokenCars.pop();

                 // It is firstHeavyVehicle
                 if (numberOfCar == 1 )
                 {
                     if(MechanicHeavyVehicle->getStatus())
                     {
                         //send firstHeavyCar to repair by mechanicHeavyVehicle
                         MechanicHeavyVehicle->changeStatusBusyOrNot();
                         myQueueOfCarsReadyToRepair.push(FirstHeavyCar);
                         myQueueOfMechanicsReadyToRepair.push(MechanicHeavyVehicle);

                     }

                     else if(MechanicSenior->getStatus())
                     {
                         //send firstHeavyCar to repair by mechanicSenior
                         MechanicSenior->changeStatusBusyOrNot();
                         myQueueOfCarsReadyToRepair.push(FirstHeavyCar);
                         myQueueOfMechanicsReadyToRepair.push(MechanicSenior);

                     }

                     // All Mechanics are busy, so we have to send it at the first position of new checkeQueue
                     else
                     {
                         myQueueOfCheckedBrokenCars.push(FirstHeavyCar);
                     }
                 }

                 // It is secondHeavyVehicle

                 if (numberOfCar == 0 )
                 {
                     if(MechanicHeavyVehicle->getStatus())
                     {
                         //send secondHeavyCar to repair by mechanicHeavyVehicle
                         MechanicHeavyVehicle->changeStatusBusyOrNot();
                         myQueueOfCarsReadyToRepair.push(SecondHeavyCar);
                         myQueueOfMechanicsReadyToRepair.push(MechanicHeavyVehicle);

                     }

                     else if(MechanicSenior->getStatus())
                     {
                         //send firstLightCar to repair by mechanicSenior
                         MechanicSenior->changeStatusBusyOrNot();
                         myQueueOfCarsReadyToRepair.push(SecondHeavyCar);
                         myQueueOfMechanicsReadyToRepair.push(MechanicHeavyVehicle);

                     }

                     // All Mechanics are busy, so we have to send it to the checkedQueue
                     else
                     {
                         myQueueOfCheckedBrokenCars.push(SecondHeavyCar);
                     }

                 }

             }


              // check if the car is LightVehicle
             if (!myQueueOfBrokenCars.empty() && !myQueueOfBrokenCars.front()->getWeight())
             {
                 // check what the number of car is (first or second)
                 numberOfCar =  myQueueOfBrokenCars.front()->getNumber();

                 myQueueOfBrokenCars.pop();

                 // It is firstLightVehicle
                 if (numberOfCar == 1 )
                 {
                     if(MechanicLightVehicle->getStatus())
                     {
                         //send firstLightCar to repair by mechanicLightVehicle
                         MechanicLightVehicle->changeStatusBusyOrNot();
                         myQueueOfCarsReadyToRepair.push(FirstLightCar);
                         myQueueOfMechanicsReadyToRepair.push(MechanicLightVehicle);

                     }

                     else if(MechanicSenior->getStatus())
                     {
                         //send firstLightCar to repair by mechanicSenior
                         MechanicSenior->changeStatusBusyOrNot();
                         myQueueOfCarsReadyToRepair.push(FirstLightCar);
                         myQueueOfMechanicsReadyToRepair.push(MechanicSenior);


                     }

                     // All Mechanics are busy, so we have to send it to the checkedQueue
                     else
                     {
                         myQueueOfCheckedBrokenCars.push(FirstLightCar);
                     }
                 }

                 // It is secondLightVehicle

                 if (numberOfCar == 0 )
                 {
                     if(MechanicLightVehicle->getStatus())
                     {
                         //send secondLightCar to repair by mechanicLightVehicle
                         MechanicLightVehicle->changeStatusBusyOrNot();
                         myQueueOfCarsReadyToRepair.push(SecondLightCar);
                         myQueueOfMechanicsReadyToRepair.push(MechanicLightVehicle);

                     }

                     else if(MechanicSenior->getStatus())
                     {
                         //send secondLightCar to repair by mechanicSenior
                         MechanicSenior->changeStatusBusyOrNot();
                         myQueueOfCarsReadyToRepair.push(SecondLightCar);
                         myQueueOfMechanicsReadyToRepair.push(MechanicSenior);

                     }

                     // All Mechanics are busy, so we have to send it to the checkedQueue
                     else
                     {
                         myQueueOfCheckedBrokenCars.push(SecondLightCar);
                     }

                 }

             }
          }
          // end of the queue`s processing

          if(FirstLightCar->getType())
          {

              // Let`s spin the drum
              randValue = (double)(rand())/RAND_MAX;
              if(randValue < exp1Vera)
              {
                  FirstLightCar->changeStatus();
                  countOfCrashesOfLightCar1++;

                  this->printLogInfo(Qcout);
                  Qcout << "\033[35mMessage from model: \033[0m";
                  Qcout << "\033[31mFirstLightCar has been already broken\033[0m\n";
                  Qcout.flush();


                  if(MechanicLightVehicle->getStatus())
                  {
                      //send firstLightCar to repair by mechanicLightVehicle
                      MechanicLightVehicle->changeStatusBusyOrNot();
                      myQueueOfCarsReadyToRepair.push(FirstLightCar);
                      myQueueOfMechanicsReadyToRepair.push(MechanicLightVehicle);

                  }

                  else if(MechanicSenior->getStatus())
                  {
                      //send firstLightCar to repair by mechanicSenior
                      MechanicSenior->changeStatusBusyOrNot();
                      myQueueOfCarsReadyToRepair.push(FirstLightCar);
                      myQueueOfMechanicsReadyToRepair.push(MechanicSenior);


                  }

                  // All Mechanics are busy, so we have to send it to the checkedQueue
                  else
                  {
                      myQueueOfCheckedBrokenCars.push(FirstLightCar);
                  }
              }
          }

          if(SecondLightCar->getType())
          {

              // Let`s spin the drum
              randValue = (double)(rand())/RAND_MAX;
              if(randValue < exp1Vera)
              {
                  SecondLightCar->changeStatus();
                  countOfCrashesOfLightCar2++;

                  this->printLogInfo(Qcout);
                  Qcout << "\033[35mMessage from model: \033[0m";
                  Qcout << "\033[31mSecondLightCar has been already broken\033[0m\n";
                  Qcout.flush();


                  if(MechanicLightVehicle->getStatus())
                  {
                      //send secondLightCar to repair by mechanicLightVehicle
                      MechanicLightVehicle->changeStatusBusyOrNot();
                      myQueueOfCarsReadyToRepair.push(SecondLightCar);
                      myQueueOfMechanicsReadyToRepair.push(MechanicLightVehicle);

                  }

                  else if(MechanicSenior->getStatus())
                  {
                      //send secondLightCar to repair by mechanicSenior
                      MechanicSenior->changeStatusBusyOrNot();
                      myQueueOfCarsReadyToRepair.push(SecondLightCar);
                      myQueueOfMechanicsReadyToRepair.push(MechanicSenior);

                  }

                  // All Mechanics are busy, so we have to send it to the checkedQueue
                  else
                  {
                      myQueueOfCheckedBrokenCars.push(SecondLightCar);
                  }
              }
          }

          if(FirstHeavyCar->getType())
          {

              // Let`s spin the drum
              randValue = (double)(rand())/RAND_MAX;
              if(randValue < exp2Vera)
              {
                  FirstHeavyCar->changeStatus();
                  countOfCrashesOfHeavyCar1++;

                  this->printLogInfo(Qcout);
                  Qcout << "\033[35mMessage from model: \033[0m";
                  Qcout << "\033[31mFirstHeavyCar has been already broken\033[0m\n";
                  Qcout.flush();
                  theTimeOfCrashesFromModeling.push_back(ii);



                  if(MechanicHeavyVehicle->getStatus())
                  {
                      //send firstHeavyCar to repair by mechanicHeavyVehicle
                      MechanicHeavyVehicle->changeStatusBusyOrNot();
                      myQueueOfCarsReadyToRepair.push(FirstHeavyCar);
                      myQueueOfMechanicsReadyToRepair.push(MechanicHeavyVehicle);

                  }

                  else if(MechanicSenior->getStatus())
                  {
                      //send firstHeavyCar to repair by mechanicSenior
                      MechanicSenior->changeStatusBusyOrNot();
                      myQueueOfCarsReadyToRepair.push(FirstHeavyCar);
                      myQueueOfMechanicsReadyToRepair.push(MechanicSenior);

                  }

                  // All Mechanics are busy, so we have to send it at the first position of new checkeQueue
                  else
                  {
                      myQueueOfCheckedBrokenCars.push(FirstHeavyCar);
                  }

               }
          }

          if(SecondHeavyCar->getType())
          {

              // Let`s spin the drum
              randValue = (double)(rand())/RAND_MAX;
              if(randValue < exp2Vera)
              {
                  SecondHeavyCar->changeStatus();
                  countOfCrashesOfHeavyCar2++;

                  this->printLogInfo(Qcout);
                  Qcout << "\033[35mMessage from model: \033[0m";
                  Qcout << "\033[31mSecondHeavyCar has been already broken\033[0m\n";
                  Qcout.flush();
                  theTimeOfCrashesFromModeling.push_back(ii);



                  if(MechanicHeavyVehicle->getStatus())
                  {
                      //send secondHeavyCar to repair by mechanicHeavyVehicle
                      MechanicHeavyVehicle->changeStatusBusyOrNot();
                      myQueueOfCarsReadyToRepair.push(SecondHeavyCar);
                      myQueueOfMechanicsReadyToRepair.push(MechanicHeavyVehicle);

                  }

                  else if(MechanicSenior->getStatus())
                  {
                      //send firstLightCar to repair by mechanicSenior
                      MechanicSenior->changeStatusBusyOrNot();
                      myQueueOfCarsReadyToRepair.push(SecondHeavyCar);
                      myQueueOfMechanicsReadyToRepair.push(MechanicSenior);

                  }

                  // All Mechanics are busy, so we have to send it to the checkedQueue
                  else
                  {
                      myQueueOfCheckedBrokenCars.push(SecondHeavyCar);
                  }
              }
          }

          while(!myQueueOfCarsReadyToRepair.empty())
          {
              //the time to start repairing


              //first light vehicle
              if(timeInRepairLightCar1 == 0 && !myQueueOfCarsReadyToRepair.front()->getWeight() && myQueueOfCarsReadyToRepair.front()->getNumber())
              {
                  if(myQueueOfMechanicsReadyToRepair.front()->isSenior())
                  {

                      this->printLogInfo(Qcout);
                      Qcout << "\033[35mMessage from model: \033[0m";
                      Qcout << QString::fromStdString(FirstLightCar->repair());
                      Qcout << "\n";
                      Qcout.flush();



                      IsSeniorRepairingFirstLightVehicle = true;

                  }
                  else
                  {

                      this->printLogInfo(Qcout);
                      Qcout << "\033[35mMessage from model: \033[0m";
                      Qcout << QString::fromStdString(FirstLightCar->repair());
                      Qcout << "\n";
                      Qcout.flush();


                      IsJuniorRepairingFirstLightVehicle = true;
                  }

                  myQueueOfCarsReadyToRepair.pop();
                  myQueueOfMechanicsReadyToRepair.pop();
              }

              //second light vehicle
              if(timeInRepairLightCar2 == 0 && !myQueueOfCarsReadyToRepair.empty() && !myQueueOfCarsReadyToRepair.front()->getWeight() && !myQueueOfCarsReadyToRepair.front()->getNumber())
              {
                  if(myQueueOfMechanicsReadyToRepair.front()->isSenior())
                  {

                      this->printLogInfo(Qcout);
                      Qcout << "\033[35mMessage from model: \033[0m";
                      Qcout << QString::fromStdString(SecondLightCar->repair());
                      Qcout << "\n";
                      Qcout.flush();

                      IsSeniorRepairingSecondLightVehicle = true;

                  }
                  else
                  {

                      this->printLogInfo(Qcout);
                      Qcout << "\033[35mMessage from model: \033[0m";
                      Qcout << QString::fromStdString(SecondLightCar->repair());
                      Qcout << "\n";
                      Qcout.flush();


                      IsJuniorRepairingSecondLightVehicle = true;
                  }

                  myQueueOfCarsReadyToRepair.pop();
                  myQueueOfMechanicsReadyToRepair.pop();
              }

              //first heavy vehicle
              if(timeInRepairHeavyCar1 == 0 && !myQueueOfCarsReadyToRepair.empty() && myQueueOfCarsReadyToRepair.front()->getWeight() && myQueueOfCarsReadyToRepair.front()->getNumber())
              {
                  if(myQueueOfMechanicsReadyToRepair.front()->isSenior())
                  {

                      this->printLogInfo(Qcout);
                      Qcout << "\033[35mMessage from model: \033[0m";
                      Qcout << QString::fromStdString(FirstHeavyCar->repair());
                      Qcout << "\n";
                      Qcout.flush();


                      IsSeniorRepairingFirstHeavyVehicle = true;

                  }
                  else
                  {
                      this->printLogInfo(Qcout);
                      Qcout << "\033[35mMessage from model: \033[0m";
                      Qcout << QString::fromStdString(FirstHeavyCar->repair());
                      Qcout << "\n";
                      Qcout.flush();

                      IsJuniorRepairingFirstHeavyVehicle = true;
                  }

                  myQueueOfCarsReadyToRepair.pop();
                  myQueueOfMechanicsReadyToRepair.pop();
              }

              //second heavy vehicle
              if(timeInRepairHeavyCar2 == 0 && !myQueueOfCarsReadyToRepair.empty() && myQueueOfCarsReadyToRepair.front()->getWeight() && !myQueueOfCarsReadyToRepair.front()->getNumber())
              {
                  if(myQueueOfMechanicsReadyToRepair.front()->isSenior())
                  {
                      this->printLogInfo(Qcout);
                      Qcout << "\033[35mMessage from model: \033[0m";
                      Qcout << QString::fromStdString(SecondHeavyCar->repair());
                      Qcout << "\n";
                      Qcout.flush();


                      IsSeniorRepairingSecondHeavyVehicle = true;

                  }
                  else
                  {
                      this->printLogInfo(Qcout);
                      Qcout << "\033[35mMessage from model: \033[0m";
                      Qcout << QString::fromStdString(SecondHeavyCar->repair());
                      Qcout << "\n";
                      Qcout.flush();


                      IsJuniorRepairingSecondHeavyVehicle = true;
                  }

                  myQueueOfCarsReadyToRepair.pop();
                  myQueueOfMechanicsReadyToRepair.pop();


              }

           }

          //continue repairing

              sleep(1);

              if(FirstLightCar->getTypeInRepairOrNot()) timeInRepairLightCar1++;
              if(SecondLightCar->getTypeInRepairOrNot()) timeInRepairLightCar2++;
              if(FirstHeavyCar->getTypeInRepairOrNot()) timeInRepairHeavyCar1++;
              if(SecondHeavyCar->getTypeInRepairOrNot()) timeInRepairHeavyCar2++;

          // one  unit time ago



              while(!myQueueOfCheckedBrokenCars.empty())
              {
                  myQueueOfBrokenCars.push(myQueueOfCheckedBrokenCars.front());
                  myQueueOfCheckedBrokenCars.pop();
              }

              //finish the repairing
              if(timeInRepairLightCar1 == timeToRepairLightCar && FirstLightCar->getTypeInRepairOrNot())
              {
                  FirstLightCar->changeStatusInRepairOrNot();
                  FirstLightCar->changeStatus();
                  if (IsSeniorRepairingFirstLightVehicle)
                  {
                      MechanicSenior->changeStatusBusyOrNot();
                     IsSeniorRepairingFirstLightVehicle = false;
                  }

                  else
                  {
                      MechanicLightVehicle->changeStatusBusyOrNot();
                      IsJuniorRepairingFirstLightVehicle = false;
                  }
                  timeInRepairLightCar1 = 0;
                  this->printLogInfo(Qcout);
                  Qcout << "\033[35mMessage from model: \033[0m";
                  Qcout << "\033[32mFirstLightCar has already repaired \033[0m\n";
                  Qcout.flush();
              }
              if(timeInRepairLightCar2 == timeToRepairLightCar && SecondLightCar->getTypeInRepairOrNot())
              {
                  SecondLightCar->changeStatusInRepairOrNot();
                  SecondLightCar->changeStatus();
                  if (IsSeniorRepairingSecondLightVehicle)
                  {
                      MechanicSenior->changeStatusBusyOrNot();
                     IsSeniorRepairingSecondLightVehicle = false;
                  }

                  else
                  {
                      MechanicLightVehicle->changeStatusBusyOrNot();
                      IsJuniorRepairingSecondLightVehicle = false;
                  }
                  timeInRepairLightCar2 = 0;

                  this->printLogInfo(Qcout);
                  Qcout << "\033[35mMessage from model: \033[0m";
                  Qcout << "\033[32mSecondLightCar has already repaired\033[0m\n";
                  Qcout.flush();
              }
              if(timeInRepairHeavyCar1 == timeToRepairHeavyCar && FirstHeavyCar->getTypeInRepairOrNot())
              {
                  FirstHeavyCar->changeStatusInRepairOrNot();
                  FirstHeavyCar->changeStatus();
                  if (IsSeniorRepairingFirstHeavyVehicle)
                  {
                      MechanicSenior->changeStatusBusyOrNot();
                     IsSeniorRepairingFirstHeavyVehicle = false;
                  }

                  else
                  {
                      MechanicHeavyVehicle->changeStatusBusyOrNot();
                      IsJuniorRepairingFirstHeavyVehicle = false;
                  }

                  timeInRepairHeavyCar1 = 0;

                  this->printLogInfo(Qcout);
                  Qcout << "\033[35mMessage from model: \033[0m";
                  Qcout << "\033[32mFirstHeavyCar has already repaired\033[0m\n";
                  Qcout.flush();
              }
              if(timeInRepairHeavyCar2 == timeToRepairHeavyCar && SecondHeavyCar->getTypeInRepairOrNot())
              {
                  SecondHeavyCar->changeStatusInRepairOrNot();
                  SecondHeavyCar->changeStatus();
                  if (IsSeniorRepairingSecondHeavyVehicle)
                  {
                      MechanicSenior->changeStatusBusyOrNot();
                     IsSeniorRepairingSecondHeavyVehicle = false;
                  }

                  else
                  {
                      MechanicHeavyVehicle->changeStatusBusyOrNot();
                      IsJuniorRepairingSecondHeavyVehicle = false;
                  }

                  timeInRepairHeavyCar2 = 0;

                  this->printLogInfo(Qcout);
                  Qcout << "\033[35mMessage from model: \033[0m";
                  Qcout << "\033[32mFirstLightCar has already repaired\033[0m\n";
                  Qcout.flush();
              }


      ////////////////////
              //checking the pressed pushButton

              //
              //transmit
               //modify
              dataToSend->intStatusInfoMechanicSenior = QString::number(MechanicSenior->getStatus());
              dataToSend->intStatusInfoMechanicLightVehicle = QString::number(MechanicLightVehicle->getStatus());
              dataToSend->intStatusInfoMechanicHeavyVehicle = QString::number(MechanicHeavyVehicle->getStatus());

              dataToSend->intCountFirstLightVehicle = QString::number(countOfCrashesOfLightCar1);
              dataToSend->intCountSecondLightVehicle = QString::number(countOfCrashesOfLightCar2);

              dataToSend->intCountFirstHeavyVehicle = QString::number(countOfCrashesOfHeavyCar1);
              dataToSend->intCountSecondHeavyVehicle = QString::number(countOfCrashesOfHeavyCar2);

              dataToSend->intStatusFirstLightVehicle = QString::number(FirstLightCar->getType());
              dataToSend->intStatusSecondLightVehicle = QString::number(SecondLightCar->getType());
              dataToSend->intStatusFirstHeavyVehicle = QString::number(FirstHeavyCar->getType());
              dataToSend->intStatusSecondHeavyVehicle = QString::number(SecondHeavyCar->getType());

              dataToSend->intInRepairOrNotFirstLightVehicle = QString::number(FirstLightCar->getTypeInRepairOrNot());
              dataToSend->intInRepairOrNotSecondLightVehicle = QString::number(SecondLightCar->getTypeInRepairOrNot());
              dataToSend->intInRepairOrNotFirstHeavyVehicle = QString::number(FirstHeavyCar->getTypeInRepairOrNot());
              dataToSend->intInRepairOrNotSecondHeavyVehicle = QString::number(SecondHeavyCar->getTypeInRepairOrNot());
              TStatistics statistics(theTimeOfCrashesFromModeling);
              dataToSend->intExpectedValue = QString::number(statistics.expectedValue());
              dataToSend->intStandardDeviation = QString::number(statistics.standardDeviation());
              sendInfoToClient(dataToSend);

      }


      //


  /////////////////////////////
          this->printLogInfo(Qcout);
          Qcout << "End of modelling\n";
          Qcout << "countOfCrashesOfLightCar1 = " << countOfCrashesOfLightCar1 << "\n";
          Qcout << "countOfCrashesOfLightCar2 = " << countOfCrashesOfLightCar2 << "\n";
          Qcout << "countOfCrashesOfHeavyCar1 = " << countOfCrashesOfHeavyCar1 << "\n";
          Qcout << "countOfCrashesOfHeavyCar2 = " << countOfCrashesOfHeavyCar2 << "\n";

          Qcout << "timeInRepairLightCar1  = " << timeInRepairLightCar1 << "\n";
          Qcout << "timeInRepairLightCar1  = " << timeInRepairLightCar2 << "\n";
          Qcout << "timeInRepairHeavyCar1  = " << timeInRepairHeavyCar1 << "\n";
          Qcout << "timeInRepairHeavyCar2  = " << timeInRepairHeavyCar2 << "\n";

          TStatistics statistics(theTimeOfCrashesFromModeling);
          Qcout << "Expected value  = " << statistics.expectedValue() << "\n";
          Qcout << "Standard Deviation  = " << statistics.standardDeviation() << "\n";




          Qcout.flush();






           delete MechanicSenior;
           delete MechanicLightVehicle;
           delete FirstLightCar;
           delete SecondLightCar;
           delete FirstHeavyCar;
           delete SecondHeavyCar;
           delete dataToSend;


}


void TApplication::sendInfoToClient(TModelMessage* dataToSend)
{
    QByteArray arr;
    arr.append(QByteArray().setNum(dataToSend->intStatusInfoMechanicSenior.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intStatusInfoMechanicLightVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intStatusInfoMechanicHeavyVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intCountFirstLightVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intCountSecondLightVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intCountFirstHeavyVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intCountSecondHeavyVehicle.toInt()));
    arr.append(";");

    arr.append(QByteArray().setNum(dataToSend->intStatusFirstLightVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intStatusSecondLightVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intStatusFirstHeavyVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intStatusSecondHeavyVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intInRepairOrNotFirstLightVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intInRepairOrNotSecondLightVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intInRepairOrNotFirstHeavyVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intInRepairOrNotSecondHeavyVehicle.toInt()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intExpectedValue.toDouble()));
    arr.append(";");
    arr.append(QByteArray().setNum(dataToSend->intStandardDeviation.toDouble()));
    emit toCommunicator(arr);
}

