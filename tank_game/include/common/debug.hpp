#pragma once

#include <string>
#include <iostream>
#include <vector>

std::string plop_file(const char* _file, int _line);

std::string format_file(const std::string&);

inline std::string plop_val(std::string val) {
    return "  =>  " + val;
}

template <class T> inline std::string plop_val(T val) {
    return "  =>  " + std::to_string(val);
}

template <> inline std::string plop_val(const char*) {
    return "";
}

inline std::string plop_unquote(const char* str) {
   std::string result(str);
   if(result.length() > 2 && result[0] == '\"' && result[result.length()-1] == '\"') {
      result = result.substr(1, result.length()-2);
   }
   return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {

    for (const T& x : v)
        os << x << " ";
    return os;
}

#define plop(x) std::cerr << " DEBUG " << plop_file(__FILE__, __LINE__) << " : " << plop_unquote(#x) << plop_val(x) << std::endl
#define error(x) std::cerr << "ERROR " << plop_file(__FILE__, __LINE__) << " : " << plop_unquote(#x) << plop_val(x) << std::endl