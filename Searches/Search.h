#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "Interpolation.h"
#include "Fibonacci.h"
#include "../Earthquake.h"
#include "../EarthquakeSort.h"

// Template to display results
template <typename T, typename Result>
void display(std::vector<Earthquake>& earthquakes, T Earthquake::*field, const std::string& fieldName, Result res, T find) {
    // If it exists, displays as such
    if (res.index != -1) {
        std::cout << "Found earthquake with " << fieldName << " " << find << " at index " << res.index << std::endl;
    } else {
        // Otherwise, displays the closest indexs and values if they exist
        if (res.above != -1) {
            std::cout << "Earthquake with "<< fieldName << " " << find << " not found. Closest above is at index " << res.above 
            << " with value " << earthquakes[res.above].*field << std::endl;
        }
        if (res.below != -1) {
            std::cout << "Earthquake with " << fieldName << " " << find << " not found. Closest below is at index " << res.below 
            << " with value " << earthquakes[res.below].*field << std::endl;
        }
    }
}

// Template for searching (ignoring strings)
template <typename T>
void search(std::vector<Earthquake>& earthquakes, T Earthquake::*field, const std::string& fieldName, int searchType) {
    // Sort and get value to find
    earthquakeSort(earthquakes, field);
    T find;
    std::cout << "Enter a value for " << fieldName << ": ";
    std::cin >> find;

    // Switch cases for each search option
    switch(searchType) {
        case 1: {
            // Interp Search, then display
            results res;
            res = interpolationSearch(earthquakes, field, find, 0, earthquakes.size()-1, res);
            display(earthquakes, field, fieldName, res, find);
            break;
        }
        case 2: {
            // Fib Search, then display
            FibResult res = FibonacciSearch::search(earthquakes, find, [field](const Earthquake& quake) {return quake.*field;});
            display(earthquakes, field, fieldName, res, find);
            break;
        }
        case 3: {
            // Do Interp Search, display, then Fib Search and display
            results res;
            res = interpolationSearch(earthquakes, field, find, 0, earthquakes.size()-1, res);
            std::cout << "\n--Interpolation Search Results--" << std::endl;
            display(earthquakes, field, fieldName, res, find);
            FibResult fibRes = FibonacciSearch::search(earthquakes, find, [field](const Earthquake& quake) {return quake.*field;});
            std::cout << "\n--Fibonacci Search Results--" << std::endl;
            display(earthquakes, field, fieldName, fibRes, find);
            break;
        }
        default: {
            std::cout << "Invalid Search Selection" << std::endl;
        }
    }
}

// Template for string searching, since only Fib Search supports it
template <typename T>
void fiboStringSearch(std::vector<Earthquake>& earthquakes, T Earthquake::*field, const std::string& fieldName) {
    // Sort and get value
    earthquakeSort(earthquakes, field);
    T find;
    std::cout << "Enter a value for " << fieldName << ": ";
    std::cin >> find;

    // Search and display
    FibResult res = FibonacciSearch::search(earthquakes, find, [field](const Earthquake& quake) {return quake.*field;});
    display(earthquakes, field, fieldName, res, find);
}