#include "lightVehicle.h"

TLightVehicle::TLightVehicle(void) : TCar ()
{
   weight = 0;
}

std::string TLightVehicle::repair()
{

    this->changeStatusInRepairOrNot();
    std::string message = "The light vehicle ";
    message.append(this->getNumber() ? "1" : "2");
    message.append("is being repaired ");
    message =  "\033[33m" + message + "\033[0m";
    return message;
}
