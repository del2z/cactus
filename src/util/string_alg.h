//------------------------------------------------------------------------------
// String algorithms - split, strip, beginswith, endswith, etc
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_UTILS_STRING_ALG_H_
#define _CACTUS_UTILS_STRING_ALG_H_

#include <string>
#include <vector>

namespace cactus {

const std::vector<std::string> SplitString(const std::string& str,
        const std::string& delim);

} // namespace cactus

#endif // _CACTUS_UTILS_STRING_ALG_H_
