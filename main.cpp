#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "csv.h"
#include "Earthquake.h"
#include "EarthquakeSort.h"
#include "Searches/Interpolation.h"

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
    if (earthquakes.empty()) {
        std::cout << "Earthquakes failed to load. Exiting program." << std::endl;
        return 0;
    }
    std::cout << "Loaded " << earthquakes.size() << " earthquakes from the CSV file." << std::endl;
    std::string choice = "";
    std::cout << "Choose a field to sort and search by:" << std::endl << "1. impactGap" << std::endl 
    << "2. impactMagnitude" << std::endl << "3. impactSignificance" << std::endl << "4. locationDepth" << std::endl
    << "5. locationDistance" << std::endl << "6. locationLatitude" << std::endl << "7. locationLongitude" << std::endl
    << "8. timeDay" << std::endl << "9. timeEpoch" << std::endl << "10. timeHour" << std::endl
    << "11. timeMinute" << std::endl << "12. timeMonth" << std::endl << "13. timeSecond" << std::endl << "14. timeYear" << std::endl;
    std::cout << "Enter selections (1-14) seperated by spaces: ";
    std::getline(std::cin, choice);
    std::vector<int> choices;
    std::stringstream ss(choice);
    int c;
    while (ss >> c) {
        choices.push_back(c);
    }
    return 0;
}