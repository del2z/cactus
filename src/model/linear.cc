//------------------------------------------------------------------------------
// Implementations of linear models
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "model/linear.h"

#include <cmath>
#include <algorithm>
#include "glog/logging.h"

#include "objective/obj_mse.h"
#include "regularizer/reg_l2.h"

namespace cactus {

Linear::Linear()
        : Model(new ObjMse(), new RegL2(), new OptSgd()),
          bias_(0), coeff_(std::vector<float>()) {}

Linear::Linear(ObjFunc* obj, RegFunc* reg, OptSgd* opt)
        : Model(obj, reg, opt), bias_(0), coeff_(std::vector<float>()) {}

Linear::Linear(ObjFunc* obj, OptSgd* opt)
        : Model(obj, new RegL2(), opt),
          bias_(0), coeff_(std::vector<float>()) {}

Linear::~Linear() {
    this->coeff_.clear();
}

void Linear::CalcGrad_(const DVector& feat_vec,
        float grad_obj,
        std::vector<float>* grad_vec) const {
    grad_vec->clear();
    // gradient of bias
    grad_vec->push_back(grad_obj);
    for (int32_t k = 0; k < feat_vec.size(); ++k) {
        if (fabs(feat_vec.GetValue(k)) > 1e-3) {
            grad_vec->push_back(grad_obj * feat_vec.GetValue(k));
        } else {
            grad_vec->push_back(0);
        }
    }
}

float Linear::Predict_(const DVector& feat_vec) const {
    float result = this->bias_;
    for (auto itr = feat_vec.data().begin(); itr != feat_vec.data().end(); ++itr) {
        result += itr->value() * this->coeff_.at(itr->index());
    }
    return result;
}

void Linear::CalcGrad(const DMatrix& train_mat,
        const std::vector<float>& pred_vec,
        std::vector<float>* grad_vec) const {
    std::vector<float> g_obj_vec;
    ((OptSgd*)this->opt_)->CalcObjGrad(this->obj_, train_mat.ydata(), pred_vec, &g_obj_vec);
    std::vector<float> g_reg_vec;
    this->reg_->CalcGrad(this->coeff_, &g_reg_vec);

    grad_vec->clear();
    std::vector<float> g_tmp_vec;
    for (int32_t k = 0; k < train_mat.num_rows(); ++k) {
        this->CalcGrad_(train_mat.GetRow(k), g_obj_vec.at(k), &g_tmp_vec);
        if (grad_vec->size() <= 0) {
            std::copy(g_tmp_vec.begin(), g_tmp_vec.end(), std::back_inserter(*grad_vec));
        } else {
            for (int32_t j = 0; j < grad_vec->size(); ++j) {
                (*grad_vec)[j] += g_tmp_vec.at(j);
            }
        }
    }

    for (int32_t k = 0; k < grad_vec->size(); ++k) {
        if (k == 0) {
            grad_vec->at(k) = grad_vec->at(k) / train_mat.num_rows();
        } else {
            grad_vec->at(k) = grad_vec->at(k) / train_mat.num_rows() + g_reg_vec.at(k - 1);
        }
    }
}

void Linear::CalcGrad(const DMatrix& train_mat,
        std::vector<float>* grad_vec) const {
    std::vector<float> pred_vec;
    this->PredictBatch(train_mat, &pred_vec);
    this->CalcGrad(train_mat, pred_vec, grad_vec);
}

void Linear::Update(const std::vector<float>& delta_vec) {
    this->bias_ -= delta_vec.at(0);
    for (int32_t k = 0; k < this->coeff_.size(); ++k) {
        this->coeff_[k] -= delta_vec.at(k + 1);
    }
}

void Linear::TrainBatch(const DMatrix& train_mat, int32_t max_epoch) {
    this->InitCoeff_(0, 0.1, train_mat.num_cols());
    Model::TrainBatch(train_mat, max_epoch);
}

void Linear::PredictBatch(const DMatrix& pred_mat,
        std::vector<float>* pred_vec) const {
    if (pred_mat.num_cols() != this->coeff_.size()) {
        LOG(ERROR) << "Unmatched feature size and model.";
        throw 106;
    }
    Model::PredictBatch(pred_mat, pred_vec);
}

void Linear::Load(const std::string& file_in) {
}

void Linear::Dump(const std::string& file_out) const {
}
} // namespace cactus
