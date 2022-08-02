#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include "abstract_list.h"

namespace s21 {
template <class T>
class list : public AbstractList<T>::AbstractList {
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

 public:
    list() : AbstractList<T>::AbstractList() {}
    explicit list(size_type n) : AbstractList<T>::AbstractList(n) {}
    list(std::initializer_list<value_type> const& items)
        : AbstractList<T>::AbstractList(items) {}
    explicit list(const AbstractList<value_type>& l)
        : AbstractList<T>::AbstractList(l) {}
    explicit list(AbstractList<value_type>&& l) : AbstractList<T>::AbstractList(l) {}

 private:
    void push(const_reference value);
};
}  // namespace s21

#endif  // SRC_LIST_H_
