#ifndef LIGHTVEHICLE_H
#define LIGHTVEHICLE_H
#include "car.h"

class TLightVehicle : public TCar
{
    // const std::string type = "light";
public:


    TLightVehicle(void);
    //explicit TLightVehicle(int);
    std::string repair(void);


};

#endif // LIGHTVEHICLE_H
