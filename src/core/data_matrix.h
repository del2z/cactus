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
    inline const DVector getRow(int32_t row_ind) const;
    inline const DVector getCol(int32_t col_ind) const;

    virtual int32_t append(const SVector& svec);
    virtual int32_t remove(int32_t row_ind);
    virtual void clear();
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

inline const DVector SMatrix::getRow(int32_t row_ind) const {
    if (row_ind < 0 || row_ind >= this->num_rows()) {
        std::cerr << "[ERROR] Row index out of range." << std::endl;
        throw 102;
    }
    return DVector(this->xdata_.at(row_ind), this->num_cols());
}

inline const DVector SMatrix::getCol(int32_t col_ind) const {
    if (col_ind < 0 || col_ind >= this->num_cols()) {
        std::cerr << "[ERROR] Column index out of range." << std::endl;
        throw 102;
    }
    DVector dvec = DVector(SVector(), this->num_rows());
    int32_t k = 0;
    for (auto itr = this->xdata_.begin(); itr != this->xdata_.end(); ++itr, ++k) {
        if (itr->getValue(col_ind) != 0) {
            dvec.append(k, itr->getValue(col_ind));
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
    inline float getY(int32_t row_ind) const;

    virtual int32_t append(const SVector& svec, float yval);
    virtual int32_t remove(int32_t row_ind);
    virtual void clear();
};

inline const std::vector<float>& DMatrix::ydata() const {
    return this->ydata_;
}

inline float DMatrix::getY(int32_t row_ind) const {
    if (row_ind < 0 || row_ind >= this->num_rows()) {
        std::cerr << "[ERROR] Row index out of range." << std::endl;
        throw 102;
    }
    return this->ydata_.at(row_ind);
}

void print(const SMatrix& smat);

} // namespace cactus

#endif // _CACTUS_CORE_DATA_MATRIX_H_
