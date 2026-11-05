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
    int intValue, index = 0;
    double doubleValue;
    long long longValue;
    results res;
    for (auto i : choices) {
        intValue = 0, index = 0, doubleValue = 0.0, longValue = 0;
        switch (i) {
            case 1:
                earthquakeSort(earthquakes, &Earthquake::impactGap);
                std::cout << "Enter a double value to search for in impactGap: ";
                std::cin >> doubleValue;
                res = interpolationSearch(earthquakes, &Earthquake::impactGap, doubleValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with impactGap " << doubleValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with impactGap " << doubleValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].impactGap << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with impactGap " << doubleValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].impactGap << std::endl;
                    }
                }
                break;
            case 2:
                earthquakeSort(earthquakes, &Earthquake::impactMagnitude);
                std::cout << "Enter a double value to search for in impactMagnitude: ";
                std::cin >> doubleValue;
                res = interpolationSearch(earthquakes, &Earthquake::impactMagnitude, doubleValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with impactMagnitude " << doubleValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with impactMagnitude " << doubleValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].impactMagnitude << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with impactMagnitude " << doubleValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].impactMagnitude << std::endl;
                    }
                }
                break;
            case 3:
                earthquakeSort(earthquakes, &Earthquake::impactSignifcance);
                std::cout << "Enter a integer value to search for in impactSignifcance: ";
                std::cin >> intValue;
                res = interpolationSearch(earthquakes, &Earthquake::impactSignifcance, intValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with impactSignifcance " << intValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with impactSignifcance " << intValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].impactSignifcance << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with impactSignifcance " << intValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].impactSignifcance << std::endl;
                    }
                }
                break;
            case 4:
                earthquakeSort(earthquakes, &Earthquake::locationDepth);
                std::cout << "Enter a double value to search for in locationDepth: ";
                std::cin >> doubleValue;
                res = interpolationSearch(earthquakes, &Earthquake::locationDepth, doubleValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with locationDepth " << doubleValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with locationDepth " << doubleValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].locationDepth << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with locationDepth " << doubleValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].locationDepth << std::endl;
                    }
                }
                break;
            case 5:
                earthquakeSort(earthquakes, &Earthquake::locationDistance);
                std::cout << "Enter a double value to search for in locationDistance: ";
                std::cin >> doubleValue;
                res = interpolationSearch(earthquakes, &Earthquake::locationDistance, doubleValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with locationDistance " << doubleValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with locationDistance " << doubleValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].locationDistance << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with locationDistance " << doubleValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].locationDistance << std::endl;
                    }
                }
                break;
            case 6:
                earthquakeSort(earthquakes, &Earthquake::locationLatitude);
                std::cout << "Enter a double value to search for in locationLatitude: ";
                std::cin >> doubleValue;
                res = interpolationSearch(earthquakes, &Earthquake::locationLatitude, doubleValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with locationLatitude " << doubleValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with locationLatitude " << doubleValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].locationLatitude << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with locationLatitude " << doubleValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].locationLatitude << std::endl;
                    }
                }
                break;
            case 7:
                earthquakeSort(earthquakes, &Earthquake::locationLongitude);
                std::cout << "Enter a double value to search for in locationLongitude: ";
                std::cin >> doubleValue;
                res = interpolationSearch(earthquakes, &Earthquake::locationLongitude, doubleValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with locationLongitude " << doubleValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with locationLongitude " << doubleValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].locationLongitude << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with locationLongitude " << doubleValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].locationLongitude << std::endl;
                    }
                }
                break;
            case 8:
                earthquakeSort(earthquakes, &Earthquake::timeDay);
                std::cout << "Enter a integer value to search for in timeDay: ";
                std::cin >> intValue;
                res = interpolationSearch(earthquakes, &Earthquake::timeDay, intValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with timeDay " << intValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with timeDay " << intValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].timeDay << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with timeDay " << intValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].timeDay << std::endl;
                    }
                }
                break;
            case 9:
                earthquakeSort(earthquakes, &Earthquake::timeEpoch);
                std::cout << "Enter a long long value to search for in timeEpoch: ";
                std::cin >> longValue;
                res = interpolationSearch(earthquakes, &Earthquake::timeEpoch, longValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with timeEpoch " << longValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with timeEpoch " << longValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].timeEpoch << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with timeEpoch " << longValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].timeEpoch << std::endl;
                    }
                }
                break;
            case 10:
                earthquakeSort(earthquakes, &Earthquake::timeHour);
                std::cout << "Enter a integer value to search for in timeHour: ";
                std::cin >> intValue;
                res = interpolationSearch(earthquakes, &Earthquake::timeHour, intValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with timeHour " << intValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with timeHour " << intValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].timeHour << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with timeHour " << intValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].timeHour << std::endl;
                    }
                }
                break;
            case 11:
                earthquakeSort(earthquakes, &Earthquake::timeMinute);
                std::cout << "Enter a integer value to search for in timeMinute: ";
                std::cin >> intValue;
                res = interpolationSearch(earthquakes, &Earthquake::timeMinute, intValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with timeMinute " << intValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with timeMinute " << intValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].timeMinute << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with timeMinute " << intValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].timeMinute << std::endl;
                    }
                }
                break;
            case 12:
                earthquakeSort(earthquakes, &Earthquake::timeMonth);
                std::cout << "Enter a integer value to search for in timeMonth: ";
                std::cin >> intValue;
                res = interpolationSearch(earthquakes, &Earthquake::timeMonth, intValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with timeMonth " << intValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with timeMonth " << intValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].timeMonth << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with timeMonth " << intValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].timeMonth << std::endl;
                    }
                }
                break;
            case 13:
                earthquakeSort(earthquakes, &Earthquake::timeSecond);
                std::cout << "Enter a integer value to search for in timeSecond: ";
                std::cin >> intValue;
                res = interpolationSearch(earthquakes, &Earthquake::timeSecond, intValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with timeSecond " << intValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with timeSecond " << intValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].timeSecond << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with timeSecond " << intValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].timeSecond << std::endl;
                    }
                }
                break;
            case 14:
                earthquakeSort(earthquakes, &Earthquake::timeYear);
                std::cout << "Enter a integer value to search for in timeYear: ";
                std::cin >> intValue;
                res = interpolationSearch(earthquakes, &Earthquake::timeYear, intValue, 0, earthquakes.size() - 1, res);
                if (res.index != -1) {
                    std::cout << "Found earthquake with timeYear " << intValue << " at index " << res.index << std::endl;
                } else {
                    if (res.above != -1) {
                        std::cout << "Earthquake with timeYear " << intValue << " not found. Closest above is at index " << res.above 
                        << " with value " << earthquakes[res.above].timeYear << std::endl;
                    }
                    if (res.below != -1) {
                        std::cout << "Earthquake with timeYear " << intValue << " not found. Closest below is at index " << res.below 
                        << " with value " << earthquakes[res.below].timeYear << std::endl;
                    }
                }
                break;
            default:
                std::cout << "Invalid choice: " << i << std::endl;
        }
    }
    return 0;
}