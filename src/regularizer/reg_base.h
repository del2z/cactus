//------------------------------------------------------------------------------
// Base class of Regularization functions
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_REGULARIZER_REG_BASE_H_
#define _CACTUS_REGULARIZER_REG_BASE_H_

#include <vector>

namespace cactus {

class RegFunc {
  protected:
    RegFunc() {}
  public:
    virtual ~RegFunc() {}

  protected:
    virtual float CalcError_(float param) const = 0;
    virtual float CalcGrad_(float param) const = 0;

  public:
    virtual float CalcError(const std::vector<float>& param_vec) const;
    virtual void CalcGrad(const std::vector<float>& param_vec,
            std::vector<float>* grad_vec) const;
};

} // namespace cactus

#endif // _CACTUS_REGULARIZER_REG_BASE_H_
