#include "test_functions/test_fns.h"
#include "optim_fn.h"
#include <stdlib.h>
#include <functional>
#include <time.h>

bool mutation = 1;
std::pair<double, double> bounds;
int dimension = 2;
int verbose = 1;
int popsize = 32;
int max_evals = static_cast<int>(1e4);

double F_scale = 0.8;
double cross_prob = 0.7;

double sigma_init = 1.0;
double c_increase = 1.1;
double c_decrease = 0.6;

int main (int argc, char **argv) {
    std::string evolution_algorithm = argv[1];
    std::string test_function = argv[2];
    std::vector<SavedInformation> all_best_results;

    if (test_function == "Sphere") {
        bounds = {-32.678, 32.678};
        if (evolution_algorithm == "DE")
            all_best_results = optim_fn::DifferentialEvolution(&Sphere, mutation, dimension, bounds, F_scale, cross_prob, popsize, max_evals, verbose);
        else if (evolution_algorithm == "ES")
            all_best_results = optim_fn::EvolutionStrategies(&Sphere, dimension, bounds, sigma_init, c_increase, c_decrease, popsize, max_evals, verbose);
        else {
            std::cout << "[Error] This algorithm is not yet implemented!\n";
            assert(evolution_algorithm == "DE" || evolution_algorithm == "ES");
        }
    }
    else if (test_function == "Rastrigin") {
        bounds = {-5.12, 5.12};
        if (evolution_algorithm == "DE") 
            all_best_results = optim_fn::DifferentialEvolution(&Rastrigin, mutation, dimension, bounds, F_scale, cross_prob, popsize, max_evals, verbose);
        else if (evolution_algorithm == "ES")
            all_best_results = optim_fn::EvolutionStrategies(&Rastrigin, dimension, bounds, sigma_init, c_increase, c_decrease, popsize, max_evals, verbose);
        else {
            std::cout << "[Error] This algorithm is not yet implemented!\n";
            assert(evolution_algorithm == "DE" || evolution_algorithm == "ES");
        }
    } 
    else if (test_function == "Rosenbrock") {
        bounds = {-5, 10};
        if (evolution_algorithm == "DE")
            all_best_results = optim_fn::DifferentialEvolution(&Rosenbrock, mutation, dimension, bounds, F_scale, cross_prob, popsize, max_evals, verbose);
        else if (evolution_algorithm == "ES")
            all_best_results = optim_fn::EvolutionStrategies(&Rosenbrock, dimension, bounds, sigma_init, c_increase, c_decrease, popsize, max_evals, verbose);
        else {
            std::cout << "[Error] This algorithm is not yet implemented!\n";
            assert(evolution_algorithm == "DE" || evolution_algorithm == "ES");
        }
    }
    else {
        std::cout << "[Error] This test function is not yet implemented!\n";
        assert(test_function == "Sphere" || test_function == "Rosenbrock" || test_function == "Rastrigin");
    }
    return 0;
}