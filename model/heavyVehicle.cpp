#include "heavyVehicle.h"

THeavyVehicle::THeavyVehicle(void) : TCar()
{
    weight = 1;
};
std::string THeavyVehicle::repair()
{
    this->changeStatusInRepairOrNot();
    std::string message = "The heavy vehicle ";
    message.append(this->getNumber() ? "1" : "2");
    message.append("is being repaired ");
    message =  "\033[33m" + message + "\033[0m";
    return message;
}


