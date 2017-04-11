//------------------------------------------------------------------------------
// Linear models - for regression and classification
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_MODEL_LINEAR_H_
#define _CACTUS_MODEL_LINEAR_H_

#include <cstdint>
#include <vector>
#include <random>

#include "model/model_base.h"
#include "optimizer/opt_sgd.h"

namespace cactus {

class Linear : public Model {
  private:
    float bias_;
    std::vector<float> coeff_;

  public:
    Linear();
    Linear(ObjFunc* obj, RegFunc* reg, OptSgd* opt);
    Linear(ObjFunc* obj, OptSgd* opt);
    virtual ~Linear();

  protected:
    virtual inline void InitCoeff_(float mean, float stdev, int32_t size);
    virtual void CalcGrad_(const DVector& feat_vec,
            float grad_obj,
            std::vector<float>* grad_vec) const;
    virtual float Predict_(const DVector& feat_vec) const;

  public:
    virtual void CalcGrad(const DMatrix& train_mat,
            const std::vector<float>& pred_vec,
            std::vector<float>* grad_vec) const;
    virtual void CalcGrad(const DMatrix& train_mat,
            std::vector<float>* grad_vec) const;
    virtual void Update(const std::vector<float>& delta_vec);
    virtual void TrainBatch(const DMatrix& train_mat,
            int32_t max_epoch);
    virtual void PredictBatch(const DMatrix& pred_mat,
            std::vector<float>* pred_vec) const;
    virtual void Load(const std::string& file_in);
    virtual void Dump(const std::string& file_out) const;
};

inline void Linear::InitCoeff_(float mean, float stdev, int32_t size) {
    std::default_random_engine rand_eng;
    std::normal_distribution<float> dist(mean, stdev);
    for (int32_t k = 0; k < size; ++k) {
        this->coeff_.push_back(dist(rand_eng));
    }
}

} // namespace cactus

#endif // _CACTUS_MODEL_LINEAR_H_
