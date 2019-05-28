#ifndef LIGHTVEHICLEMECHANIC_H
#define LIGHTVEHICLEMECHANIC_H
#include "mechanic.h"

class TLightVehicleMechanic : virtual public TMechanic
{
public:
    TLightVehicleMechanic();
    void StartToRepairLightVehicle(TCar&);
    bool isSenior();
};

#endif // LIGHTVEHICLEMECHANIC_H
