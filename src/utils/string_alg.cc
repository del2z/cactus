//------------------------------------------------------------------------------
// Implementations of String algorithms
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "utils/string_alg.h"

#include <string.h>

namespace cactus {

std::vector<std::string> splitString(const std::string& str, const char* delim) {
    std::vector<std::string> str_vec;
    char* pch;
    pch = strtok((char*)str.c_str(), delim);
    while (pch != NULL) {
        pch = strtok(NULL, delim);
        str_vec.push_back(std::string(pch));
    }
    return str_vec;
}

} // namespace cactus
