//
// Created by LiZnB on 2024/3/28.
//

#ifndef SA_SA_HPP
#define SA_SA_HPP

#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <algorithm>

template<typename T>
class SA {
public:
    SA(T _task, double _timeLimit);

    // 运行模拟退火，返回顺序
    std::vector<int> run();

private:
    T task;
    std::mt19937 engine;
    double timeLimit;
    std::vector<int> order;

    // 初始化退火参数, 自动调参
    void init();
};

template<typename T>
std::vector<int> SA<T>::run() {
    return order;
}

template<typename T>
void SA<T>::init() {
}

template<typename T>
SA<T>::SA(T _task, double _timeLimit) : task(_task), timeLimit(_timeLimit){
    engine = std::mt19937(2024);
    order.resize(task.size());
    std::iota(order.begin(), order.end(), 0);
    std::shuffle(order.begin(), order.end(), engine);
    init();
}

#endif //SA_SA_HPP
