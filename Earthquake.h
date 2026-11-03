#pragma once
#include <string>

struct Earthquake {
    std::string id;
    double impactGap;
    double impactMagnitude;
    int impactSignifcance;
    double locationDepth;
    double locationLatitude;
    double locationLongitude;
    std::string locationName;
    int timeDay;
    int timeEpoch;
    int timeHour;
    int timeMinute;
    int timeMonth;
    int timeSecond;
    int timeYear;
};