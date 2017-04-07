//------------------------------------------------------------------------------
// Implementations of Data matrix
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "core/data_matrix.h"

#include <cmath>
#include "glog/logging.h"

namespace cactus {

SMatrix::SMatrix()
        : xdata_(std::vector<SVector>()), num_rows_(0), num_cols_(0) {}

SMatrix::SMatrix(const SMatrix& smat)
        : xdata_(std::vector<SVector>(smat.xdata())), num_rows_(smat.num_rows()),
          num_cols_(smat.num_cols()) {}

SMatrix::~SMatrix() {
    this->xdata_.clear();
}

int32_t SMatrix::Append(const SVector& svec) {
    this->xdata_.push_back(svec);
    this->num_rows_ += 1;
    this->num_cols_ = std::max(this->num_cols(), svec.data().back().index() + 1);
    return 0;
}

int32_t SMatrix::Remove(int32_t row_ind) {
    if (row_ind < 0 || row_ind >= this->num_rows()) {
        LOG(ERROR) << "Row index out of range.";
        throw 102;
    }
    auto ptr = this->xdata_.begin();
    this->xdata_.erase(ptr + row_ind);
    this->num_rows_ -= 1;
    return 0;
}

void SMatrix::Clear() {
    this->xdata_.clear();
    this->num_rows_ = 0;
    this->num_cols_ = 0;
}

DMatrix::DMatrix()
        : SMatrix(), ydata_(std::vector<float>()) {}

DMatrix::DMatrix(const SMatrix& smat, const std::vector<float>& yvec)
        : SMatrix(smat), ydata_(std::vector<float>(yvec)) {}

DMatrix::~DMatrix() {
    this->ydata_.clear();
}

int32_t DMatrix::Append(const SVector& svec, float yval) {
    this->ydata_.push_back(yval);
    return SMatrix::Append(svec);
}

int32_t DMatrix::Remove(int32_t row_ind) {
    int32_t ec = SMatrix::Remove(row_ind);
    if (ec == 0) {
        auto ptr = this->ydata_.begin();
        this->ydata_.erase(ptr + row_ind);
    }
    return ec;
}

void DMatrix::Clear() {
    SMatrix::Clear();
    this->ydata_.clear();
}

void print(const SMatrix& smat) {
    int32_t k = 0;
    for (auto itr = smat.xdata().begin(); itr != smat.xdata().end(); ++itr, ++k) {
        if (k < 5 || smat.num_rows() - k <= 5) {
            std::cout << "[" << k << "]\t";
            print(*itr);
        }
    }
}

} // namespacecactus
