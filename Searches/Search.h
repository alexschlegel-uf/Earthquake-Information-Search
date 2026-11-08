#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "Interpolation.h"
#include "Fibonacci.h"
#include "../Earthquake.h"
#include "../EarthquakeSort.h"

template <typename T, typename Result>
void display(std::vector<Earthquake>& earthquakes, T Earthquake::*field, const std::string& fieldName, Result res, T find) {
    if (res.index != -1) {
        std::cout << "Found earthquake with " << fieldName << " " << find << " at index " << res.index << std::endl;
    } else {
        if (res.above != -1) {
            std::cout << "Earthquake with "<< fieldName << " " << doubleValue << " not found. Closest above is at index " << res.above 
            << " with value " << earthquakes[res.above].*field << std::endl;
        }
        if (res.below != -1) {
            std::cout << "Earthquake with " << fieldName << " " << doubleValue << " not found. Closest below is at index " << res.below 
            << " with value " << earthquakes[res.below].*field << std::endl;
        }
    }
}

template <typename T>
void search(std::vector<Earthquake>& earthquakes, T Earthquake::*field, const std::string& fieldName, int searchType) {
    earthquakeSort(earthquakes, field);
    T find;
    std::cout << "Enter a value for " << fieldName << ": ";
    std::cin >> find;

    switch(searchType) {
        case 1: {
            results res;
            res = interpolationSearch(earthquakes, field, find, 0, earthquakes.size()-1, res);
            display(earthquakes, field, fieldName, res, find);
            break;
        }
        case 2: {
            FibResult res = FibonacciSearch::search(earthquakes, find, [field](const Earthquake& quake) {return quake.*field;});
            display(earthquakes, field, fieldname, res, find);
            break;
        }
        case 3: {
            results res;
            res = interpolationSearch(earthquakes, field, find, 0, earthquakes.size()-1, res);
            std::cout << "\n--Interpolation Search Results--" << std::endl;
            display(earthquakes, field, fieldName, res, find);
            FibResult fibRes = FibonacciSearch::search(earthquakes, find, [field](const Earthquake& quake) {return quake.*field;});
            std::cout << "\n--Fibonacci Search Results--" << std::endl;
            display(earthquakes, field, fieldname, fibRes, find);
            break;
        }
        default: {
            std::cout << "Invalid Search Selection" << std::endl;
        }
    }
}

template <typename T>
void fiboStringSearch(std::vector<Earthquake>& earthquakes, T Earthquake::*field, const std::string& fieldName) {
    earthquakeSort(earthquakes, field);
    T find;
    std::cout << "Enter a value for " << fieldName << ": ";
    std::cin >> find;

    FibResult res = FibonacciSearch::search(earthquakes, find, [field](const Earthquake& quake) {return quake.*field;});
    display(earthquakes, field, fieldname, res, find);
}