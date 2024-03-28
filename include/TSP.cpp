//
// Created by LiZnB on 2024/3/28.
//

#include "TSP.h"

TSP::TSP(const std::vector<std::pair<double, double>> &_nodes) : nodes(_nodes) {}

double TSP::GetScore(const std::vector<int>& order) const {
    double score = 0;
    for (int u = 0; u < (int)order.size(); u++) {
        int v = (u + 1) % (int)order.size();
        score += Distance(nodes[order[u]], nodes[order[v]]);
    }
    return score;
}

double TSP::Distance(const std::pair<double, double> &u, const std::pair<double, double> &v) {
    return std::sqrt((u.first - v.first) * (u.first - v.first) + (u.second - v.second) * (u.second - v.second));
}

int TSP::size() const {
    return (int)nodes.size();
}
