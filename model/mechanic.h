#ifndef MECHANIC_H
#define MECHANIC_H
#include "heavyVehicle.h"
#include "lightVehicle.h"

class TMechanic
{
    bool isReadyToWork;  // 1 = yes;
                         // 0 = no;
public:
    TMechanic();
    virtual ~TMechanic(void) = 0;
    virtual void changeStatusBusyOrNot(void);
    virtual bool getStatus(void) const;
    virtual bool isSenior(void) = 0;




};

#endif // MECHANIC_H
