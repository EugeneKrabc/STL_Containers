

namespace s21 {

template <class Key, class T>
typename map<Key, T>::Item* map<Key, T>::PushItem(const value_type data, Item *node, bool &was_insert) {
    if (!node)
        return this->CreateItem(data);
    else if (data.first < node->data.first)
        node->left = PushItem(data, node->left, was_insert);
    else if (data.first > node->data.first)
        node->right = PushItem(data, node->right, was_insert);
    else if (data.first == node->data.first)
        was_insert = false;
    return node;
}

template <class Key, class T>
bool map<Key, T>::CompareBinaryTrees(Item *first_root, Item *second_root) const {
    if (first_root == nullptr && second_root == nullptr)
        return true;
    if ((first_root && !second_root) || !first_root)
        return false;
    if (first_root->data.first == second_root->data.first &&
        first_root->data.second == second_root->data.second &&
        CompareBinaryTrees(first_root->left, second_root->left) &&
        CompareBinaryTrees(first_root->right, second_root->right)) {
        return true;
    }
    return false;
}

template <class Key, class T>
bool map<Key, T>::contains(const Key &key) const {
    if (this->root_) {
        for (iterator it((*this).begin()); it != (*this).end(); it++)
            if ((*it).first == key) return true;
    }
    return false;
}

template <class Key, class T>
typename map<Key, T>::iterator map<Key, T>::find(const Key &key) const {
    iterator it;
    for (it = this->begin(); it != this->end(); it++)
        if ((*it).first == key) break;
    return it;
}

template <class Key, class T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(std::pair<Key, T> data) {
    bool was_insert = true;
    this->root_ = PushItem(data, this->root_, was_insert);

    std::pair<iterator, bool> p(this->begin(), was_insert);
    if (p.second)
        this->number_of_items_++;
    p.first = this->find(data.first);
    return p;
}

template <class Key, class T>
typename  map<Key, T>::iterator map<Key, T>::begin() const {
    iterator it;
    it.ConvertBtreeToArr(this->root_, this->number_of_items_);
    it.SetIteratorBegin();
    return it;
}

template <class Key, class T>
typename  map<Key, T>::iterator map<Key, T>::end() const {
    iterator it;
    it.ConvertBtreeToArr(this->root_, this->number_of_items_);
    it.SetIteratorEnd();
    return it;
}

template <class Key, class T>
typename  map<Key, T>::const_iterator map<Key, T>::cbegin() const {
    const_iterator it;
    it.ConvertBtreeToArr(this->root_, this->number_of_items_);
    it.SetIteratorBegin();
    return it;
}

template <class Key, class T>
typename  map<Key, T>::const_iterator map<Key, T>::cend() const {
    const_iterator it;
    it.ConvertBtreeToArr(this->root_, this->number_of_items_);
    it.SetIteratorEnd();
    return it;
}

template <class Key, class T>
void map<Key, T>::erase(iterator &pos) {
    map new_map;
    int index = 0;
    int was_erase = 0, erase_index = 0;
    for (auto it = this->begin(); it != this->end(); it++, index++) {
        if (it == pos) {
            was_erase = 1;
            erase_index = index;
            continue;
        }
        new_map.insert(*it);
    }
    *this = new_map;
    if (was_erase) {
        pos = this->begin();
        for (int i = 0; i < erase_index; i++)
            pos++;
    } else {
        pos = this->end();
    }
}

template <class Key, class T>
T& map<Key, T>::at(const Key &key) {
    iterator it = this->find(key);
    if (it == this->end())
        throw std::out_of_range("map::at error: no such key in map\n");
    return (*it).second;
}

template <class Key, class T>
T& map<Key, T>::operator[](const Key &key) {
    iterator it = this->find(key);
    if (it == this->end()) {
        std::pair<iterator, bool> it_pair(it, true);
        std::pair<Key, T> insert_pair(key, 0);
        it_pair = this->insert(insert_pair);
        return (*(it_pair.first)).second;
    }
    return (*it).second;
}

template <class Key, class T>
template <class ... Args>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::emplace(Args &&...args) {
    std::pair<typename map<Key, T>::iterator, bool> p = insert(value_type({args...}));
    return p;
}


//####### MapConstIterator class #######//
template <class Key, class T>
typename map<Key, T>::const_iterator& map<Key, T>::MapConstIterator::operator=(const const_iterator &it) {
    this->FreeMemory();
    this->CopyOtherIterator(it);
    this->error_value_ = new value_type();
    return (*this);
}


//####### MapIterator class #######//
template <class Key, class T>
typename map<Key, T>::value_type& map<Key, T>::MapIterator::operator*() const {
    if (this->array_ && this->current_ != this->arr_end_)
        return (*(this->current_))->data;
    else
        return *(this->error_value_);
}

template <class Key, class T>
typename map<Key, T>::iterator& map<Key, T>::MapIterator::operator=(const iterator &it) {
    this->FreeMemory();
    this->CopyOtherIterator(it);
    this->error_value_ = new value_type();
    return (*this);
}

}  // namespace s21

