#ifndef CAR_H
#define CAR_H

#include <string>
#include <unistd.h>

class TCar
{
protected:

    bool status;               // 1 = ready to work
                               // 0 = it was broken

    bool statusInRepairOrNot;  // 1 = inRepair;
                               // 0 = notinRepair;

    bool weight;                // 1 = Heavy;
                               // 0 = Light;

    bool number;                // 1 = first;
                                // 0 = second;

public:
    TCar();
    virtual std::string repair(void) = 0;
    virtual ~TCar(void) = 0;

    void changeStatus(void);
    void changeStatusInRepairOrNot(void);

    bool getType(void) const;
    bool getTypeInRepairOrNot(void) const;

    bool getWeight(void) const;

    bool getNumber(void) const;
    void setNumber(bool);

};

#endif // CAR_H
