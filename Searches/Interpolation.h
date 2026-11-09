#pragma once
#include <vector>
#include "Earthquake.h"

// Struct to hold the results of the interpolation search
struct results {
    int index = -1;
    int below = -1;
    int above = -1;
};

// Template so that the 3 types, int, double, and long long, can be used for the interpolation search
template <typename T>
results interpolationSearch(const std::vector<Earthquake>& earthquakes, T Earthquake::*field, T find, int low, int high, results& res) {
    // If low > high, the index was never found, so return the above and below indexes
    if (low > high) {
        res.below = high;
        res.above = low;
        return res;
    }
    // If the value to find is less than the lowest possible value, return that lowest value, as it is the closest above
    if (find < earthquakes[low].*field) {
        res.above = low;
        return res;
    }
    // Same as above, but for if the value is greater than the highest possible value
    if (find > earthquakes[high].*field) {
        res.below = high;
        return res;
    }
    // Check if low and high are within bounds
    if (low < earthquakes.size() && high < earthquakes.size()) {
        // Check if the value to find is equal to the lowest or highest values, returning that value if so
        // If it is equal to neither, and the lowest and highest values are equal, return res (with its base values of -1 for index, above, and below)
        if (find == earthquakes[low].*field) {
            res.index = low;
            return res; 
        } else if (find == earthquakes[high].*field) {
            res.index = high;
            return res;
        } else if (earthquakes[high].*field == earthquakes[low].*field) {
            return res;
        }
        // Calculate the interpolation index
        int interpIndex = low + (int)(((find - earthquakes[low].*field)*(high - low))/(earthquakes[high].*field - earthquakes[low].*field));
        // Check if the value to find is equal to the value at the interpolation index, returning that index if so
        if (earthquakes[interpIndex].*field == find) {
            res.index = interpIndex;
            return res;
        }
        // If less, set low to the interpolation index + 1, and if greater, set high to the interpolation index - 1, and call the function again
        if (earthquakes[interpIndex].*field < find) {
            res.below = interpIndex;
            return interpolationSearch(earthquakes, field, find, interpIndex + 1, high, res);
        } else {
            res.above = interpIndex;
            return interpolationSearch(earthquakes, field, find, low, interpIndex - 1, res);
        }
    }
    return res;
}