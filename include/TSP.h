//
// Created by LiZnB on 2024/3/28.
//

#ifndef SA_TSP_H
#define SA_TSP_H

#include <vector>
#include <cmath>

class TSP {
public:
    TSP(const std::vector<std::pair<double, double>>& _nodes);

    // GetScore: 输入顺序，返回这个顺序的得分
    [[nodiscard]] double GetScore(const std::vector<int>& order) const;

    [[nodiscard]] int size() const;

private:
    std::vector<std::pair<double, double>> nodes;

    // Distance: 得到两个 node 之间的距离
    static double Distance(const std::pair<double, double>& u, const std::pair<double, double>& v) ;
};

#endif //SA_TSP_H
