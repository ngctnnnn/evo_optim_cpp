#include "test_functions/test_fns.h"
#include "optim_fn.h"
#include <stdlib.h>
#include <functional>
#include <time.h>

bool mutation = 1;
std::pair<double, double> bounds;
int dimension = 2;
double F_scale = 0.8;
double cross_prob = 0.7;
int popsize = 32;
int max_evals = static_cast<int>(1e4);
int verbose = 1;

int main (int argc, char **argv) {
    std::string test_function = argv[1];
    std::vector<SavedInformation> all_best_results;

    if (test_function == "Sphere") {
        bounds = {-32.678, 32.678};
        all_best_results = optim_fn::DifferentialEvolution(&Sphere, mutation, dimension, bounds, F_scale, cross_prob, popsize, max_evals, verbose);
    }
    else if (test_function == "Rastrigin") {
        bounds = {-5.12, 5.12};
        all_best_results = optim_fn::DifferentialEvolution(&Rastrigin, mutation, dimension, bounds, F_scale, cross_prob, popsize, max_evals, verbose);
    } 
    else if (test_function == "Rosenbrock") {
        bounds = {-5, 10};
        all_best_results = optim_fn::DifferentialEvolution(&Rosenbrock, mutation, dimension, bounds, F_scale, cross_prob, popsize, max_evals, verbose);
    }
    else {
        std::cout << "[Error] This test function is not yet implemented!\n";
        assert(1==2);
    }
    return 0;
}