//------------------------------------------------------------------------------
// Implementations of L2 Regularization
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "regularizer/reg_l2.h"

#include "glog/logging.h"

namespace cactus {

RegL2::RegL2()
        : lambda_(0.1) {}

RegL2::RegL2(float lambda)
        : lambda_(lambda) {}

} // namespace cactus
