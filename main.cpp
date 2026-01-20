//
// Created by pc on 05.01.2026.
//
#include <iostream>
#include <vector>
#include <cassert>

#include "Evaluator.h"
#include "Individual.h"
#include "REunner.h"

void assertEqual(double actual, double expected, const std::string &testName) {
    if (actual == expected) {
        std::cout << "[OK] " << testName << "\n";
    } else {
        std::cout << "[FAIL] " << testName
                << " expected=" << expected
                << " actual=" << actual << "\n";
    }
}

void testLCVRP_NoCapacityBreak() {
    std::vector<std::vector<int>> dist = {
        {0, 1, 2},
        {1, 0, 1},
        {2, 1, 0}
    };

    Evaluator eval;
    eval.set_dist(dist);
    eval.set_client_num(2);
    eval.set_client_perm({1, 2});
    eval.set_grups_num(1);
    eval.set_depot_inx(0);
    eval.set_capacity(10);
    eval.set_demands({0, 3, 4});
    eval.set_load_instance(true);

    std::vector<int> genotype = {0, 0};

    double cost = eval.evaluate(genotype);
    assertEqual(cost, 4.0, "LCVRP no capacity break");
}

void testLCVRP_CapacityBreak() {
    std::vector<std::vector<int>> dist = {
        {0, 1, 2},
        {1, 0, 1},
        {2, 1, 0}
    };

    Evaluator eval;
    eval.set_dist(dist);
    eval.set_client_num(2);
    eval.set_client_perm({1, 2});
    eval.set_grups_num(1);
    eval.set_depot_inx(0);
    eval.set_capacity(5);
    eval.set_demands({0, 3, 4});
    eval.set_load_instance(true);

    std::vector<int> genotype = {0, 0};

    double cost = eval.evaluate(genotype);
    assertEqual(cost, 6.0, "LCVRP capacity exceeded");
}

void testLCVRP_TwoGroupsWithCapacity() {
    std::vector<std::vector<int>> dist = {
        {0, 1, 2, 3},
        {1, 0, 1, 2},
        {2, 1, 0, 1},
        {3, 2, 1, 0}
    };

    Evaluator eval;
    eval.set_dist(dist);
    eval.set_client_num(3);
    eval.set_client_perm({1, 2, 3});
    eval.set_grups_num(2);
    eval.set_depot_inx(0);
    eval.set_capacity(5);
    eval.set_demands({0, 3, 3, 2});
    eval.set_load_instance(true);

    std::vector<int> genotype = {0, 0, 1};

    double cost = eval.evaluate(genotype);
    assertEqual(cost, 12.0, "LCVRP two groups with capacity");
}



int main() {
    // testLCVRP_NoCapacityBreak();
    // testLCVRP_CapacityBreak();
    // testLCVRP_TwoGroupsWithCapacity();

    REunner::runFromFile("C:/Users/pc/OneDrive - Politechnika Wroclawska/Pulpit/studia/studia/listy/TechnikiLab/konkurs/LcVRPContestPack/data/lcvrp/Vrp-Set-A/A-n33-k5.lcvrp");
    return 0;


}
