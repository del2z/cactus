//------------------------------------------------------------------------------
// Implementations of Objective functions
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "core/objective.h"

namespace cactus {

Objective::Objective()
        : err_type_(MSE) {}

Objective::Objective(ErrType err_type)
        : err_type_(err_type) {}

float Objective::getError(float label, float pred) const {
    if (this->err_type_ == MSE) {
        return this->calc_err_mse(label, pred);
    } else {
        return this->calc_err_mse(label, pred);
    }
}

const std::vector<float> Objective::getBatchError(const std::vector<float>& labels,
        const std::vector<float>& preds) const {
    if (labels.size() != preds.size() || labels.size() <= 0 || preds.size() <= 0) {
        std::cerr << "[ERROR] Empty vector or Unequal size." << std::endl;
        throw 104;
    }

    float (Objective::*calc_err_) (float, float) const = NULL;
    if (this->err_type_ == MSE) {
        calc_err_ = &Objective::calc_err_mse;
    } else {
        calc_err_ = &Objective::calc_err_mse;
    }

    std::vector<float> err_vec = std::vector<float>();
    for (int32_t k = 0; k < labels.size(); ++k) {
        err_vec.push_back((this->*calc_err_)(labels.at(k), preds.at(k)));
    }
    return err_vec;
}

float Objective::getBatchErrorSum(const std::vector<float>& labels,
        const std::vector<float>& preds) const {
    float err = 0;
    std::vector<float> err_vec = this->getBatchError(labels, preds);
    for (auto itr = err_vec.begin(); itr != err_vec.end(); ++itr) {
        err += *itr;
    }
    return err;
}

float Objective::getBatchErrorMean(const std::vector<float>& labels,
        const std::vector<float>& preds) const {
    float err = this->getBatchErrorSum(labels, preds);
    int32_t size = labels.size();
    return err / size;
}

float Objective::getGrad(float label, float pred) const {
    if (this->err_type_ == MSE) {
        return this->calc_grad_mse(label, pred);
    } else {
        return this->calc_grad_mse(label, pred);
    }
}

const std::vector<float> Objective::getBatchGrad(const std::vector<float>& labels,
        const std::vector<float>& preds) const {
    if (labels.size() != preds.size() || labels.size() <= 0 || preds.size() <= 0) {
        std::cerr << "[ERROR] Empty vector or Unequal size." << std::endl;
        throw 104;
    }

    float (Objective::*calc_grad_) (float, float) const = NULL;
    if (this->err_type_ == MSE) {
        calc_grad_ = &Objective::calc_grad_mse;
    } else {
        calc_grad_ = &Objective::calc_grad_mse;
    }

    std::vector<float> grad_vec = std::vector<float>();
    for (int32_t k = 0; k < labels.size(); ++k) {
        grad_vec.push_back((this->*calc_grad_)(labels.at(k), preds.at(k)));
    }
    return grad_vec;
}

} // namespace cactus
