#pragma once
#include <string>

// Basic struct to hold the data for each earthquake, with each field corresponding to a column in the CSV file
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