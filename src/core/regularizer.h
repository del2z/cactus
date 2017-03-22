//------------------------------------------------------------------------------
// Regularization term - L1, L2 and L12, etc
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_REGULARIZER_H_
#define _CACTUS_CORE_REGULARIZER_H_

#include <cstdint>
#include <vector>
#include <cmath>

namespace cactus {

enum RegType {L1, L2, L12};

class Regularizer {
  private:
    RegType reg_type_;

  public:
    Regularizer();
    virtual ~Regularizer() {}
    Regularizer(RegType reg_type);

  private:
    inline float calc_reg_l1(float param) const;
    inline float calc_grad_l1(float param) const;
    inline float calc_reg_l2(float param) const;
    inline float calc_grad_l2(float param) const;

  public:
    float getReg(float param) const;
    const std::vector<float> getBatchReg(const std::vector<float>& params) const;

    float getGrad(float param) const;
    const std::vector<float> getBatchGrad(const std::vector<float>& params) const;
};

inline float Regularizer::calc_reg_l1(float param) const {
    return fabs(param);
}

inline float Regularizer::calc_grad_l1(float param) const {
    return (param >= 0) ? 1 : -1;
}

inline float Regularizer::calc_reg_l2(float param) const {
    return param * param;
}

inline float Regularizer::calc_grad_l2(float param) const {
    return 2 * param;
}

} // namespace cactus

#endif // _CACTUS_CORE_REGULARIZER_H_
