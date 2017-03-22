//------------------------------------------------------------------------------
// Implementations of String algorithms
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "utils/string_alg.h"

#include <iostream>

namespace cactus {

const std::vector<std::string> splitString(const std::string& str,
        const std::string& delim) {
    std::vector<std::string> str_vec = std::vector<std::string>();
    std::string::size_type pos1 = 0;
    std::string::size_type pos2 = str.find(delim);
    while(std::string::npos != pos2) {
        str_vec.push_back(str.substr(pos1, pos2 - pos1));
        pos1 = pos2 + delim.size();
        pos2 = str.find(delim, pos1);
    }
    if(pos1 != str.length()) {
        str_vec.push_back(str.substr(pos1));
    }
    return str_vec;
}

} // namespace cactus
