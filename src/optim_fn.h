#ifndef optim_fn_HPP
#define optim_fn_HPP

#include "NumCpp.hpp"

struct SavedInformation {
    std::vector<double> all_best_individuals;
    double fitness;
    int num_evaluation;

    SavedInformation(std::vector<double> abi, double f, int n_e) {
        all_best_individuals = abi;
        fitness = f;
        num_evaluation = n_e;
    }
};

double randint(double minN, double maxN) {
    return minN + rand() % static_cast<int>(maxN + 1.0 - minN);
}
double fabs(double x) {
    return x < 0 ? -1.0 * x : x; 
}

namespace optim_fn {
    std::vector<SavedInformation> DifferentialEvolution(double (*test_function)(std::vector<double>), bool mutation, int dimension, const std::pair<double, double> bounds, double F_scale, double cross_prob, int popsize, int max_evals, int verbose) {
        /*
        Differential Evolution

        Returns:
        best_individual -- Returns best individual
        */
        int num_eval = 0;
        int generation_count = 0;

        const double bound_lower = bounds.first;
        const double bound_upper = bounds.second;
        const double diff = fabs(bound_lower - bound_upper);

        std::vector<std::vector<double>> population;
        std::vector<SavedInformation> all_best_results;
        
        // Initialize population
        for (int pop_idx = 0; pop_idx < popsize; ++pop_idx) {
            std::vector<double> tmp_pop;
            for (int dim = 0; dim < dimension; ++dim) {
                tmp_pop.push_back(bound_lower + diff * randint(bound_lower, bound_upper));
            }
            population.push_back(tmp_pop);
        }

        // Fitness evaluation
        int best_idx = -1; 
        int current_idx = 0;
        int64_t best_fitness = static_cast<int64_t>(1e17);
        std::vector<double> fitness;
        
        for (std::vector<double> ind : population) {
            double current_fitness = test_function(ind);
            ++num_eval;
            fitness.push_back(current_fitness);
            // Get best fitness individual index
            if (current_fitness < best_fitness) {
                best_fitness = current_fitness;
                best_idx = current_idx;
            }
            ++current_idx;
        }

        assert(best_idx != -1);

        // Save information from 1st generation
        std::vector<double> best_individual = population[best_idx];
        all_best_results.push_back(SavedInformation(best_individual, best_fitness, num_eval));

        // Evaluation process
        for (;;) {
            if (num_eval > max_evals) {
                break;
            }
            for (int i = 0; i < popsize; ++i) {
                // Mutation 
                nc::NdArray<double> mutant;
                if (mutation) {
                    std::vector<int> indexes;
                    for (int idx = 0; idx < popsize; ++idx) {
                        if (idx != i) {
                            indexes.push_back(idx);
                        }
                    }
                    nc::NdArray<int> random_choice = nc::random::choice(nc::NdArray<int>(indexes, true), 3, false);
                    nc::NdArray<double> a = nc::NdArray<double>(population[random_choice.at(0)]), b = nc::NdArray<double>(population[random_choice.at(1)]), c = nc::NdArray<double>(population[random_choice.at(2)]);
                    mutant = nc::clip(F_scale*(b - c) + a, bound_lower, bound_upper);
                }
                // Crossover
                nc::NdArray<double> uniform_crossover = nc::random::rand<double>(nc::Shape(1, dimension));
                std::vector<int> cross_points;
                for (double point : uniform_crossover) {
                    if (point < cross_prob) {
                        cross_points.push_back(1);
                    } else {
                        cross_points.push_back(0);
                    }
                }
                nc::NdArray<int> is_cross_points = nc::NdArray<int>(cross_points, true);
                if (!nc::any(is_cross_points).at(0)) {
                    cross_points[nc::random::randInt(0, dimension)] = 1;
                }

                // Offspring
                std::vector<double> trial;
                for (int idx = 0; idx < is_cross_points.size(); ++idx) {
                    if (is_cross_points[idx]) {
                        trial.push_back(mutant.at(idx));
                    }
                    else {
                        trial.push_back(population[i][idx]);
                    }
                }

                // Evaluate fitness
                double f = test_function(trial);
                ++num_eval;

                // Selection 
                if (f < fitness[i]) {
                    population[i] = trial;
                    fitness[i] = f;
                    if (f < fitness[best_idx]) {
                        best_individual = trial;
                        best_idx = i;
                    }
                }
            }
            
            if (verbose == 1) {
                std::cout << "#Generation: " << generation_count + 1 << "\t  ";
                std::cout << "Best individual: [";
                for (auto x : best_individual) {
                    std::cout << x << ",";
                }
                std::cout << "]\t";
                std::cout << "Fitness: " << 100 - fitness[best_idx] << "%\t  ";
                std::cout << "#Eval: " << num_eval << std::endl;
            }

            all_best_results.push_back(SavedInformation(best_individual, fitness[best_idx], num_eval));

            if (fitness[best_idx] < constant::eps) {
                break;
            }
            ++generation_count;
        }
        return all_best_results;
    }
    std::vector<SavedInformation> EvolutionStrategies(double (*test_function)(std::vector<double>), int dimension, const std::pair<double, double> bounds, double sigma_init, double c_increase, double c_decrease, int popsize, int max_evals, int verbose) {
        /*
        Evolution Strategies
        */

        int num_eval = 0;
        int generation_count = 0;
        
        double sigma = sigma_init;

        const double bound_lower = bounds.first;
        const double bound_upper = bounds.second;

        const double diff = fabs(bound_lower - bound_upper);

        std::vector<std::vector<double>> mu;
        std::vector<SavedInformation> all_best_results;
        
        // Initialize mu
        for (int mu_idx = 0; mu_idx < popsize; ++mu_idx) {
            std::vector<double> tmp_mu;
            for (int dim = 0; dim < dimension; ++dim) {
                tmp_mu.push_back(bound_lower + diff * randint(bound_lower, bound_upper));
            }
            mu.push_back(tmp_mu);
        }

        // Evaluate fitness of generation 0
        std::vector<double> mu_fitness;
        for (int mu_idx = 0; mu_idx < popsize; ++mu_idx) {
            mu_fitness.push_back(test_function(mu[mu_idx]));
            ++num_eval;
        }


        for (;;) {
            if (num_eval > max_evals)
                break;
            nc::NdArray<double> epsilon = nc::random::randN<double>(nc::Shape{static_cast<nc::uint32>(popsize), static_cast<nc::uint32>(dimension)});
            std::vector<double> offspring;
            for (int idx = 0; idx < mu.size(); ++idx) {
                offspring.push_back(mu[idx] + sigma * epsilon.at(idx)]);
            }
        }
        
        return all_best_results;
    }
}


#endif