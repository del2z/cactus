//------------------------------------------------------------------------------
// Implementations of Optimizer
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "core/optimizer.h"

#include "glog/logging.h"

namespace cactus {

Optimizer::Optimizer()
        : opt_type_(SGD), alpha_(0), beta_(0),
          grad_(std::vector<float>()), sq_grad_(std::vector<float>()) {}

Optimizer::Optimizer(OptType opt_type)
        : opt_type_(opt_type), alpha_(0.99), beta_(0.99),
          grad_(std::vector<float>()), sq_grad_(std::vector<float>()) {}

Optimizer::~Optimizer() {
    this->grad_.clear();
    this->sq_grad_.clear();
}

float Optimizer::getUpdate(float grad) const {
    if (this->opt_type_ == SGD) {
        return this->calc_opt_sgd(grad);
    } else {
        return this->calc_opt_sgd(grad);
    }
}

const std::vector<float> Optimizer::getAllUpdate(const std::vector<float>& grads) const {
    if (grads.size() <= 0) {
        LOG(ERROR) << "Empty vector.";
        throw 104;
    }

    float (Optimizer::*calc_opt_) (float) const = NULL;
    if (this->opt_type_ == SGD) {
        calc_opt_ = &Optimizer::calc_opt_sgd;
    } else {
        calc_opt_ = &Optimizer::calc_opt_sgd;
    }

    std::vector<float> upd_vec = std::vector<float>();
    for (int32_t k = 0; k < grads.size(); ++k) {
        upd_vec.push_back((this->*calc_opt_)(grads.at(k)));
    }
    return upd_vec;
}

} // namespace cactus
