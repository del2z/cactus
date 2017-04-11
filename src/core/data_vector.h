//------------------------------------------------------------------------------
// Data vector - structures of Entry, SVector and DVector
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_DATA_VECTOR_H_
#define _CACTUS_CORE_DATA_VECTOR_H_

#include <cstdint>
#include <vector>
#include <iostream>
#include "glog/logging.h"

namespace cactus {

/*
 * Basic element in a sparse vector
 */
class Entry {
  private:
    int32_t index_;
    float value_;

  public:
    Entry();
    virtual ~Entry() {}
    Entry(int32_t index, float value);
    Entry(const Entry& entry);

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
        LOG(ERROR) << "Illegal entry index '" << index <<
            "' (must be non-negative).";
        throw 101;
    } else {
        this->index_ = index;
    }
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

/*
 * Sparse vector of Entries
 */
class SVector {
  protected:
    std::vector<Entry> data_;

  public:
    SVector();
    virtual ~SVector();
    SVector(const SVector& svec);

  protected:
    SVector(const std::vector<Entry>& svec);

  public:
    inline const std::vector<Entry>& data() const;
    inline bool empty() const;
    
    virtual float GetValue(int32_t index) const;
    virtual int32_t Append(int32_t index, float value);
    virtual int32_t Append(const Entry& entry);
    virtual void Clear();
};

inline const std::vector<Entry>& SVector::data() const {
    return this->data_;
}

inline bool SVector::empty() const {
    return this->data_.empty();
}

/*
 * Data vector of Entries
 */
class DVector : public SVector {
  protected:
    int32_t size_;

  public:
    DVector();
    virtual ~DVector();
    DVector(const SVector& svec, int32_t size);
    DVector(const DVector& dvec);

  public:
    inline int32_t size() const;
    
    virtual float GetValue(int32_t index) const;
    virtual int32_t Append(int32_t index, float value);
    virtual int32_t Append(const Entry& entry);
    virtual void Clear();
};

inline int32_t DVector::size() const {
    return this->size_;
}

void print(const SVector& svec);

} // namespace cactus

#endif // _CACTUS_CORE_DATA_VECTOR_H_
