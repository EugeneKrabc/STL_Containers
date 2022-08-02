#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include "abstract_list.h"

namespace s21 {
template <class T>
class queue : public AbstractList<T>::AbstractList {
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using iterator = typename AbstractList<T>::ListIterator;
    using const_iterator = typename AbstractList<T>::ListConstIterator;

 public:
    queue() : AbstractList<T>::AbstractList() {}
    explicit queue(size_type n) : AbstractList<T>::AbstractList(n) {}
    queue(std::initializer_list<value_type> const& items)
        : AbstractList<T>::AbstractList(items) {}
    explicit queue(const AbstractList<value_type>& l)
        : AbstractList<T>::AbstractList(l) {}
    explicit queue(AbstractList<value_type>&& l) : AbstractList<T>::AbstractList(l) {}

    void pop();

 private:
    iterator begin();
    iterator end();
    size_type max_size();
    void clear();
    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void push_front(const_reference value);
    void pop_front();
    void merge(AbstractList<T>& other);
    void splice(iterator pos, AbstractList<T>& other);
    void reverse();
    void unique();
    void sort();
    template <typename... Args>
    void emplace_front(Args&&... args);
};
}  // namespace s21

#include "queue.cpp"

#endif  // SRC_QUEUE_H_
