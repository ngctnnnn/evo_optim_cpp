#define OPTIM_ENABLE_EIGEN_WRAPPERS
#include "optim.hpp"
#include "test_functions/Ackley.h"
#include <iostream>

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