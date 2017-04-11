//------------------------------------------------------------------------------
// Base class of Objective functions
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_OBJECTIVE_OBJ_BASE_H_
#define _CACTUS_OBJECTIVE_OBJ_BASE_H_

#include <cstdint>
#include <vector>

#include "optimizer/opt_base.h"

namespace cactus {

class ObjFunc {
  protected:
    ObjFunc() {}
  public:
    virtual ~ObjFunc() {}

  protected:
    virtual float CalcError_(float label, float pred) const = 0;
    virtual float CalcGrad_(float label, float pred) const = 0;

  public:
    virtual void CalcError(const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec,
            std::vector<float>* err_vec) const;
    virtual void CalcBatchError(const Engine* opt,
            const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec,
            std::vector<float>* err_vec) const;
    virtual float CalcSumError(const Engine* opt,
            const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec) const;
    virtual float CalcAvgError(const Engine* opt,
            const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec) const;

    virtual void CalcGrad(const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec,
            std::vector<float>* grad_vec) const;
    virtual void CalcBatchGrad(const Engine* opt,
            const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec,
            std::vector<float>* grad_vec) const;
};

} // namespace cactus

#endif // _CACTUS_OBJECTIVE_OBJ_BASE_H_
