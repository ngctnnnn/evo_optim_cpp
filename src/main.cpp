#include "test_functions/test_fns.h"
#include "optim_fn.h"
#include <stdlib.h>
#include <functional>
#include <time.h>

bool mutation = 1;
std::pair<double, double> bounds = {-32.678, 32.678};
int dimension = 2;
double F_scale = 0.8;
double cross_prob = 0.7;
int popsize = 32;
int max_evals = static_cast<int>(1e4);
int verbose = 1;

int main (int argc, char **argv) {
    // auto test_function = Sphere;
    // std::function<double(std::vector<double>)> test_fn = Sphere;
    std::vector<SavedInformation> all_best_results = optim_fn::DifferentialEvolution(&Sphere, mutation, dimension, bounds, F_scale, cross_prob, popsize, max_evals, verbose);

    return 0;
}