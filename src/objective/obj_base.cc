//------------------------------------------------------------------------------
// Implementations of Objective functions
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "objective/obj_base.h"

#include "glog/logging.h"

#include "optimizer/opt_sgd.h"

namespace cactus {

void ObjFunc::CalcError(const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec,
        std::vector<float>* err_vec) const {
    err_vec->clear();
    for (int32_t k = 0; k < label_vec.size(); ++k) {
        err_vec->push_back(this->CalcError_(label_vec.at(k), pred_vec.at(k)));
    }
    return;
}

void ObjFunc::CalcBatchError(const Engine* opt,
        const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec,
        std::vector<float>* err_vec) const {
    if (label_vec.size() != pred_vec.size() || label_vec.size() <= 0 || pred_vec.size() <= 0) {
        LOG(ERROR) << "Empty vector or Unequal size.";
        throw 104;
    }
    opt->CalcObjError(this, label_vec, pred_vec, err_vec);
}

float ObjFunc::CalcSumError(const Engine* opt,
        const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec) const {
    std::vector<float> err_vec;
    this->CalcBatchError(opt, label_vec, pred_vec, &err_vec);

    float err = 0;
    for (auto itr = err_vec.begin(); itr != err_vec.end(); ++itr) {
        err += *itr;
    }
    return err;
}

float ObjFunc::CalcAvgError(const Engine* opt,
        const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec) const {
    float err = this->CalcSumError(opt, label_vec, pred_vec);
    return err / label_vec.size();
}

void ObjFunc::CalcGrad(const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec,
        std::vector<float>* grad_vec) const {
    grad_vec->clear();
    for (int32_t k = 0; k < label_vec.size(); ++k) {
        grad_vec->push_back(this->CalcGrad_(label_vec.at(k), pred_vec.at(k)));
    }
    return;
}

void ObjFunc::CalcBatchGrad(const Engine* opt,
        const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec,
        std::vector<float>* grad_vec) const {
    if (label_vec.size() != pred_vec.size() || label_vec.size() <= 0 || pred_vec.size() <= 0) {
        LOG(ERROR) << "Empty vector or Unequal size.";
        throw 104;
    }

    const OptSgd* opt_sgd = dynamic_cast<const OptSgd*>(opt);
    if (!opt_sgd) {
        LOG(ERROR) << "Non-gradient descent optimizer not suitable for calculating objective's gradients.";
        throw 107;
    }
    opt_sgd->CalcObjGrad(this, label_vec, pred_vec, grad_vec);
}

} // namespace cactus
