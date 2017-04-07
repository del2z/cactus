//------------------------------------------------------------------------------
// Implementations of mini-batch Stochastic Gradient Descent
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "optimizer/opt_sgd.h"

namespace cactus {

OptSgd::OptSgd()
        : eta_(0.5) {}

OptSgd::OptSgd(float eta)
        : eta_(eta) {}

void OptSgd::CalcObjGrad(const ObjFunc* obj,
        const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec,
        std::vector<float>* grad_vec) const {
    // TODO: add multi-thread support
    obj->CalcGrad(label_vec, pred_vec, grad_vec);
}

void OptSgd::CalcUpdate(const std::vector<float>& grad_vec,
        std::vector<float>* delta_vec) {
    delta_vec->clear();
    std::copy(grad_vec.begin(), grad_vec.end(), delta_vec->begin());
}

void OptSgd::Train(Model* mdl, const DMatrix& train_mat, int32_t max_epoch) const {
    std::vector<int32_t> index_vec;
    for (int32_t k = 0; k < train_mat.num_rows(); ++k) {
        index_vec.push_back(k);
    }

    int32_t batch_size = 256;
    int32_t num_steps = train_mat.num_rows() / batch_size;
    for (int32_t epoch = 0; epoch < max_epoch; ++epoch) {
        std::vector<float> pred_vec;
        mdl->PredictBatch(train_mat, &pred_vec);
        float ep_err = mdl->CalcAvgError(train_mat.ydata(), pred_vec);
        VLOG(0) << "Error at epoch " << epoch << ": " << ep_err;

        std::random_shuffle(index_vec.begin(), index_vec.end());
        for (int32_t step = 0; step < num_steps; ++step) {
            DMatrix batch_mat;
            for (int32_t k = step * batch_size; k < (step + 1) * batch_size; ++k) {
                batch_mat.Append(train_mat.GetRow(index_vec.at(k)), train_mat.GetY(index_vec.at(k)));
            }
            std::vector<float> grad_vec;
            mdl->CalcGrad(batch_mat, &grad_vec);
            std::vector<float> delta_vec;
            this->CalcUpdate(grad_vec, &delta_vec);
            mdl->Update(delta_vec);
        }
        this->eta_ *= 0.95;
    }
}

} // namespace cactus
