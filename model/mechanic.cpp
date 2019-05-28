#include "mechanic.h"

TMechanic::TMechanic() : isReadyToWork(true) {};
TMechanic::~TMechanic() {};
void TMechanic::changeStatusBusyOrNot(void)
{
    isReadyToWork = !isReadyToWork;
}

bool TMechanic::getStatus(void) const
{
    return this->isReadyToWork;
}
