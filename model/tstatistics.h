#ifndef TSTATISTICS_H
#define TSTATISTICS_H

#include <vector>

class TStatistics
{

    std::vector<int> theTimeOfCrashes;
    std::vector<int> thePeriodsBetweenCrashes;
public:
    explicit TStatistics(std::vector<int>);
    double expectedValue(void) const;
    double standardDeviation(void) const;

};


#endif // TSTATISTICS_H
