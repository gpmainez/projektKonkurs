//
// Created by pc on 05.01.2026.
//

#include "Algorythm.h"

#include <algorithm>


Algorythm::Algorythm(Evaluator &evaluator, int popSize, double crossProb, double mutProb) : eval(evaluator),
    rng(std::random_device{}()),
    popSize(popSize),
    crossProb(crossProb),
    mutProb(mutProb),
    bestIndividual(std::vector<int>(evaluator.get_client_num(), 0), evaluator) {
    population.reserve(popSize);
}

Individual Algorythm::run(int numberOfCycles) {
    population.clear();
    initializePopulation();

    for (auto &ind: population) {
        ind.getFitness();
    }

    bestIndividual = population[0];

    for (int i = 0; i < numberOfCycles; i++) {
        std::vector<Individual> newPopulation;
        newPopulation.reserve(popSize);

        while (newPopulation.size() < popSize) {
            Individual &p1 = selectParent();
            Individual &p2 = selectParent();

            auto children = Individual::reproduction(p1, p2, crossProb, rng);

            for (auto& child : children) {
                child.mutate(mutProb, rng);
                child.getFitness();
                newPopulation.push_back(child);

                if (newPopulation.size() >= popSize)
                    break;
            }
        }
        population = std::move(newPopulation);

        for (auto& ind : population) {
            if (ind.getFitness() < bestIndividual.getFitness())
                bestIndividual = ind;
        }
    }
    return bestIndividual;
}

Individual &Algorythm::selectParent() {
    std::uniform_int_distribution<> dist(0, population.size() - 1);

    Individual &a = population[dist(rng)];
    Individual &b = population[dist(rng)];

    return (a.getFitness() < b.getFitness()) ? a : b;
}

void Algorythm::initializePopulation() {

    std::uniform_int_distribution<> groups(0, eval.get_group_num() - 1);

    population.clear();
    population.reserve(popSize);

    for (int i = 0; i < popSize; i++) {
        std::vector<int> genotype(eval.get_client_num());
        for (int&g: genotype) {
            g = groups(rng);
        }
        population.emplace_back(genotype, eval);
    }
}

const Individual& Algorythm::getBestIndividual() const {
    return bestIndividual;
}
