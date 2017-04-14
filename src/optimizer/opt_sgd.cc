//------------------------------------------------------------------------------
// Implementations of mini-batch Stochastic Gradient Descent
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "optimizer/opt_sgd.h"

#include <iostream>
#include "model/linear.h"

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
    float norm_grad = 0;
    for (int32_t k = 0; k < grad_vec.size(); ++k) {
        norm_grad += grad_vec.at(k) * grad_vec.at(k);
    }
    norm_grad = sqrt(norm_grad + 1e-8);
    for (int32_t k = 0; k < grad_vec.size(); ++k) {
        delta_vec->push_back(this->eta_ * grad_vec.at(k) / norm_grad);
    }
}

void OptSgd::Train(Model* mdl, const DMatrix& train_mat, int32_t max_epoch) {
    // TODO: add multi-thread support
    Linear* mdl_lin = dynamic_cast<Linear*>(mdl);
    if (!mdl_lin) {
        LOG(ERROR) << "Gradient descent not suitable for non-linear model.";
        throw 107;
    }

    std::vector<int32_t> index_vec;
    for (int32_t k = 0; k < train_mat.num_rows(); ++k) {
        index_vec.push_back(k);
    }

    int32_t batch_size = 256;
    int32_t num_steps = train_mat.num_rows() / batch_size;
    for (int32_t epoch = 0; epoch < max_epoch; ++epoch) {
        std::vector<float> pred_vec;
        mdl_lin->PredictBatch(train_mat, &pred_vec);
        float ep_err = mdl_lin->CalcAvgError(train_mat.ydata(), pred_vec);
        std::cout << "Error at epoch " << epoch << ": " << ep_err << std::endl;

        std::random_shuffle(index_vec.begin(), index_vec.end());
        for (int32_t step = 0; step < num_steps; ++step) {
            DMatrix batch_mat;
            for (int32_t k = step * batch_size; k < (step + 1) * batch_size; ++k) {
                batch_mat.Append(train_mat.GetRow(index_vec.at(k)), train_mat.GetY(index_vec.at(k)));
            }
            std::vector<float> grad_vec;
            mdl_lin->CalcGrad(batch_mat, &grad_vec);
            std::vector<float> delta_vec;
            this->CalcUpdate(grad_vec, &delta_vec);
            mdl_lin->Update(delta_vec);
        }
        this->eta_ *= 0.95;
    }
}

} // namespace cactus
