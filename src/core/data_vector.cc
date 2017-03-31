//------------------------------------------------------------------------------
// Implementations of Data vector
//
// Copyright by del2z <delta.z@aliyun.com>
//------------------------------------------------------------------------------
#include "core/data_vector.h"

#include <cmath>
#include "glog/logging.h"

namespace cactus {

Entry::Entry()
        : index_(-1), value_(nanf("")) {}

Entry::Entry(int32_t index, float value)
        : index_(index), value_(value) {}

Entry::Entry(const Entry& entry)
        : index_(entry.index()), value_(entry.value()) {}

SVector::SVector()
        : data_(std::vector<Entry>()) {}

SVector::SVector(const std::vector<Entry>& svec)
        : data_(std::vector<Entry>(svec)) {}

SVector::SVector(const SVector& svec)
        : data_(std::vector<Entry>(svec.data())) {}

SVector::~SVector() {
    this->data_.clear();
}

float SVector::getValue(int32_t index) const {
    if (index < 0) {
        LOG(ERROR) << "Illegal index '" << index <<
            "' (must be non-negative).";
        throw 101;
    }
    for (auto itr = this->data_.begin(); itr != this->data_.end(); ++itr) {
        if (index == itr->index()) {
            return itr->value();
        } else if (index < itr->index()) {
            return 0;
        }
    }
    return 0;
}

int32_t SVector::append(int32_t index, float value) {
    if (index < 0) {
        LOG(ERROR) << "Illegal index '" << index <<
            "' (must be non-negative).";
        throw 101;
    }
    if (this->data_.empty() || index > this->data_.back().index()) {
        this->data_.push_back(Entry(index, value));
        return 0;
    }
    return 1;
}

int32_t SVector::append(const Entry& entry) {
    return this->append(entry.index(), entry.value());
}

void SVector::clear() {
    this->data_.clear();
}

DVector::DVector()
        : SVector(), size_(0) {}

DVector::DVector(const SVector& svec, int32_t size)
        : SVector(svec) {
    if (size == -1) {
        this->size_ = svec.data().back().index() + 1;
    } else {
        this->size_ = size;
    }
}

DVector::DVector(const DVector& dvec)
        : SVector(dvec.data()), size_(dvec.size()) {}

DVector::~DVector() {
    this->size_ = 0;
}

float DVector::getValue(int32_t index) const {
    if (index < 0 || index >= this->size()) {
        LOG(ERROR) << "Index out of range.";
        throw 102;
    }
    return SVector::getValue(index);
}

int32_t DVector::append(int32_t index, float value) {
    int32_t ec = SVector::append(index, value);
    if (ec == 0) {
        this->size_ = std::max(this->size() + 1, index + 1);
    }
    return ec;
}

int32_t DVector::append(const Entry& entry) {
    return this->append(entry.index(), entry.value());
}

void DVector::clear() {
    SVector::clear();
    this->size_ = 0;
}

void print(const SVector& svec) {
    int32_t k = 0;
    for (auto itr = svec.data().begin(); itr != svec.data().end(); ++itr, ++k) {
        std::cout << "(" << itr->index() << ", " << itr->value() << "), ";
        if ((k + 1) % 10 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

} // namespace cactus
