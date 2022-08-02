#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>

#include "base_vec_arr.h"
#include "array.h"

namespace s21 {
template <typename T>
class vector : public BaseClassVecArr<T> {
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

 public:
    class VectorConstIterator;
    using const_iterator = VectorConstIterator;
    class VectorIterator;
    using iterator = VectorIterator;

    vector() { Zero_All_Data(); }
    explicit vector(const size_type n);
    vector(std::initializer_list<value_type> const &items);
    vector(const vector &v);
    vector(vector &&v);
    ~vector() { clear(); }
    vector operator=(vector &&v);

    iterator data() const { return begin(); }
    [[nodiscard]] iterator begin() const;
    [[nodiscard]] iterator end() const;
    void reserve(size_type size);
    [[nodiscard]] size_type capacity() const { return capacity_var_; }
    void shrink_to_fit();
    void clear();
    iterator insert(iterator& pos, const_reference value);
    void erase(iterator& pos);
    void push_back(const_reference value);
    void pop_back();
    void swap(vector& other);

    template <typename ...Args>
    iterator emplace(const const_iterator pos, Args&&... args);
    template <typename ...Args>
    void emplace_back(Args&&... args);

 private:
    void Allocate_Memory();
    void Copy_Array(const value_type* arr, size_type end, int ignore = -1);
    void Zero_All_Data();

    size_type capacity_var_;
};

template <class T>
class vector<T>::VectorConstIterator {
 public:
    VectorConstIterator();
    VectorConstIterator(const const_iterator &other);
    VectorConstIterator(const iterator &not_const);
    VectorConstIterator(const vector &vec, size_type cur_pos);

    [[nodiscard]] T operator*() const;
    const_iterator& operator==(const const_iterator &other) const;
    const_iterator& operator!=(const const_iterator &other) const;
    const_iterator& operator++();
    const_iterator& operator--();
    const_iterator operator++(int);
    const_iterator operator--(int);

 protected:
    value_type *iter_arr_;
    size_type cur_pos_;
    size_type max_elem_;

 private:
    friend void vector::erase(iterator& pos);
    friend vector::iterator
    vector::insert(iterator& pos, const_reference value);
};

template <class T>
class vector<T>::VectorIterator : public vector<T>::VectorConstIterator {
 public:
    VectorIterator(const vector &vec, size_type cur_pos);
    VectorIterator(const const_iterator &other);
    VectorIterator();

    iterator& operator=(const const_iterator &other);
    [[nodiscard]] reference operator*() const;
};
}  // namespace s21

#include "vector.cpp"

#endif  //  SRC_VECTOR_H_
