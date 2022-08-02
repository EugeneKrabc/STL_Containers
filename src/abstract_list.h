#ifndef SRC_ABSTRACT_LIST_H_
#define SRC_ABSTRACT_LIST_H_

#include <string>

namespace s21 {
const unsigned long int MAX_SIZE = 230584300921369395;

template <class T>
class AbstractList {
    //=========================================================================
    // List Member type
    //=========================================================================
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

 protected:
    struct Node {
        value_type value;
        struct Node* next;
        struct Node* prev;
    };
    Node* head_;
    Node* tail_;
    AbstractList();
    explicit AbstractList(size_type n);
    AbstractList(std::initializer_list<value_type> const& items);
    AbstractList(const AbstractList& l);
    AbstractList(AbstractList&& l);
    ~AbstractList();

    void DefaultConstructor();
    void CopyConstructor(const AbstractList& l);
    void CreateNewNode(Node*& tmp);
    void CreateEmptyNode(Node*& tmp);

 public:
    class ListConstIterator;
    class ListIterator;

    using iterator = ListIterator;
    using const_iterator = ListConstIterator;

    const AbstractList& operator=(AbstractList& l);
    bool operator==(const AbstractList& other);

    const_reference front() const;
    const_reference back() const;

    iterator begin() const;
    iterator end() const;

    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    void clear();
    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void push_front(const_reference value);
    void pop_front();
    void swap(AbstractList& other);
    void merge(AbstractList& other);
    void splice(iterator pos, AbstractList& other);
    void reverse();
    void unique();
    void sort();

    void push(const_reference value);

    template <typename... Args>
    iterator emplace(iterator pos, Args&&... args);
    template <typename... Args>
    void emplace_back(Args&&... args);
    template <typename... Args>
    void emplace_front(Args&&... args);
};
}  // namespace s21

#include "abstract_list.cpp"

#endif  // SRC_ABSTRACT_LIST_H_
