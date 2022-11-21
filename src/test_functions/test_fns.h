#pragma once
#include "constant.h"
#include <vector>

double Sphere(std::vector<double> ind) {
    /*
    Sphere test function:
    f(x) = \sum_{i = 1}^d x_i^2
    */
    double obj_val = 0;
    for (double value : ind) {
        obj_val += value*value;
    }
    return obj_val;
}

// double Ackley(const Eigen::VectorXd& vals_inp, Eigen::VectorXd* grad_out, void* opt_data) {
//     /*
//     Ackley test function
//     */
//     const double x = vals_inp(0);
//     const double y = vals_inp(1);

//     const double obj_val = 20 + std::exp(1) - 20*std::exp( -0.2*std::sqrt(0.5*(x*x + y*y)) ) - std::exp( 0.5*(std::cos(2 * constant::PI * x) + std::cos(2 * constant::PI * y)) );
            
//     return obj_val;
// }
