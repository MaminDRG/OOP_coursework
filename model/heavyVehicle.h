#ifndef HEAVYVEHICLE_H
#define HEAVYVEHICLE_H
#include "car.h"

    class THeavyVehicle : public TCar
    {
    private:
        //const std::string type = "heavy";

    public:
        THeavyVehicle(void);
    std::string repair(void);

};

#endif // HEAVYVEHICLE_H
