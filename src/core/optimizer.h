//------------------------------------------------------------------------------
// Optimizer - mini-batch stochastic gradient decent
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_OPTIMIZER_H_
#define _CACTUS_CORE_OPTIMIZER_H_

#include <cstdint>
#include <vector>
#include <iostream>

namespace cactus {

enum OptType {SGD, Momentum, AdaGrad, AdaDelta, RMSprop, Adam};

class Optimizer {
  private:
    OptType opt_type_;
    float alpha_;
    float beta_;
    std::vector<float> grad_;
    std::vector<float> sq_grad_;

  public:
    Optimizer();
    virtual ~Optimizer();
    Optimizer(OptType opt_type);

  private:
    inline float calc_opt_sgd(float grad) const;

  public:
    float getUpdate(float grad) const;
    const std::vector<float> getAllUpdate(const std::vector<float>& grads) const;
};

inline float Optimizer::calc_opt_sgd(float grad) const {
    return -grad;
}

} // namespace cactus

#endif // _CACTUS_CORE_OPTIMIZER_H_
