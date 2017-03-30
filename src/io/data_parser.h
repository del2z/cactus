//------------------------------------------------------------------------------
// Data parser - load training data into array and dump predictions into csv
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_IO_DATA_PARSER_H_
#define _CACTUS_IO_DATA_PARSER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "core/data_matrix.h"

namespace cactus {

class DataParser {
  public:
    DataParser() {}
    virtual ~DataParser() {}

  private:
    const DMatrix load_svm(const std::string& file_in) const;
    int32_t dump_csv(const DVector& data, const std::string& file_out) const;

  public:
    const DMatrix load(const std::string& file_in, const std::string& format) const;
    int32_t dump(const DVector& data, const std::string& file_out) const;

};
} // namespace cactus

#endif // _CACTUS_IO_DATA_PARSER_H_
