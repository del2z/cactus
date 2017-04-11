//------------------------------------------------------------------------------
// Regularization function - L2 Regularization
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_REGULARIZER_REG_L2_H_
#define _CACTUS_REGULARIZER_REG_L2_H_

#include <cmath>

#include "regularizer/reg_base.h"

namespace cactus {

class RegL2 : public RegFunc {
  private:
    float lambda_;

  public:
    RegL2();
    RegL2(float lambda);
    virtual ~RegL2() {}

  private:
    inline float CalcError_(float param) const;
    inline float CalcGrad_(float param) const;
};

inline float RegL2::CalcError_(float param) const {
    return this->lambda_ * param * param;
}

inline float RegL2::CalcGrad_(float param) const {
    return this->lambda_ * 2 * param;
}

} // namespace cactus

#endif // _CACTUS_REGULARIZER_REG_L2_H_
