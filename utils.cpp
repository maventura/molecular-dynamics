#include "utils.h"
double rand(double a, double b) {
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

bool in(const int n, const vector<int> v) {
    for (unsigned int i = 0; i < v.size(); ++i) {
        if (v[i] == n) {
            return true;
        }
    }
    return false;
}

