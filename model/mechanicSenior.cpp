#include "mechanicSenior.h"

TMechanicSenior::TMechanicSenior() : TLightVehicleMechanic(), THeavyVehicleMechanic() {};

bool TMechanicSenior::isSenior()
{
    return true;
}
