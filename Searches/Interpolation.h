#pragma once
#include <vector>
#include "Earthquake.h"

template <typename T>
int interpolationSearch(const std::vector<Earthquake>& earthquakes, T Earthquake::*field, T find, int low, int high) {
    if (low <= high && low < earthquakes.size() && high < earthquakes.size() && 
    find >= earthquakes[low].*field && find <= earthquakes[high].*field) {
        if (find == earthquakes[low].*field) {
            return low; 
        } else if (find == earthquakes[high].*field) {
            return high; 
        } else if (earthquakes[high].*field == earthquakes[low].*field) {
            return -1;
        }
        int index = low + (int)((find - earthquakes[low].*field)*(high - low))/(earthquakes[high].*field - earthquakes[low].*field);
        if (earthquakes[index].*field == find) {
            return index; 
        }
        if (earthquakes[index].*field < find) {
            return interpolationSearch(earthquakes, field, find, index + 1, high);
        } else {
            return interpolationSearch(earthquakes, field, find, low, index - 1);
        }
    }
    return -1;
}