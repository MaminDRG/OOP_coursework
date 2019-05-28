#include "heavyVehicleMechanic.h"

THeavyVehicleMechanic::THeavyVehicleMechanic() : TMechanic () {};

void THeavyVehicleMechanic::StartToRepairHeavyVehicle(TCar& vehicle)
{
    vehicle.repair();
    this->changeStatusBusyOrNot();
}

bool THeavyVehicleMechanic::isSenior()
{
    return false;
}

