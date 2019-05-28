#ifndef MECHANICSENIOR_H
#define MECHANICSENIOR_H

#include "lightVehicleMechanic.h"
#include "heavyVehicleMechanic.h"

class TMechanicSenior : public TLightVehicleMechanic, THeavyVehicleMechanic
{
public:
    TMechanicSenior();
    bool isSenior();
};

#endif // MECHANICSENIOR_H
