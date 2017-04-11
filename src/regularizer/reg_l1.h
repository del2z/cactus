//------------------------------------------------------------------------------
// Regularization function - L1 Regularization
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_REGULARIZER_REG_L1_H_
#define _CACTUS_REGULARIZER_REG_L1_H_

#include <cmath>

#include "regularizer/reg_base.h"

namespace cactus {

class RegL1 : public RegFunc {
  private:
    float lambda_;

  public:
    RegL1();
    RegL1(float lambda);
    virtual ~RegL1() {}

  private:
    inline float CalcError_(float param) const;
    inline float CalcGrad_(float param) const;
};

inline float RegL1::CalcError_(float param) const {
    return this->lambda_ * fabs(param);
}

inline float RegL1::CalcGrad_(float param) const {
    if (param >= 0) {
        return this->lambda_;
    } else {
        return -1.0 * this->lambda_;
    }
}

} // namespace cactus

#endif // _CACTUS_REGULARIZER_REG_L1_H_
