//------------------------------------------------------------------------------
// Implementations of Optimization engine
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "optimizer/opt_base.h"

namespace cactus {

void Engine::CalcObjError(const ObjFunc* obj,
        const std::vector<float>& label_vec,
        const std::vector<float>& pred_vec,
        std::vector<float>* err_vec) const {
    // TODO: add multi-thread support
    obj->CalcError(label_vec, pred_vec, err_vec);
}

void Engine::Predict(const Model* mdl, const DMatrix& pred_mat,
        std::vector<float>* pred_vec) const {
    // TODO: add multi-thread support
    mdl->Predict(pred_mat, pred_vec);
}

} // namespace cactus
