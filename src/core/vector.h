//------------------------------------------------------------------------------
// Abstract Vector class
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_VECTOR_H_
#define _CACTUS_CORE_VECTOR_H_

#include <cstdint>

namespace cactus {

class Vector {
  private:
    bool is_row_;

  public:
    Vector();
    virtual ~Vector() {}

  public:
    inline bool is_row() const;
    inline const Vector& Transpose();

    virtual int32_t size() const = 0;
    virtual float Get(int32_t index) const = 0;
    virtual void Append(float value) = 0;
    virtual void Append(int32_t index, float value) = 0;
    virtual void Assign(int32_t index, float value) = 0;
    virtual void Clear() = 0;
};

Vector::Vector()
        : is_row_(true) {}

inline bool Vector::is_row() const {
    return this->is_row_;
}

inline const Vector& Vector::Transpose() {
    this->is_row_ = false;
    return *this;
}

} // namespace cactus

#endif // _CACTUS_CORE_VECTOR_H_
