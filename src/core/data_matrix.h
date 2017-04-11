//------------------------------------------------------------------------------
// Data matrix - structures of SMatrix and DMatrix
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#ifndef _CACTUS_CORE_DATA_MATRIX_H_
#define _CACTUS_CORE_DATA_MATRIX_H_

#include <cstdint>
#include <vector>
#include <iostream>
#include "glog/logging.h"

#include "core/data_vector.h"

namespace cactus {

/*
 * Sparse matrix of Entries
 * 
 * Rows are densely stored by sparse vector of Entries
 */
class SMatrix {
  protected:
    std::vector<SVector> xdata_;
    int32_t num_rows_;
    int32_t num_cols_;

  public:
    SMatrix();
    virtual ~SMatrix();
    SMatrix(const SMatrix& smat);

  public:
    inline int32_t num_rows() const;
    inline int32_t num_cols() const;
    inline const std::vector<SVector>& xdata() const;

    inline const DVector GetRow(int32_t row_ind) const;
    inline const DVector GetCol(int32_t col_ind) const;

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


/*
 * Data matrix of Entries with corresponding labels
 */
class DMatrix : public SMatrix {
  private:
    std::vector<float> ydata_;

  public:
    DMatrix();
    virtual ~DMatrix();
    DMatrix(const SMatrix& smat, const std::vector<float>& yvec);

  public:
    inline const std::vector<float>& ydata() const;
    
    inline float GetY(int32_t row_ind) const;
    virtual int32_t Append(const SVector& svec, float yval);
    virtual int32_t Remove(int32_t row_ind);
    virtual void Clear();
};

inline const std::vector<float>& DMatrix::ydata() const {
    return this->ydata_;
}

inline float DMatrix::GetY(int32_t row_ind) const {
    if (row_ind < 0 || row_ind >= this->num_rows()) {
        LOG(ERROR) << "Row index out of range.";
        throw 102;
    }
    return this->ydata_.at(row_ind);
}

void print(const SMatrix& smat);

} // namespace cactus

#endif // _CACTUS_CORE_DATA_MATRIX_H_
