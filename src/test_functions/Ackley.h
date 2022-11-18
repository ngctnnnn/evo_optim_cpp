#pragma once
#include "constant.h"

double Ackley(const Eigen::VectorXd& vals_inp, Eigen::VectorXd* grad_out, void* opt_data) {
    const double x = vals_inp(0);
    const double y = vals_inp(1);

    const double obj_val = 20 + std::exp(1) - 20*std::exp( -0.2*std::sqrt(0.5*(x*x + y*y)) ) - std::exp( 0.5*(std::cos(2 * constant::PI * x) + std::cos(2 * constant::PI * y)) );
            
    return obj_val;
}