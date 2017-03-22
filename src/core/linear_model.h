//------------------------------------------------------------------------------
// Linear model - linear, lasso, ridge and elastic net regression
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_LINEAR_MODEL_H_
#define _CACTUS_CORE_LINEAR_MODEL_H_

#include <cstdint>
#include <vector>
#include <iostream>
#include <random>

#include "core/objective.h"
#include "core/regularizer.h"
#include "core/optimizer.h"
#include "core/data_matrix.h"

namespace cactus {

class Linear {
  private:
    float bias_;
    std::vector<float> coeff_;

  public:
    Linear();
    virtual ~Linear();

  private:
    inline void init_coeff(float mu, float sigma, int32_t size);
    inline float calc_update(float param, float grad, float eta) const;
    inline float calc_pred(const DVector& feat) const;

  public:
    void train(const DMatrix& samples, ErrType err_type, RegType reg_type, OptType opt_type);
    const std::vector<float> predict(const DMatrix& samples) const;
    void evaluate(const DMatrix& samples) const;
};

inline void Linear::init_coeff(float mu, float sigma, int32_t size) {
    std::default_random_engine rand_eng;
    std::normal_distribution<float> dist(mu, sigma);
    for (int32_t k = 0; k < size; ++k) {
        this->coeff_.push_back(dist(rand_eng));
    }
}

inline float Linear::calc_pred(const DVector& feat) const {
    float y_hat = this->bias_;
    if (feat.data().empty()) {
        return y_hat;
    }
    for (auto itr = feat.data().begin(); itr != feat.data().end(); ++itr) {
        y_hat += this->coeff_.at(itr->index()) * itr->value();
    }
    return y_hat;
}

} // namespace cactus

#endif // _CACTUS_CORE_LINEAR_MODEL_H_
