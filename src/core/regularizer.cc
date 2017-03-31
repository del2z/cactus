//------------------------------------------------------------------------------
// Implementations of Regularizer
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "core/regularizer.h"

#include <iostream>
#include "glog/logging.h"

namespace cactus {

Regularizer::Regularizer()
        : reg_type_(L2) {}

Regularizer::Regularizer(RegType reg_type)
        : reg_type_(reg_type) {}

float Regularizer::getReg(float param) const {
    if (this->reg_type_ == L1) {
        return this->calc_reg_l1(param);
    } else {
        return this->calc_reg_l2(param);
    }
}

const std::vector<float> Regularizer::getBatchReg(
        const std::vector<float>& params) const {
    if (params.size() <= 0) {
        LOG(ERROR) << "Empty vector.";
        throw 104;
    }

    float (Regularizer::*calc_reg_) (float) const = NULL;
    if (this->reg_type_ == L1) {
        calc_reg_ = &Regularizer::calc_reg_l1;
    } else {
        calc_reg_ = &Regularizer::calc_reg_l2;
    }

    std::vector<float> reg_vec = std::vector<float>();
    for (int32_t k = 0; k < params.size(); ++k) {
        reg_vec.push_back((this->*calc_reg_)(params.at(k)));
    }
    return reg_vec;
}

float Regularizer::getGrad(float param) const {
    if (this->reg_type_ == L1) {
        return this->calc_grad_l1(param);
    } else {
        return this->calc_grad_l2(param);
    }
}

const std::vector<float> Regularizer::getBatchGrad(
        const std::vector<float>& params) const {
    if (params.size() <= 0) {
        LOG(ERROR) << "Empty vector.";
        throw 104;
    }

    float (Regularizer::*calc_grad_) (float) const = NULL;
    if (this->reg_type_ == L1) {
        calc_grad_ = &Regularizer::calc_grad_l1;
    } else {
        calc_grad_ = &Regularizer::calc_grad_l2;
    }

    std::vector<float> grad_vec = std::vector<float>();
    for (int32_t k = 0; k < params.size(); ++k) {
        grad_vec.push_back((this->*calc_grad_)(params.at(k)));
    }
    return grad_vec;
}

} // namespace cactus
