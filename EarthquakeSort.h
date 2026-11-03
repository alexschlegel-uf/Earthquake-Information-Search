#pragma once

#include <algorithm>
#include <vector>
#include "Earthquake.h"

template <typename T>
void earthquakeSort(std::vector<Earthquake>& earthquakes, T Earthquake::*field) {
    std::sort(earthquakes.begin(), earthquakes.end(), [field](const Earthquake& a, const Earthquake& b) {
        return a.*field < b.*field;
    });
}