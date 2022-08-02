#ifndef SRC_BASE_VEC_ARR_H_
#define SRC_BASE_VEC_ARR_H_

namespace s21 {

const unsigned long int MAX_ALLOCATED = 9223372036854775808U;

template <typename T>
class BaseClassVecArr {
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

 public:
    [[nodiscard]] reference at(size_type at) const;
    reference operator[](size_type pos) const;
    const_reference front() const;
    const_reference back() const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_type size() const;
    [[nodiscard]] unsigned long max_size() const;

 protected:
    BaseClassVecArr() {}

    value_type* arr_;
    size_type size_;
};
}  // namespace s21

#include "base_vec_arr.cpp"

#endif  // SRC_BASE_VEC_ARR_H_
