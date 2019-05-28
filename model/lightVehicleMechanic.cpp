#include "lightVehicleMechanic.h"

TLightVehicleMechanic::TLightVehicleMechanic(void) : TMechanic (){};
void TLightVehicleMechanic::StartToRepairLightVehicle(TCar& vehicle)
{
    vehicle.repair();
    this->changeStatusBusyOrNot();
}

bool TLightVehicleMechanic::isSenior()
{
    return false;
}
