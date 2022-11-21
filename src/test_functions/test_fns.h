#pragma once
#include "constant.h"
#include <cmath>
#include <vector>
#include <iostream>

double sqr(double x) {
    return x * x;
}

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
double Rosenbrock(std::vector<double> ind) {
    /*
    Rosenbrock function
    f(x) = \sum_{i = 1}^{d - 1}\left[100(x_{i+1}-x_i^2) + (x_i - 1)^2\right]
    s.t., $x_i \in [-5;10]$
    */
    double sum = 0;
    for (int i = 0; i < ind.size() - 1; ++i) {
        sum += 100 * sqr(ind[i + 1] - ind[i]*ind[i]) + sqr(ind[i] - 1);
    }
    return sum;
}