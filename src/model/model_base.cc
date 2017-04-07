//------------------------------------------------------------------------------
// Implementations of models
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "model/model_base.h"

#include <cstddef>
#include "glog/logging.h"

namespace cactus {

Model::Model(const ObjFunc* obj, Engine* opt)
        : obj_(obj), reg_(nullptr), opt_(opt) {}

Model::Model(const ObjFunc* obj, const RegFunc* reg, Engine* opt)
        : obj_(obj), reg_(reg), opt_(opt) {}

Model::~Model() {
    if (this->obj_) delete this->obj_;
    if (this->reg_) delete this->reg_;
    if (this->opt_) delete this->opt_;
}

float Model::CalcSumError(const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec) const {
    return this->obj_->CalcSumError(this->opt_, label_vec, pred_vec);
}

float Model::CalcAvgError(const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec) const {
    return this->obj_->CalcAvgError(this->opt_, label_vec, pred_vec);
}

void Model::TrainBatch(const DMatrix& train_mat) {
    if (train_mat.num_rows() <= 0 || train_mat.num_cols() <= 0) {
        LOG(ERROR) << "Empty data set.";
        throw 105;
    }
    this->opt_->Train(this, train_mat);
}

void Model::Predict(const DMatrix& pred_mat,
        std::vector<float>* pred_vec) const {
    pred_vec->clear();
    for (int32_t k = 0; k < pred_mat.num_rows(); ++k) {
        pred_vec->push_back(this->Predict_(pred_mat.GetRow(k)));
    }
    return;
}

void Model::PredictBatch(const DMatrix& pred_mat,
        std::vector<float>* pred_vec) const {
    if (pred_mat.num_rows() <= 0 || pred_mat.num_cols() <= 0) {
        LOG(ERROR) << "Empty data set.";
        throw 105;
    }
    this->opt_->Predict(this, pred_mat, pred_vec);
}

} // namespace cactus
