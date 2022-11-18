#define OPTIM_ENABLE_EIGEN_WRAPPERS
#include "optim.hpp"
#include <iostream>

namespace constant {
    static double PI = 3.14159265358979323846264338327050;
}

double Ackley(const Eigen::VectorXd& vals_inp, Eigen::VectorXd* grad_out, void* opt_data) {
    const double x = vals_inp(0);
    const double y = vals_inp(1);

    const double obj_val = 20 + std::exp(1) - 20*std::exp( -0.2*std::sqrt(0.5*(x*x + y*y)) ) - std::exp( 0.5*(std::cos(2 * constant::PI * x) + std::cos(2 * constant::PI * y)) );
            
    return obj_val;
}

int main (int argc, char** argv) {
    Eigen::VectorXd x = 2.0 * Eigen::VectorXd::Ones(2); // initial values: (2,2)
        
    bool success = optim::de(x, Ackley, nullptr);
        
    if (success) {
        std::cout << "de: Ackley test completed successfully." << std::endl;
    } else {
        std::cout << "de: Ackley test completed unsuccessfully." << std::endl;
    }
        
    std::cout << "de: solution to Ackley test:\n" << x << std::endl;
        
    return 0;
}