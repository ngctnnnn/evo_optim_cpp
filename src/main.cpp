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

double (*test_fn)(std::vector<double>) = &Sphere;

int main (int argc, char **argv) {
    std::string test_function = argv[1];
    if (test_function == "Sphere") {
        double (*test_fn)(std::vector<double>) = &Sphere;
        bounds = {-32.678, 32.678};
    }
    else if (test_function == "Rastrigin") {
        double (*test_fn)(std::vector<double>) = &Rastrigin;
        bounds = {-5.12, 5.12};
    } 
    else {
        std::cout << "[Error] This test function is not yet implemented!\n";
        assert(1==2);
    }

    std::vector<SavedInformation> all_best_results = optim_fn::DifferentialEvolution(test_fn, mutation, dimension, bounds, F_scale, cross_prob, popsize, max_evals, verbose);
    
    return 0;
}