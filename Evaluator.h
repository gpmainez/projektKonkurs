//
// Created by pc on 02.01.2026.
//

#ifndef PROJEKT_EVALUATOR_H
#define PROJEKT_EVALUATOR_H
#include <vector>
#include  <iostream>
#include  <string>


class Evaluator {
public:
    Evaluator();

    double evaluate(const std::vector<int>& genotype) const;
    bool loadFile(std::string& filename);

    bool isGood() const;

    int get_group_num() const {
        return grupsNum;
    }

    int get_client_num() const {
        return clientNum;
    }

    int get_capacity() const {
        return capacity;
    }

    const std::vector<int>& get_demand() const {
        return demands;
    }


    void set_client_num(int client_num) {
        clientNum = client_num;
    }

    void set_depot_inx(int depot_inx) {
        depotInx = depot_inx;
    }

    void set_grups_num(int grups_num) {
        grupsNum = grups_num;
    }

    void set_dist(const std::vector<std::vector<int>> &dist) {
        this->dist = dist;
    }

    void set_client_perm(const std::vector<int> &client_perm) {
        clientPerm = client_perm;
    }

    void set_load_instance(bool load_instance) {
        loadInstance = load_instance;
    }

    void set_demands(const std::vector<int>& d) {
        demands = d;
    }

    void set_capacity(int c) {
        capacity = c;
    }

private:

    int clientNum;
    int depotInx;
    int grupsNum;
    std::vector<std::vector<int>> dist ;
    std::vector<int> clientPerm;
    std::vector<int> demands;
    int capacity;
    bool loadInstance;

    bool isValid(const std::vector<int>& genotype) const;
    double computeGroup(int groupId, const std::vector<int>& genotype) const;

};


#endif //PROJEKT_EVALUATOR_H