#include "car.h"

 TCar::TCar() : status(true), statusInRepairOrNot(false) {};
 TCar::~TCar() {};
 void TCar::changeStatus(void)
 {
     status = !status;
 }

 void TCar::changeStatusInRepairOrNot(void)
 {
     statusInRepairOrNot = !statusInRepairOrNot;
 }

 bool TCar::getType(void) const
 {
     return this->status;
 }

 bool TCar::getTypeInRepairOrNot(void) const
 {
     return this->statusInRepairOrNot;
 }

 bool TCar::getWeight(void) const
 {
     return this->weight;
 }


 bool TCar::getNumber(void) const
 {
     return this->number;
 }


 void TCar::setNumber(bool numberToSet)
 {
     number = numberToSet;
 }
