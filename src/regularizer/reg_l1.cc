//------------------------------------------------------------------------------
// Implementations of L1 Regularization
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "regularizer/reg_l1.h"

#include "glog/logging.h"

namespace cactus {

RegL1::RegL1()
        : lambda_(0.1) {}

RegL1::RegL1(float lambda)
        : lambda_(lambda) {}

} // namespace cactus
