#pragma once
#include <vector>
#include "Earthquake.h"

struct results {
    int index = -1;
    int below = -1;
    int above = -1;
};

template <typename T>
results interpolationSearch(const std::vector<Earthquake>& earthquakes, T Earthquake::*field, T find, int low, int high, results& res) {
    if (low > high) {
        res.below = high;
        res.above = low;
        return res;
    }
    if (find < earthquakes[low].*field) {
        res.above = low;
        return res;
    }
    if (find > earthquakes[high].*field) {
        res.below = high;
        return res;
    }
    if (low < earthquakes.size() && high < earthquakes.size()) {
        if (find == earthquakes[low].*field) {
            res.index = low;
            return res; 
        } else if (find == earthquakes[high].*field) {
            res.index = high;
            return res;
        } else if (earthquakes[high].*field == earthquakes[low].*field) {
            return res;
        }
        int interpIndex = low + (int)((find - earthquakes[low].*field)*(high - low))/(earthquakes[high].*field - earthquakes[low].*field);
        if (earthquakes[interpIndex].*field == find) {
            res.index = interpIndex;
            return res;
        }
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