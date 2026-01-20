//
// Created by pc on 14.01.2026.
//

#include "LoadBalancer.h"
#include <iostream>

LoadBalancer::LoadBalancer() : tableSize(0), capacity(0), depotId(0), groupNum(0) {
}

LoadBalancer::~LoadBalancer() = default;

bool LoadBalancer::loadFromFile(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) return false;

    tableSize = 0;
    capacity = 0;
    depotId = -1;
    coords.clear();
    demands.clear();
    permutation.clear();
    dist.clear();
    groupNum = parseGroupNumFromName(fileName);

    parseHeader(file);
    parseCoords(file);
    parseDemands(file);
    parseDepot(file);
    buildDistanceMatrix();

    file.close();

    return tableSize > 0 && coords.size() == tableSize && permutation.size() == tableSize - 1 && demands.size() ==
           tableSize && !dist.empty();
}

void LoadBalancer::fillEvaluator(Evaluator &evaluator) const {
    evaluator.set_capacity(capacity);
    evaluator.set_demands(demands);
    evaluator.set_client_num(permutation.size());
    evaluator.set_client_perm(permutation);
    evaluator.set_dist(dist);
    evaluator.set_grups_num(groupNum);
    evaluator.set_depot_inx(depotId);
    evaluator.set_load_instance(true);



    std::cout << "tablesize:" << tableSize << std::endl;
    std::cout << "dpot:" << depotId << std::endl;
    std::cout << "capacioty:" << capacity << std::endl;
    std::cout << "permsize:" << permutation.size() << std::endl;
    std::cout << "gropuNum: "<< groupNum << std::endl;
}

void LoadBalancer::parseHeader(std::ifstream &file) {
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string key;
        lineStream >> key;

        if (key == "DIMENSION") {
            size_t colon = line.find(':');
            if (colon != std::string::npos) {
                std::istringstream dimensionStream(line.substr(colon + 1));
                dimensionStream >> tableSize;
            }
        } else if (key == "CAPACITY") {
            size_t colon = line.find(':');
            if (colon != std::string::npos) {
                std::istringstream capacityStream(line.substr(colon + 1));
                capacityStream >> capacity;
            }
        } else if (key == "PERMUTATION") {
            size_t colon = line.find(':');
            if (colon != std::string::npos) {
                std::istringstream perm(line.substr(colon + 1));
                int val;
                while (perm >> val) {
                    permutation.push_back(val - 1);
                }
            }
        } else if (key == "NODE_COORD_SECTION") return;
    }
}

void LoadBalancer::parseCoords(std::ifstream &file) {
    std::string line;
    coords.clear();
    coords.reserve(tableSize);
    int cunt = 0;
    while (std::getline(file, line) && cunt < tableSize) {
        std::istringstream lineStream(line);
        double x, y;
        int id;

        if (lineStream >> id >> x >> y) {
            coords.emplace_back(x, y); //coords[id - 1] = {x, y}; bezpoieczniejsze
            cunt++;
        }
    }
}

void LoadBalancer::parseDemands(std::ifstream &file) {
    demands.clear();
    demands.reserve(tableSize);


    std::string line;
    int readCount = 0;

    while (readCount < tableSize && std::getline(file, line)) {
        std::istringstream lineStream(line);

        int id, demand;
        if (lineStream >> id >> demand) {
            demands.push_back(demand); //ewentualnie demands [id - 1] = demand bezpieczniejsze
            readCount++;
        }
    }
}


void LoadBalancer::parseDepot(std::ifstream &file) {
    std::string line;
    std::getline(file, line);
    std::istringstream lineStream(line);
    lineStream >> depotId;
}

void LoadBalancer::buildDistanceMatrix() {
    int n = coords.size();
    dist.assign(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dx = coords[i].first - coords[j].first;
            double dy = coords[i].second - coords[j].second;

            int d = static_cast<int>(round(sqrt(dx * dx + dy * dy)));
            dist[i][j] = dist[j][i] = d;
        }
    }
}

int LoadBalancer::parseGroupNumFromName(const std::string &fileName) {
    size_t kPos = fileName.find_last_of('k');
    if (kPos == std::string::npos) return 0;

    try {
        size_t dotPos = fileName.find('.', kPos);
        if (dotPos == std::string::npos) dotPos = fileName.length();

        std::string numStr = fileName.substr(kPos + 1, dotPos - kPos - 1);
        return std::stoi(numStr);
    } catch (...) {
        return 0;
    }
}



