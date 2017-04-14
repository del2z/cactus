//------------------------------------------------------------------------------
// Implementations of Dense Vector
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "core/dense_vector.h"

#include <cmath>
#include "glog/logging.h"

namespace cactus {

DVector::DVector()
        : data_(std::vector<float>()) {}

DVector::DVector(const SVector& svec) {
    LOG(WARNING) << "Need iterator on Vector to implement.";
}

DVector::DVector(const DVector& dvec) {
    LOG(WARNING) << "Need iterator on Vector to implement.";
}

} // namespace cactus
