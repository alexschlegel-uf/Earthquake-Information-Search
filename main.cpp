#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

#include "csv.h"
#include "Earthquake.h"
#include "EarthquakeSort.h"
#include "Searches/Search.h"

int main()
{
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

    // Check to ensure the vector actually populated
    if (earthquakes.empty()) {
        std::cout << "Earthquakes failed to load. Exiting program." << std::endl;
        return 0;
    }
    std::cout << "Loaded " << earthquakes.size() << " earthquakes from the CSV file." << std::endl;

    // Prompt to get desired Search
    int searchType = 0;
    std::cout << "Note: Interpolation search does not support Strings. " <<
    "If choosing a string field, choosing 1 will skip them, and 3 will only return Fibonacci's results" << std::endl;
    std::cout << "Enter desired search: " << std::endl << "1. Interpolation" << std::endl << "2. Fibonacci" << std::endl << "3. Both" << std::endl;
    std::cin >> searchType;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Prompt the user to choose a field to sort and search by
    std::string choice = "";
    std::cout << "Choose a field to sort and search by:" << std::endl << "1. impactGap" << std::endl 
    << "2. impactMagnitude" << std::endl << "3. impactSignificance" << std::endl << "4. locationDepth" << std::endl
    << "5. locationDistance" << std::endl << "6. locationLatitude" << std::endl << "7. locationLongitude" << std::endl
    << "8. timeDay" << std::endl << "9. timeEpoch" << std::endl << "10. timeHour" << std::endl
    << "11. timeMinute" << std::endl << "12. timeMonth" << std::endl << "13. timeSecond" << std::endl << "14. timeYear" << std::endl
    << "15. ID (String)" << std::endl << "16. locationName (String)" << std::endl;
    std::cout << "Enter selections (1-16) seperated by spaces (15 - ID and 16 - locationName do not support Interpolation): ";
    std::getline(std::cin, choice);
    std::vector<int> choices;
    std::stringstream ss(choice);
    int c;
    while (ss >> c) {
        choices.push_back(c);
    }

    // For each choice, call search with relevant information
    for (auto i : choices) {
        switch (i) {
            case 1: {
                search(earthquakes, &Earthquake::impactGap, "Impact Gap", searchType);
                break;
            }
            case 2: {
                search(earthquakes, &Earthquake::impactMagnitude, "Impact Magnitude", searchType);
                break;
            }
            case 3: {
                search(earthquakes, &Earthquake::impactSignifcance, "Impact Significance", searchType);
                break;
            }
            case 4: {
                search(earthquakes, &Earthquake::locationDepth, "Location Depth", searchType);
                break;
            }
            case 5: {
                search(earthquakes, &Earthquake::locationDistance, "Location Distance", searchType);
                break;
            }
            case 6: {
                search(earthquakes, &Earthquake::locationLatitude, "Location Latitude", searchType);
                break;
            }
            case 7: {
                search(earthquakes, &Earthquake::locationLongitude, "Location Longitude", searchType);
                break;
            }
            case 8: {
                search(earthquakes, &Earthquake::timeDay, "Time Day", searchType);
                break;
            }
            case 9: {
                search(earthquakes, &Earthquake::timeEpoch, "Time Epoch", searchType);
                break;
            }
            case 10: {
                search(earthquakes, &Earthquake::timeHour, "Time Hour", searchType);
                break;
            }
            case 11: {
                search(earthquakes, &Earthquake::timeMinute, "Time Minute", searchType);
                break;
            }
            case 12: {
                search(earthquakes, &Earthquake::timeMonth, "Time Month", searchType);
                break;
            }
            case 13: {
                search(earthquakes, &Earthquake::timeSecond, "Time Second", searchType);
                break;
            }
            case 14: {
                search(earthquakes, &Earthquake::timeYear, "Time Year", searchType);
                break;
            }
            case 15: {
                if (searchType == 2 || searchType == 3) {
                    fiboStringSearch(earthquakes, &Earthquake::id, "ID");
                }
                break;
            }
            case 16: {
                if (searchType == 2 || searchType == 3) {
                    fiboStringSearch(earthquakes, &Earthquake::locationName, "Location Name");
                }
                break;
            }
            default:
                // For when a value not allowed is given
                std::cout << "Invalid choice: " << i << std::endl;
        }
    }
    return 0;
}