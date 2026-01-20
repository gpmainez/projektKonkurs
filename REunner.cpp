//
// Created by pc on 16.01.2026.
//

#include "REunner.h"
#include "LoadBalancer.h"
#include "Evaluator.h"
#include "Algorythm.h"
#include <iostream>

using namespace std;

void REunner::runFromFile(const std::string& fileName) {
    LoadBalancer lb;

    if (!lb.loadFromFile(fileName)) {
        cout << "Cannot load file: " << fileName << endl;
        return;
    }

    Evaluator evaluator;
    lb.fillEvaluator(evaluator);

    if (!evaluator.isGood()) {
        cout << "Evaluator not initialized!" << endl;
        return;
    }


    Algorythm ga(evaluator, 50, 0.7, 0.01);
    ga.run(1000);

    const Individual& best = ga.getBestIndividual();
    std::cout << best.getFitness() << std::endl;
}
