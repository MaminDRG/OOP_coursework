#include "tstatistics.h"
#include "cmath"
TStatistics::TStatistics(std::vector<int> thetimeOfCrashesFromModeling) : theTimeOfCrashes(thetimeOfCrashesFromModeling)
{
    if(theTimeOfCrashes.size() < 2) thePeriodsBetweenCrashes = {-1};
    else {
        int leftElem = 0;
        int rightElem = 0;

        for (unsigned int i = 0; i < theTimeOfCrashes.size() - 1;i++)
        {
            leftElem = theTimeOfCrashes[i];
            rightElem = theTimeOfCrashes[i + 1];
            thePeriodsBetweenCrashes.push_back(rightElem-leftElem);
        }
    }
};

double TStatistics::standardDeviation(void) const
{
    double expected = this->expectedValue();
    if (expected < 0) return -1.0;
    else {
        double sum = 0;
        for (unsigned int i = 0; i < thePeriodsBetweenCrashes.size(); i++)
        {
            sum += (thePeriodsBetweenCrashes[i] - expected) * (thePeriodsBetweenCrashes[i] - expected);
        }
            return sqrt(sum/static_cast<int>(thePeriodsBetweenCrashes.size() - 1 ));
         }

}

double TStatistics::expectedValue(void) const
{
    int sum = 0;
    if (thePeriodsBetweenCrashes.size() == 1 && thePeriodsBetweenCrashes[0] == -1) return -1.0;
    else {
        for (unsigned int i = 0; i < thePeriodsBetweenCrashes.size(); i++)
        {
             sum += thePeriodsBetweenCrashes[i];
        }
            return sum/static_cast<int>(thePeriodsBetweenCrashes.size());
        }
}
