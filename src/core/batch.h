//------------------------------------------------------------------------------
// Matrix
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_MATRIX_H_
#define _CACTUS_CORE_MATRIX_H_

#include <cstdint>
#include <vector>

namespace cactus {

class Matrix {
  protected:
    std::vector<Vector> mdata_;
    int32_t num_rows_;
    int32_t num_cols_;

  public:
    Matrix();
    virtual ~Matrix();
    Matrix(const Matrix& mat);

  public:
    inline int32_t num_rows() const;
    inline int32_t num_cols() const;

    inline const Vector& GetRow(int32_t row_ind) const;
    inline const Vector& GetCol(int32_t col_ind) const;

    virtual int32_t Append(const SVector& svec);
    virtual int32_t Remove(int32_t row_ind);
    virtual void Clear();
};

inline int32_t SMatrix::num_rows() const {
    return this->num_rows_;
}

inline int32_t SMatrix::num_cols() const {
    return this->num_cols_;
}

inline const std::vector<SVector>& SMatrix::xdata() const {
    return this->xdata_;
}

inline const DVector SMatrix::GetRow(int32_t row_ind) const {
    if (row_ind < 0 || row_ind >= this->num_rows()) {
        LOG(ERROR) << "Row index out of range.";
        throw 102;
    }
    return DVector(this->xdata_.at(row_ind), this->num_cols());
}

inline const DVector SMatrix::GetCol(int32_t col_ind) const {
    if (col_ind < 0 || col_ind >= this->num_cols()) {
        LOG(ERROR) << "Column index out of range.";
        throw 102;
    }
    DVector dvec = DVector(SVector(), this->num_rows());
    int32_t k = 0;
    for (auto itr = this->xdata_.begin(); itr != this->xdata_.end(); ++itr, ++k) {
        if (itr->GetValue(col_ind) != 0) {
            dvec.Append(k, itr->GetValue(col_ind));
        }
    }
    return dvec;
}

} // namespace cactus

#endif // _CACTUS_CORE_MATRIX_H_
