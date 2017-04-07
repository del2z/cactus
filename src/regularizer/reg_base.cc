//------------------------------------------------------------------------------
// Implementations of Regularization functions
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "regularizer/reg_base.h"

#include "glog/logging.h"

namespace cactus {

float RegFunc::CalcError(const std::vector<float>& param_vec) const {
    if (param_vec.size() <= 0) {
        LOG(WARNING) << "Empty vector.";
        return 0;
    }

    float err = 0;
    for (int32_t k = 0; k < param_vec.size(); ++k) {
        err += this->CalcError_(param_vec.at(k));
    }
    return err;
}

void RegFunc::CalcGrad(const std::vector<float>& param_vec,
        std::vector<float>* grad_vec) const {
    if (param_vec.size() <= 0) {
        LOG(ERROR) << "Empty vector.";
        throw 104;
    }
    grad_vec->clear();
    for (int32_t k = 0; k < param_vec.size(); ++k) {
        grad_vec->push_back(this->CalcGrad_(param_vec.at(k)));
    }
    return;
}

} // namespace cactus
