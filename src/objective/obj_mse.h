//------------------------------------------------------------------------------
// Objective function - Mean Squared Error
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_OBJECTIVE_OBJ_MSE_H_
#define _CACTUS_OBJECTIVE_OBJ_MSE_H_

#include <cstdint>
#include <vector>

#include "objective/obj_base.h"

namespace cactus {

class ObjMse : public ObjFunc {
  public:
    ObjMse() {}
    virtual ~ObjMse() {}

  private:
    inline float CalcError_(float label, float pred) const;
    inline float CalcGrad_(float label, float pred) const;
};

inline float ObjMse::CalcError_(float label, float pred) const {
    float resi = label - pred;
    return resi * resi;
}

inline float ObjMse::CalcGrad_(float label, float pred) const {
    return 2 * (pred - label);
}

} // namespace cactus

#endif // _CACTUS_OBJECTIVE_OBJ_MSE_H_
