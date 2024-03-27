//
// Created by LiZnB on 2024/3/28.
//

#ifndef SA_DATAIO_H
#define SA_DATAIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>

class DataIO {
public:
    DataIO(const std::string& _inputFilePath);
    std::vector<std::pair<double, double>> ReadData();

private:
    std::string inputFilePath;
    std::ifstream in;
};


#endif //SA_DATAIO_H
