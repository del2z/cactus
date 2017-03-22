//------------------------------------------------------------------------------
// Implementations of Linear model
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "core/linear_model.h"

#include <cmath>
#include <algorithm>

namespace cactus {

Linear::Linear()
        : bias_(0), coeff_(std::vector<float>()) {}

Linear::~Linear() {
    this->coeff_.clear();
}

void Linear::train(const DMatrix& samples, ErrType err_type, RegType reg_type,
        OptType opt_type) {
    Objective err_obj = Objective(err_type);
    Regularizer err_reg = Regularizer(reg_type);
    Optimizer optimizer = Optimizer(opt_type);
    int32_t batch_size = std::max(256, samples.num_rows() / 50);

    std::vector<int32_t> ind_vec = std::vector<int32_t>();
    for (int32_t k = 0; k < samples.num_rows(); ++k) {
        ind_vec.push_back(k);
    }

    this->init_coeff(0, 0.1, samples.num_cols());

    int32_t num_steps = samples.num_rows() / batch_size;
    float eta = 0.1;
    for (int32_t epoch = 0; epoch < 10; ++epoch) {
        std::random_shuffle(ind_vec.begin(), ind_vec.end());
        for (int32_t step = 0; step < num_steps; ++step) {
            std::vector<float> grad_coeff_vec = std::vector<float>();
            float grad_bias = 0;
            for (int32_t k = 0; k < batch_size; ++k) {
                DVector feat = samples.getRow(ind_vec.at(step * batch_size + k));
                float label = samples.getY(ind_vec.at(step * batch_size + k));
                float pred = this->calc_pred(feat);
                float grad_pred = err_obj.getGrad(label, pred);

                grad_bias += grad_pred;
                if (grad_coeff_vec.empty()) {
                    for (int32_t j = 0; j < this->coeff_.size(); ++j) {
                        grad_coeff_vec.push_back(grad_pred * feat.getValue(j));
                    }
                } else {
                    for (auto itr = feat.data().begin(); itr != feat.data().end(); ++itr) {
                        grad_coeff_vec[itr->index()] += grad_pred * itr->value();
                    }
                }
            }
            this->bias_ += eta * optimizer.getUpdate(grad_bias);
            std::vector<float> dwt = optimizer.getAllUpdate(grad_coeff_vec);
            for (int32_t j = 0; j < this->coeff_.size(); ++j) {
                this->coeff_[j] += eta * dwt.at(j);
            }
            eta = eta / sqrt(1 + epoch * num_steps + step);
        }
        std::vector<float> preds = this->predict(samples);
        float err_ep = err_obj.getBatchErrorMean(samples.ydata(), preds);
        std::cout << "MSE in " << epoch << " epoch: " << err_ep << std::endl;
    }
    return;
}

const std::vector<float> Linear::predict(const DMatrix& samples) const {
    std::vector<float> yhat_vec = std::vector<float>();
    for (int32_t k = 0; k < samples.num_rows(); ++k) {
        DVector feat = samples.getRow(k);
        yhat_vec.push_back(this->calc_pred(feat));
    }
    return yhat_vec;
}

void Linear::evaluate(const DMatrix& samples) const {
    std::vector<float> yhat_vec = this->predict(samples);
    float err = 0;
    for (int32_t k = 0; k < samples.num_rows(); ++k) {
        float resi = yhat_vec.at(k) - samples.getY(k);
        err += resi * resi;
    }
    std::cout << "Mean Squared Error: " << err / samples.num_rows() << std::endl;
    return;
}

} // namespace cactus
