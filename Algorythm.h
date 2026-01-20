//
// Created by pc on 05.01.2026.
//

#ifndef PROJEKT_ALGORYTHM_H
#define PROJEKT_ALGORYTHM_H
#include "Evaluator.h"
#include "Individual.h"


class Algorythm {
public:
    Algorythm(Evaluator& evaluator, int popSize, double crossProb, double mutProb);

    Individual run(int numberOfCycles);

    const Individual& getBestIndividual() const;

private:
    Individual& selectParent();
    void initializePopulation();

    Evaluator& eval;
    std::mt19937 rng;
    int popSize;
    double crossProb;
    double mutProb;

    std::vector<Individual> population;
    Individual bestIndividual;



};


#endif //PROJEKT_ALGORYTHM_H