//
// Created by pc on 02.01.2026.
//

#include "Evaluator.h"

using namespace std;


Evaluator::Evaluator()
    : clientNum(0),
      grupsNum(0),
      depotInx(0),
      capacity(0),
      loadInstance(false) {
}

bool Evaluator::isValid(const std::vector<int> &genotype) const {
    if (genotype.size() != clientPerm.size()) return false;

    for (int i: genotype) {
        if (i < 0 || i >= grupsNum) return false;
    }

    return true;
}

double Evaluator::computeGroup(const int groupId, const std::vector<int> &genotype) const {
    vector<int> groupClients;
    for (int i = 0; i < genotype.size(); i++) {
        if (genotype[i] == groupId) {
            int permNum = clientPerm[i];

            groupClients.push_back(permNum);
        }
    }

    if (groupClients.empty()) {
        return 0.0; //bo nie wyjedzie ceizarowka
    }
    double cost = 0.0;
    int currentLoad = 0;
    int last = depotInx;

    for (int client: groupClients) {
        int demand = demands[client];


        if (demand > capacity) {
            return 1e9;
        }

        if (currentLoad + demand > capacity) {
            cost += dist[last][depotInx];
            cost += dist[depotInx][client];
            currentLoad = demand;
            last = client;
        } else {
            cost += dist[last][client];
            currentLoad += demand;
            last = client;
        }
    }
    if (last != depotInx) {
        cost += dist[last][depotInx];
    }

    return cost;
}

bool Evaluator::isGood() const {
    return loadInstance;
}


double Evaluator::evaluate(const std::vector<int> &genotype) const {
    if (!isValid(genotype)) return 1e9;
    double totalCost = 0.0;
    for (int i = 0; i < grupsNum; i++) {
        totalCost += computeGroup(i, genotype);
    }

    return totalCost;
}
