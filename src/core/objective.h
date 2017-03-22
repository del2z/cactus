//------------------------------------------------------------------------------
// Objective function - mean squared error, cross-entropy error, etc
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_OBJECTIVE_H_
#define _CACTUS_CORE_OBJECTIVE_H_

#include <cstdint>
#include <vector>
#include <iostream>

namespace cactus {

enum ErrType {MSE, CEE};

class Objective {
  private:
    ErrType err_type_;

  public:
    Objective();
    virtual ~Objective() {};
    Objective(ErrType err_type);

  private:
    inline float calc_err_mse(float label, float pred) const;
    inline float calc_grad_mse(float label, float pred) const;

  public:
    float getError(float label, float pred) const;
    const std::vector<float> getBatchError(const std::vector<float>& labels,
            const std::vector<float>& preds) const;
    float getBatchErrorSum(const std::vector<float>& labels,
            const std::vector<float>& preds) const;
    float getBatchErrorMean(const std::vector<float>& labels,
            const std::vector<float>& preds) const;

    float getGrad(float label, float pred) const;
    const std::vector<float> getBatchGrad(const std::vector<float>& labels,
            const std::vector<float>& preds) const;
};

inline float Objective::calc_err_mse(float label, float pred) const {
    float resi = pred - label;
    return resi * resi;
}

inline float Objective::calc_grad_mse(float label, float pred) const {
    return 2 * (pred - label);
}
} // namespace cactus

#endif // _CACTUS_CORE_OBJECTIVE_H_
