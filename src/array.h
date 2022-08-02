#ifndef SRC_ARRAY_H_
#define SRC_ARRAY_H_

namespace s21 {
template<class T, size_t size>
class array : public BaseClassVecArr<T> {
    using value_type = T;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using iterator = T *;
    using const_iterator = const T *;

 public:
    array();
    array(std::initializer_list <value_type> const &items);
    array(const array &a);
    array(array &&a);
    ~array() { fill(0); }
    array &operator=(array &&a);
    iterator data() const { return begin(); }
    [[nodiscard]] iterator begin() const { return this->arr_; }
    [[nodiscard]] iterator end() const { return this->arr_ + size; }
    void swap(array &other);
    void fill(const_reference value);

    iterator iter = arr_static_;
    const_iterator const_iter = arr_static_;

 private:
    void Check_Size();
    void Copy_Array(const T *arr);
    void Generic_Initialization();
    value_type arr_static_[size];
};
}  // namespace s21

#include "array.cpp"

#endif  // SRC_ARRAY_H_
