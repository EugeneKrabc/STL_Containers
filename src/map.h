#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "set.h"

namespace s21 {
template <class Key, class T>
class map : public set<std::pair<Key, T>> {
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<key_type, mapped_type>;
    using Item = typename set<value_type>::Item;

 private:
    Item* PushItem(const value_type data, Item* node, bool& was_insert);
    bool CompareBinaryTrees(Item* first_root, Item* second_root) const;

 public:
    map() : set<value_type>::set() {}
    map(std::initializer_list<value_type> const& items) : set<value_type>::set(items) {}
    explicit map(const set<value_type>& s) : set<value_type>::set(s) {}
    explicit map(set<value_type>&& s) : set<value_type>::set(s) {}

    std::pair<typename map<Key, T>::iterator, bool> insert(value_type data);
    typename map<Key, T>::iterator find(const Key& key) const;
    bool contains(const Key& key) const;

    class MapIterator;
    using iterator = MapIterator;
    class MapConstIterator;
    using const_iterator = MapConstIterator;

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    void erase(iterator& pos);
    T& at(const Key& key);
    T& operator[](const Key& key);

    template <class ... Args>
    std::pair<typename map<Key, T>::iterator, bool> emplace(Args&&... args);
};



//####### MapConstIterator class #######//
template <class Key, class T>
class map<Key, T>::MapConstIterator : public set<std::pair<Key, T>>::SetConstIterator {
 public:
    MapConstIterator() : set<std::pair<Key, T>>::SetConstIterator() {}
    MapConstIterator(const const_iterator& cit) : set<std::pair<Key, T>>::SetConstIterator(cit) {}

    const_iterator& operator=(const const_iterator& it);
};


//####### MapIterator class #######//
template <class Key, class T>
class map<Key, T>::MapIterator : public MapConstIterator {
 public:
    MapIterator() : MapConstIterator() {}
    MapIterator(const iterator& it) : MapConstIterator(it) {}

    value_type& operator*() const;
    iterator& operator=(const iterator& it);
};

}  // namespace s21

#include "map.cpp"

#endif  // SRC_MAP_H_
