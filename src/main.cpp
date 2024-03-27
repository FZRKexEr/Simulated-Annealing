#include <iostream>
#include <vector>
#include "TSP.h"
#include "SA.hpp"
#include "DataIO.h"

int main() {

    DataIO data("../data/bcl380.tsp");

    std::vector<std::pair<double, double>> task = data.ReadData();

    SA<TSP> solver(task, 10);
    auto order = solver.run();
    TSP res(task);

    std::cout << "Final Score: " << res.GetScore(order) << std::endl;
    for (auto &it : order) {
        std::cout << it << " ";
    }

    return 0;
}