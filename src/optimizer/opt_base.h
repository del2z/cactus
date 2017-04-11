//------------------------------------------------------------------------------
// Base class of Optimization engine
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_OPTIMIZER_OPT_BASE_H_
#define _CACTUS_OPTIMIZER_OPT_BASE_H_

#include <vector>

#include "core/data_matrix.h"

namespace cactus {

class ObjFunc;
class Model;

class Engine {
  public:
    Engine() {}
    virtual ~Engine() {}

  public:
    virtual void CalcObjError(const ObjFunc* obj,
            const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec,
            std::vector<float>* err_vec) const;

    virtual void Train(Model* mdl, const DMatrix& train_mat, int32_t max_epoch) = 0;
    virtual void Predict(const Model* mdl, const DMatrix& pred_mat,
            std::vector<float>* pred_vec) const;
};

} // namespace cactus

#endif // _CACTUS_OPTIMIZER_OPT_BASE_H_
