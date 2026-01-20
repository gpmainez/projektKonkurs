//
// Created by pc on 02.01.2026.
//

#include "Individual.h"
#include <iostream>
#include <vector>
#include <algorithm>


Individual::Individual(const std::vector<int> &genotype, const Evaluator &eval)
    : genotype(genotype),
      evaluator(eval),
      groupsNum(eval.get_group_num()),
      fitness(0.0),
      fitnessCalculated(false) {
}

Individual::Individual(const Individual &other)
    : genotype(other.genotype),
      groupsNum(other.groupsNum),
      evaluator(other.evaluator),
      fitness(other.fitness),
      fitnessCalculated(other.fitnessCalculated)
{
}

Individual &Individual::operator=(const Individual &other) {
    if (this != &other) {
        genotype = other.genotype;
        fitness = other.fitness;
        fitnessCalculated = other.fitnessCalculated;
        groupsNum = other.groupsNum;
    }
    return *this;
}

Individual::~Individual() = default;

double Individual::calcAdaptation() const {
    if (!fitnessCalculated) {
        fitness = evaluator.evaluate(genotype);
        fitnessCalculated = true;
    }
    return fitness;
}

void Individual::mutate(double mutProb, std::mt19937 &rng) {
    std::uniform_real_distribution<> probDist(0.0, 1.0);
    std::uniform_int_distribution<> groupDist(0, groupsNum - 1);

    for (size_t i = 0; i < genotype.size(); i++) {
        if (probDist(rng) < mutProb) {
            genotype[i] = groupDist(rng);
        }
    }
    fitnessCalculated = false;
}

std::vector<Individual> Individual::reproduction(const Individual& p1, const Individual& p2, const double crossProb,std::mt19937& rng) {
    std::uniform_real_distribution<> probDist(0.0, 1.0);
    std::vector<Individual> children;
    children.reserve(2);

    const int n = p1.genotype.size();

    std::vector<int> g1 = p1.genotype;
    std::vector<int> g2 = p2.genotype;

    if (probDist(rng) < crossProb) {
        std::uniform_int_distribution<> cutDist(1, n - 1);
        int cut = cutDist(rng);

        for (int i = cut; i < n; ++i) {
            std::swap(g1[i], g2[i]);
        }
    }

    children.emplace_back(g1, p1.evaluator);
    children.emplace_back(g2, p1.evaluator);

    return children;
}
