//------------------------------------------------------------------------------
// Implementations of Data parser
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "io/data_parser.h"

#include <fstream>
#include "glog/logging.h"
#include "utils/string_alg.h"
#include "core/data_matrix.h"

namespace cactus {

const DMatrix DataParser::LoadSvm_(const std::string& file_in) const {
    std::ifstream ifs(file_in, std::ios::in);
    if (ifs.is_open()) {
        DMatrix dmat = DMatrix();
        std::string line;
        while (std::getline(ifs, line)) {
            std::vector<std::string> str_vec = SplitString(line, " ");
            float label = atof(str_vec.at(0).c_str());
            SVector svec = SVector();
            for (auto itr = str_vec.begin() + 1; itr != str_vec.end(); ++itr) {
                std::vector<std::string> entry = SplitString(*itr, ":");
                if (entry.size() != 2) continue;

                int32_t index = atoi(entry.at(0).c_str());
                float value = atof(entry.at(1).c_str());
                svec.Append(index, value);
            }
            if (!svec.empty()) {
                dmat.Append(svec, label);
            }
        }
        ifs.close();
        return dmat;
    } else {
        LOG(FATAL) << "Cannot open file '" << file_in << "'.";
        throw 103;
    }
}

int32_t DataParser::DumpCsv_(const DVector& data,
        const std::string& file_out) const {
    return 0;
}

const DMatrix DataParser::Load(const std::string& file_in,
        const std::string& format) const {
    if (format.compare("svm") == 0) {
        return this->LoadSvm_(file_in);
    } else {
        return DMatrix();
    }
}

int32_t DataParser::Dump(const DVector& data,
        const std::string& file_out) const {
    return 0;
}

} // namespace cactus
