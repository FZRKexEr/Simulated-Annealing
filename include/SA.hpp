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
#include <cmath>
#include <cassert>

template<typename T>
class SA {
public:
    SA(T _task);

    // run: 运行模拟退火，返回顺序, timeLimit 时间限制, noImproveLimit 无改进迭代次数限制
    std::vector<int> run(double timeLimit, int noImproveLimit);

private:
    T task;                                                 // 排序对象
    std::mt19937 engine;
    std::vector<int> order;
    std::uniform_int_distribution<int> randNumber;          // 随机数
    std::uniform_real_distribution<double> zeroOne;         // 0到1随机数
    double tempInit;                                        // 初始温度

    void init();                                            // 初始化退火参数, 自动调参?
    void swapOpt(std::vector<int>& arr);                    // swap
    void reverseOpt(std::vector<int>& arr);                 // reverse
    void transposeOpt(std::vector<int>& arr);               // transpose
};

template<typename T>
void SA<T>::transposeOpt(std::vector<int> &arr) {
    int u = randNumber(engine);
    int v = randNumber(engine);
    while (u == v) {
        v = randNumber(engine);
    }
    if (u < v) {
        arr.insert(arr.begin() + v + 1, arr[u]);
        arr.erase(arr.begin() + u);
    } else {
        arr.insert(arr.begin() + v + 1, arr[u]);
        arr.erase(arr.begin() + u + 1);
    }
}

template<typename T>
void SA<T>::reverseOpt(std::vector<int> &arr) {
    int u = randNumber(engine);
    int v = randNumber(engine);
    while (u == v) {
        v = randNumber(engine);
    }
    if (u > v) {
        std::swap(u, v);
    }
    std::reverse(arr.begin() + u, arr.begin() + v + 1);
}

template<typename T>
void SA<T>::swapOpt(std::vector<int> &arr) {
    int u = randNumber(engine);
    int v = randNumber(engine);
    while (u == v) {
        v = randNumber(engine);
    }
    std::swap(arr[u], arr[v]);
}

template<typename T>
std::vector<int> SA<T>::run(double timeLimit, int noImproveLimit) {
    auto startTime = std::chrono::high_resolution_clock::now();
    int iterationNumbers = 0;
    int noImproveNumbers = 0;

    double temp = tempInit;
    double currentScore = task.GetScore(order);
    double bestScore = currentScore;
    double lastBestScore = bestScore;
    std::vector<int> currentOrder = order;

    while ((double)(std::chrono::high_resolution_clock::now() - startTime).count() < timeLimit * 1e9
           &&
           noImproveNumbers <= noImproveLimit) {

        std::vector<int> newOrder = currentOrder;

        int method = randNumber(engine) % 3;
        switch (method) {
            case 0:
                swapOpt(newOrder);
                break;
            case 1:
                transposeOpt(newOrder);
                break;
            case 2:
                reverseOpt(newOrder);
                break;
            default:
                assert(0);
                break;
        }

        double newScore = task.GetScore(newOrder);

        if (newScore <= currentScore || (zeroOne(engine) < std::exp(-1.0 * (newScore - currentScore) / temp))) {
            currentScore = newScore;
            currentOrder = newOrder;
            if (currentScore < bestScore) {
                bestScore = currentScore;
                order = currentOrder;
            }
        }

        double alpha = 1 + std::log(1 + iterationNumbers);      // 下降系数
        iterationNumbers++;
        temp = tempInit / alpha;

        if (std::abs(bestScore - lastBestScore) < 1e-12) {
            noImproveNumbers++;
        } else {
            noImproveNumbers = 0;
        }
        lastBestScore = bestScore;
    }

    return order;
}

template<typename T>
void SA<T>::init() {
    tempInit = 10;
}

template<typename T>
SA<T>::SA(T _task) : task(_task) {
    assert(task.size() >= 3);
    engine = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());

    order.resize(task.size());
    std::iota(order.begin(), order.end(), 0);
    std::shuffle(order.begin(), order.end(), engine);

    randNumber = std::uniform_int_distribution<int>(0, (int)task.size() - 1);
    zeroOne = std::uniform_real_distribution<double>(0.0, 1.0);
    init();
}

#endif //SA_SA_HPP
