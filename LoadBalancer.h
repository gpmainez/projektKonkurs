//
// Created by pc on 14.01.2026.
//

#ifndef PROJEKT_LOADBALANCER_H
#define PROJEKT_LOADBALANCER_H
#include <string>

#include "Evaluator.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>



class LoadBalancer {
public:
    LoadBalancer();
    ~LoadBalancer();

    bool loadFromFile(const std::string & fileName);

    void fillEvaluator(Evaluator & evaluator) const;
    static int parseGroupNumFromName(const std::string &fileName);

private:
    void parseHeader(std::ifstream& file);
    void parseCoords(std::ifstream& file);
    void parseDemands(std::ifstream& file);
    void parseDepot(std::ifstream& file);


    void buildDistanceMatrix();

    int tableSize;
    int capacity;
    int depotId;
    int groupNum;

    std::vector<std::pair<double,double>> coords;
    std::vector<int> demands;
    std::vector<int> permutation;

    std::vector<std::vector<int>> dist;
};


#endif //PROJEKT_LOADBALANCER_H