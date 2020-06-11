#include <json.hpp>
#include "common/debug.hpp"


#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char* argv[]) {
    nlohmann::json j2;
    std::ifstream i2(argv[1]);
    i2>>j2;

    std::cout << j2 << std::endl;

    return 0;
}
