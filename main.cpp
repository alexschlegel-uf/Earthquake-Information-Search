#include <iostream>
#include <vector>
#include <string>
#include <exception>

#include "csv.h"
#include "Earthquake.h"
#include "Earthquakesort.h"
#include "Searches/Fibonacci.h"

int main()
{
    // Fibonacci Search works for both strings and ints, so make sure you use a template so that both work
    // On the other hand, Interpolation Search only works for ints, so when making the ui, lock string options when Interp is selected,
    // describing with some text at the bottom or something that it has a weakness of not working for strings.
    std::vector<Earthquake> earthquakes;

    // Load the CSV file into the vector of Earthquake structs
    io::CSVReader<16,io::trim_chars<' ', '\t'>,io::double_quote_escape<',', '"'>> in("Data/earthquakes.csv");
    in.read_header(io::ignore_extra_column, 
        "id", "impact.gap", "impact.magnitude", 
        "impact.significance", "location.depth", 
        "location.distance", "location.latitude", 
        "location.longitude", "location.name", 
        "time.day", "time.epoch", "time.hour", 
        "time.minute", "time.month", "time.second", "time.year");

    std::string id, locationName;
    double impactGap, impactMagnitude, locationDepth, locationDistance, locationLatitude, locationLongitude;
    int impactSignifcance, timeDay, timeHour, timeMinute, timeMonth, timeSecond, timeYear;
    long long timeEpoch;

    while (in.read_row(id, impactGap, impactMagnitude, impactSignifcance, locationDepth, 
        locationDistance, locationLatitude, locationLongitude, locationName, timeDay, timeEpoch, 
        timeHour, timeMinute, timeMonth, timeSecond, timeYear)) {
            Earthquake eq;
            eq.id = id;
            eq.impactGap = impactGap;
            eq.impactMagnitude = impactMagnitude;
            eq.impactSignifcance = impactSignifcance;
            eq.locationDepth = locationDepth;
            eq.locationDistance = locationDistance;
            eq.locationLatitude = locationLatitude;
            eq.locationLongitude = locationLongitude;
            eq.locationName = locationName;
            eq.timeDay = timeDay;
            eq.timeEpoch = timeEpoch;
            eq.timeHour = timeHour;
            eq.timeMinute = timeMinute;
            eq.timeMonth = timeMonth;
            eq.timeSecond = timeSecond;
            eq.timeYear = timeYear;
            earthquakes.push_back(eq);
    }
    
    std::cout << "Loaded " << earthquakes.size() << " earthquakes from the CSV file." << std::endl;

    /* to use fibonnaci sort, first sort the vector by 'inforation'(i.e. id, impactMagnitude, locationName,etc) by:
    earthquakeSort(earthquakes, &Earthquake::'information');
    then choose a target 'information' to search for
    to run the Fibonacci search targeting the 'information' field:
    target = whatever target you want for 'information'
    FibResult res = FibonacciSearch::search(earthquakes, target, [](const Earthquake& eq) {return eq.'information';});
    it will return a FibResult struct (res) that has the index in which the target was found or -1 if no target found
    for index and index of closest element below and above target or -1 for below and above
*/
    return 0;
}