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

    inline void setIndex(int32_t index);
    inline void setValue(float value);
    inline void set(int32_t index, float value);
    inline void set(const Entry& entry);
};

inline int32_t Entry::index() const {
    return this->index_;
}

inline float Entry::value() const {
    return this->value_;
}

inline void Entry::setIndex(int32_t index) {
    if (index < 0) {
        std::cerr << "[ERROR] Illegal entry index '" << index <<
            "' (must be non-negative)." << std::endl;
        throw 101;
    } else {
        this->index_ = index;
    }
}

inline void Entry::setValue(float value) {
    this->value_ = value;
}

inline void Entry::set(int32_t index, float value) {
    this->setIndex(index);
    this->setValue(value);
}

inline void Entry::set(const Entry& entry) {
    this->set(entry.index(), entry.value());
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
    virtual float getValue(int32_t index) const;

    virtual int32_t append(int32_t index, float value);
    virtual int32_t append(const Entry& entry);
    virtual void clear();
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
    virtual float getValue(int32_t index) const;

    virtual int32_t append(int32_t index, float value);
    virtual int32_t append(const Entry& entry);
    virtual void clear();
};

inline int32_t DVector::size() const {
    return this->size_;
}

void print(const SVector& svec);

} // namespace cactus

#endif // _CACTUS_CORE_DATA_VECTOR_H_
