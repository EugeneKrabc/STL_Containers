#ifndef SRC_SET_H_
#define SRC_SET_H_
#include <cstddef>
#include <cstring>
#include <utility>
#include <iostream>

#define MAX_SIZE 230584300921369395

namespace s21 {

//####### Set class #######//
template <class T>
class set {
    using key_type = T;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

 protected:
    struct Item {
        value_type data;
        Item* left;
        Item* right;
    };
    Item* root_;
    size_type number_of_items_;

    Item* CreateItem(const value_type data);
    virtual Item* PushItem(const value_type data, Item* node, bool& was_insert);
    void DeleteAllItems(Item* ptr);
    void CopyItems(Item* other_root);
    virtual bool CompareBinaryTrees(Item* first_root, Item* second_root) const;
    void SetEmptyTree();

 public:
    //---- Set Member functions ----//
    set();
    set(std::initializer_list<value_type> const& items);
    set(const set& s);
    set(set&& s);
    ~set();
    set& operator=(set&& s);
    set& operator=(const set& s);
    bool operator==(const set& s) const;
    bool operator!=(const set& s) const;


    //---- Set Iterators ----//
    class SetIterator;
    using iterator = SetIterator;
    class SetConstIterator;
    using const_iterator = SetConstIterator;
    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    //---- Set Capacity ----//
    bool empty() const { return root_ == nullptr; }
    size_t size() const { return number_of_items_; }
    size_t max_size() const { return MAX_SIZE; }

    //---- Set Modifiers ----//
    void clear();
    std::pair<iterator, bool> insert(value_type data);
    void erase(iterator& pos);
    void swap(set& other);
    void merge(set& other);

    //---- Set Lookup ----//
    virtual iterator find(const value_type& key) const;
    virtual bool contains(const value_type& key) const;

    template <class... Args>
    std::pair<iterator, bool> emplace(Args&&... args);
};


//####### Multiset class #######//
template <class value_type>
class multiset : public set<value_type> {
    using Item = typename set<value_type>::Item;
 private:
    Item* PushItem(const value_type data, Item* node, bool& was_insert);

 public:
    multiset() : set<value_type>::set() {}
    multiset(std::initializer_list<value_type> const& items) : set<value_type>::set(items) {}
    explicit multiset(const set<value_type>& s) : set<value_type>::set(s) {}
    explicit multiset(set<value_type>&& s) : set<value_type>::set(s) {}
};



//####### SetConstIterator class #######//
template <class value_type>
class set<value_type>::SetConstIterator {
 protected:
    Item** array_;
    Item** arr_begin_;
    Item** arr_end_;
    Item** current_;
    value_type* error_value_;

    void SetPointersNull();
    void CreateArray(int nmb_of_items);
    void CopyOtherIterator(const const_iterator& it);
    void AddNodesToArray(Item* root, int& cur_index);
    void FreeMemory();

 public:
    SetConstIterator();
    SetConstIterator(const const_iterator& it);
    SetConstIterator(const iterator& it);
    ~SetConstIterator();

    const_iterator& operator++();
    const_iterator& operator--();
    const_iterator operator++(int);
    const_iterator operator--(int);
    const value_type& operator*() const;

    bool operator==(const const_iterator& it) const;
    bool operator!=(const const_iterator& it) const;
    const_iterator& operator=(const const_iterator& it);
    void ConvertBtreeToArr(Item* root, size_t nmb_of_items);
    void SetIteratorBegin() { current_ = arr_begin_; }
    void SetIteratorEnd() { current_ = arr_end_; }
};


//####### SetIterator class #######//
template <class value_type>
class set<value_type>::SetIterator : public SetConstIterator {
 public:
    SetIterator() : SetConstIterator() {}
    SetIterator(const const_iterator& cit) : SetConstIterator(cit) {}
};

}  // namespace s21

#include "set.cpp"

#endif  // SRC_SET_H_
