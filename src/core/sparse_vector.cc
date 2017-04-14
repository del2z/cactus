//------------------------------------------------------------------------------
// Implementations of Sparse Vector
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "core/sparse_vector.h"

#include <cmath>

namespace cactus {

Entry::Entry(int32_t index, float value)
        : index_(index), value_(value) {}

Entry::Entry(const Entry& entry)
        : index_(entry.index()), value_(entry.value()) {}

SVector::SVector()
        : rdata_(std::vector<Entry>()),
          cdata_(std::map<int32_t, float>()), size_(0) {}

SVector::SVector(const SVector& svec)
        : size_(svec.size()) {
    LOG(WARNING) << "Need iterator on Vector to implement.";
}

SVector::SVector(const DVector& dvec)
        : size_(dvec.size()) {
    LOG(WARNING) << "Need iterator on Vector to implement.";
}

SVector::~SVector() {
    this->rdata_.clear();
    this->cdata_.clear();
    this->size_ = 0;
}

float SVector::Get(int32_t index) const {
    if (index < 0 || index >= this->size()) {
        LOG(ERROR) << "Out of vector bound.";
        throw 102;
    }
    if (this->cdata_.find(index) != this->cdata_.end()) {
        return this->cdata_.at(index);
    }
    return 0;
}

void SVector::Assign(int32_t index, float value) {
    if (index >= this->size()) {
        VLOG(50) << "Index '" << index << "' not less than "
            << "vector size '" << this->size() << "'; "
            << "use Append(int, float) instead.";
        return;
    }
    for (auto itr = this->rdata_.begin(); itr != this->rdata_.end(); ++itr) {
        if (itr->index() > index) {
            this->rdata_.insert(itr, Entry(index, value));
            break;
        } else if (itr->index() == index) {
            itr->SetValue(value);
            break;
        }
    }
    this->cdata_[index] = value;
}

} // namespace cactus
