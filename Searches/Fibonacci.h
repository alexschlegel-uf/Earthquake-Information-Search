#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <vector>
#include <algorithm>
#include "../Earthquake.h"
using namespace std;

struct FibResult {
    int index = -1;
    int below = -1;
    int above = -1;
};

class FibonacciSearch {

    public:
    template<typename T, typename KeyExtracter> //since what we searching can be int,string,...
    static FibResult search(const vector<Earthquake>& earthquakes, T target, KeyExtracter extracter) {
        FibResult res;
        int size = earthquakes.size();
        if (size == 0) {return res;}
        //getting fibonacci numbers
        int fib1 = 0, fib2 = 1;
        int fibMax = fib1 + fib2;
        //getting the smallest fib number that is greater or equal to size
        while (fibMax < size) {
            fib1 = fib2;
            fib2 = fibMax;
            fibMax = fib1 + fib2;
        }
        int offset = -1;

        while (fibMax > 1) {
            int i = min(offset + fib1, size - 1);
            T current = extracter(earthquakes[i]);

            if (current < target) {
                fibMax = fib2;
                fib2 = fib1;
                fib1 = fibMax - fib2;
                offset = i;
            }
            else if (current > target) {
                fibMax = fib1;
                fib2 = fib2 - fib1;
                fib1 = fibMax - fib2;
            }
            else {
                res.index = i;
                return res;
            }
        }
        if (fib2 && offset + 1 < size) {
            if (extracter(earthquakes[offset+1]) == target) {
                res.index = offset + 1;
                return res;
            }
        }

        res.below = offset;
        res.above = (offset + 1 < size) ? offset + 1 : -1;
        return res;
    }
};

#endif