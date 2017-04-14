//------------------------------------------------------------------------------
// Sparse Vector
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_SPARSE_VECTOR_H_
#define _CACTUS_CORE_SPARSE_VECTOR_H_

#include <cstdint>
#include <vector>
#include "glog/logging.h"

namespace cactus {

class Entry {
  private:
    int32_t index_;
    float value_;

  public:
    Entry(int32_t index, float value);
    Entry(const Entry& entry);
    virtual ~Entry() {}

  public:
    inline int32_t index() const;
    inline float value() const;

    inline void SetIndex(int32_t index);
    inline void SetValue(float value);
    inline void Set(int32_t index, float value);
    inline void Set(const Entry& entry);
};

inline int32_t Entry::index() const {
    return this->index_;
}

inline float Entry::value() const {
    return this->value_;
}

inline void Entry::SetIndex(int32_t index) {
    if (index < 0) {
        LOG(ERROR) << "Illegal entry index '" << index
            << "' (must be non-negative).";
        throw 101;
    }
    this->index_ = index;
}

inline void Entry::SetValue(float value) {
    this->value_ = value;
}

inline void Entry::Set(int32_t index, float value) {
    this->SetIndex(index);
    this->SetValue(value);
}

inline void Entry::Set(const Entry& entry) {
    this->Set(entry.index(), entry.value());
}

class DVector;
class SVector : public Vector {
  private:
    // rdata_ for row access
    std::vector<Entry> rdata_;
    // cdata_ for col access
    std::map<int32_t, float> cdata_;
    int32_t size_;

  public:
    SVector();
    SVector(const SVector& svec);
    SVector(const DVector& dvec);
    virtual ~SVector();

  public:
    inline int32_t size() const;

    float Get(int32_t index) const;
    inline void Append(float value);
    inline void Append(int32_t index, float value);
    void Assign(int32_t index, float value);
    inline void Clear();
};

inline int32_t SVector::size() const {
    return this->size_;
}

inline void SVector::Append(float value) {
    this->rdata_.push_back(Entry(this->size(), value));
    this->cdata_[this->size()] = value;
    ++this->size_;
}

inline void SVector::Append(int32_t index, float value) {
    if (index < this->size()) {
        VLOG(50) << "Index '" << index << "' not greater than "
            << "vector size '" << this->size() << "'; "
            << "use Assign(int, float) instead.";
        return;
    }
    this->rdata_.push_back(Entry(index, value));
    this->cdata_[index] = value;
    this->size_ = index + 1;
}

inline void SVector::Clear() {
    this->rdata_.clear();
    this->cdata_.clear();
    this->size_ = 0;
}

} // namespace cactus

#endif // _CACTUS_CORE_SPARSE_VECTOR_H_
