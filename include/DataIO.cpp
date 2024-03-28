//
// Created by LiZnB on 2024/3/28.
//

#include "DataIO.h"

DataIO::DataIO(const std::string& _inputFilePath) : inputFilePath(_inputFilePath), in(_inputFilePath) {
    if (in.is_open()) {
        std::cout << "Open " << inputFilePath << " Succeeded" << std::endl;
    } else {
        std::cout << "Open " << inputFilePath << " Failed" << std::endl;
    }
}

std::vector<std::pair<double, double>> DataIO::ReadData() {
    std::string info;
    std::vector<std::pair<double, double>> task;
    do {
        if (!std::getline(in, info)) {
            std::cerr << "File format error" << std::endl;
            assert(0);
        }
    } while (info != "NODE_COORD_SECTION");
    while (true) {
        if (!std::getline(in, info)) {
            std::cerr << "File format error" << std::endl;
            assert(0);
        }
        std::istringstream iss(info);
        if (info == "EOF") {
            break;
        }
        int id;
        double x, y;
        iss >> id >> x >> y;
        task.emplace_back(x, y);
    }
    return task;
}
