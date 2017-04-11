//------------------------------------------------------------------------------
// Optimization engine - mini-batch Stochastic Gradient Descent
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_OPTIMIZER_OPT_SGD_H_
#define _CACTUS_OPTIMIZER_OPT_SGD_H_

#include <vector>

#include "optimizer/opt_base.h"

namespace cactus {

class OptSgd : public Engine {
  private:
    // learning rate
    float eta_;

  public:
    OptSgd();
    OptSgd(float eta);
    virtual ~OptSgd() {}

  public:
    virtual void CalcObjGrad(const ObjFunc* obj,
            const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec,
            std::vector<float>* grad_vec) const;
    virtual void CalcUpdate(const std::vector<float>& grad_vec,
            std::vector<float>* delta_vec);
    virtual void Train(Model* mdl, const DMatrix& train_mat, int32_t max_epoch);
};

} // namespace cactus

#endif // _CACTUS_OPTIMIZER_OPT_SGD_H_
