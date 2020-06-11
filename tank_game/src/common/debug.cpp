#include "common/debug.hpp"

std::string format_file(const std::string& file){
    const std::string key("tank_game");
    auto found = file.rfind(key);
    if (found!=std::string::npos) {
        auto cut = found+key.size();
        return file.substr(cut, file.size()-cut);
    }
    return file;
}

std::string plop_file(const char* _file, int _line) {
    std::string file = format_file(_file);
    std::string line = std::to_string(_line);
    return " < File '"+file+"' | line "+line+" >";
}