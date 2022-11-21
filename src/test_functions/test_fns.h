#pragma once
#include "constant.h"
#include <cmath>
#include <vector>

double Sphere(std::vector<double> ind) {
    /*
    Sphere test function:
    f(x) = \sum_{i = 1}^d x_i^2
    s.t.,
    - x \in \left[-32.678, 32.678\right]^d
    */
    double obj_val = 0;
    for (double value : ind) {
        obj_val += value*value;
    }
    return obj_val;
}
double Rastrigin(std::vector<double> ind) {
    /*
    Rastrigin function
    f(x) = A + \sum_{i = 1}^d[x_i^2 - A \cos(2\pi x_i)]
    s.t.,
    - A = 10
    - x \in \left[-5.12, 5.12]\right]^d
    */
    
    double obj_val = 10 * ind.size();
    for (auto value : ind) {
        obj_val += (value*value) - (10 * std::cos(2*constant::PI*value));
    }
    return obj_val;
}