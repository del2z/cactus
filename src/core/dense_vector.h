//------------------------------------------------------------------------------
// Dense Vector
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_DENSE_VECTOR_H_
#define _CACTUS_CORE_DENSE_VECTOR_H_

#include <cstdint>
#include <vector>

namespace cactus {

class SVector;
class DVector : public Vector {
  private:
    std::vector<float> data_;

  public:
    DVector();
    DVector(const SVector& svec);
    DVector(const DVector& dvec);
    virtual ~DVector();

  public:
    inline int32_t size() const;

    inline float Get(int32_t index) const;
    inline void Append(float value);
    inline void Append(int32_t index, float value);
    inline void Assign(int32_t index, float value);
    inline void Clear();
};

inline int32_t DVector::size() const {
    return this->data_.size();
}

inline float DVector::Get(int32_t index) const {
    if (index < 0 || index >= this->size()) {
        LOG(ERROR) << "Out of vector bound.";
        throw 102;
    }
    return this->data_.at(index);
}

inline void DVector::Append(float value) {
    this->data_.push_back(value);
}

inline void DVector::Append(int32_t index, float value) {
    if (index < this->size()) {
        VLOG(50) << "Index '" << index << "' not greater than "
            << "vector size '" << this->size() << "'; "
            << "use Assign(int, float) instead.";
        return;
    }
    for (int32_t k = this->size(); k < index; ++k) {
        this->data_.push_back(0);
    }
    this->Append(value);
}

inline void DVector::Assign(int32_t index, float value) {
    if (index >= this->size()) {
        VLOG(50) << "Index '" << index << "' not less than "
            << "vector size '" << this->size() << "'; "
            << "use Append(int, float) instead.";
        return;
    }
    this->data_[index] = value;
}

inline void DVector::Clear() {
    this->data_.clear();
}

} // namespace cactus

#endif // _CACTUS_CORE_DENSE_VECTOR_H_
