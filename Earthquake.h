#pragma once
#include <string>

struct Earthquake {
    std::string id;
    double impactGap;
    double impactMagnitude;
    int impactSignifcance;
    double locationDepth;
    double locationDistance;
    double locationLatitude;
    double locationLongitude;
    std::string locationName;
    int timeDay;
    long long timeEpoch;
    int timeHour;
    int timeMinute;
    int timeMonth;
    int timeSecond;
    int timeYear;
};