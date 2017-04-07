//------------------------------------------------------------------------------
// Base class of models
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_MODEL_MODEL_BASE_H_
#define _CACTUS_MODEL_MODEL_BASE_H_

#include <cstdint>
#include <vector>

#include "core/data_matrix.h"
#include "objective/obj_base.h"
#include "regularizer/reg_base.h"
#include "optimizer/opt_base.h"

namespace cactus {

class Model {
  protected:
    ObjFunc* obj_;
    RegFunc* reg_;
    Engine* opt_;

  protected:
    Model(const ObjFunc* obj, Engine* opt);
    Model(const ObjFunc* obj, const RegFunc* reg, Engine* opt);
    virtual ~Model()

  protected:
    virtual float Predict_(const DVector& feat_vec) const = 0;

  public:
    virtual float CalcSumError(const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec) const;
    virtual float CalcAvgError(const std::vector<float>& label_vec,
            const std::vector<float>& pred_vec) const;
    virtual void TrainBatch(const DMatrix& train_mat);

    virtual void Predict(const DMatrix& pred_mat,
            std::vector<float>* pred_vec) const;
    virtual void PredictBatch(const DMatrix& pred_mat,
            std::vector<float>* pred_vec) const;
};

} // namespace cactus

#endif // _CACTUS_MODEL_MODEL_BASE_H_
