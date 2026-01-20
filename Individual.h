//
// Created by pc on 02.01.2026.
//

#ifndef PROJEKT_INDIVIDUAL_H
#define PROJEKT_INDIVIDUAL_H
#include <vector>
#include <iostream>
#include <random>

#include "Evaluator.h"


class Individual {
public:

    Individual(const std::vector<int> &genotype, const Evaluator &eval);

    Individual(const Individual &other);

    Individual &operator=(const Individual &other);

    ~Individual();

    double calcAdaptation() const;

    void mutate(double mutProb, std::mt19937 &rng);

    static std::vector<Individual> reproduction(const Individual &p1, const Individual &p2,
                                         double crossProb, std::mt19937 &rng);

    double getFitness() const { return calcAdaptation(); }
    const std::vector<int> &getGenotype() const { return genotype; }

private:
    std::vector<int> genotype;
    mutable double fitness;
    const Evaluator &evaluator;
    mutable bool fitnessCalculated;

    int groupsNum;
};


#endif //PROJEKT_INDIVIDUAL_H
