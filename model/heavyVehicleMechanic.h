#ifndef HEAVYVEHICLEMECHANIC_H
#define HEAVYVEHICLEMECHANIC_H

#include "mechanic.h"

class THeavyVehicleMechanic : virtual public TMechanic
{
public:
    THeavyVehicleMechanic(void);
    void StartToRepairHeavyVehicle(TCar&);
    bool isSenior();

};

#endif // HEAVYVEHICLEMECHANIC_H
