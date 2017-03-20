//------------------------------------------------------------------------------
// Implementations of Data parser
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "io/data_parser.h"

#include <fstream>
#include <ifstream>
#include <ofstream>

#include "utils/string_alg.h"
#include "core/data_matrix.h"

namespace cactus {

const DMatrix& DataParser::load_svm(const std::string& file_in) const {
    ifstream ifs(file_in, ios::in);
    if (ifs.is_open()) {
        DMatrix dmat = DMatrix();
        std::string line;
        while (std::getline(ifs, line)) {
            std::vector<std::string> str_vec = splitString(line, ' ');
            float label = atof(str_vec.at(0).c_str());
            SVector svec = SVector();
            for (auto itr = str_vec.begin() + 1; itr != str_vec.end(); ++itr) {
                std::vector<std::string> entry = splitString(*itr, ':');
                if (entry.size() != 2) continue;

                int32_t index = atoi(entry.at(0).c_str());
                float value = atof(entry.at(1).c_str());
                svec.append(index, value);
            }
            if (!svec.empty()) {
                dmat.append(svec, label);
            }
        }
        ifs.close();
        return dmat;
    } else {
        std::cerr << "[ERROR] Cannot open file '" << file_in << "'." << std::endl;
        throw 103;
    }
}

int32_t DataParser::dump_csv(const std::vector<float>& data,
        const std::string& file_out) const {
}

const DMatrix& DataParser::load(const std::string& file_in,
        const std::string& format) const {
    if (format.compare("svm") == 0) {
        return load_svm(file_in);
    } else {
        return DMatrix();
    }
}

int32_t DataParser::dump(const std::vector<float>& data,
        const std::string& file_out) const {
}

} // namespace cactus
