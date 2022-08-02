
namespace s21 {


//---- Set Private Methods ----//
template<class value_type>
typename set<value_type>::Item *set<value_type>::CreateItem(const value_type data) {
    Item *new_item = new Item;
    new_item->data = data;
    new_item->left = nullptr;
    new_item->right = nullptr;
    return new_item;
}

template<class value_type>
typename set<value_type>::Item *set<value_type>::
PushItem(const value_type data, Item *node, bool &was_insert) {
    if (!node)
        return CreateItem(data);
    else if (data == node->data)
        was_insert = false;
    else if (data < node->data)
        node->left = PushItem(data, node->left, was_insert);
    else
        node->right = PushItem(data, node->right, was_insert);
    return node;
}

template<class value_type>
void set<value_type>::DeleteAllItems(Item *ptr) {
    if (ptr) {
        DeleteAllItems(ptr->left);
        DeleteAllItems(ptr->right);
        delete ptr;
    }
}

template<class value_type>
void set<value_type>::CopyItems(Item *other_root) {
    if (other_root) {
        bool was_insert = true;
        root_ = PushItem(other_root->data, root_, was_insert);
        CopyItems(other_root->left);
        CopyItems(other_root->right);
    }
}

template<class value_type>
bool set<value_type>::CompareBinaryTrees(Item *first_root, Item *second_root) const {
    if (first_root == nullptr && second_root == nullptr)
        return true;
    if ((first_root && !second_root) || !first_root)
        return false;
    if (first_root->data == second_root->data &&
        CompareBinaryTrees(first_root->left, second_root->left) &&
        CompareBinaryTrees(first_root->right, second_root->right)) {
        return true;
    }
    return false;
}

template<class value_type>
void set<value_type>::SetEmptyTree() {
    root_ = nullptr;
    number_of_items_ = 0;
}


//---- Set Member functions ----//
template<class value_type>
set<value_type>::set() {
    SetEmptyTree();
}

template<class value_type>
set<value_type>::set(std::initializer_list <value_type> const &items) {
    SetEmptyTree();
    for (auto it = items.begin(); it != items.end(); it++) {
        bool was_insert = true;
        root_ = this->PushItem(*it, root_, was_insert);
        if (was_insert)
            number_of_items_++;
    }
}


template<class value_type>
set<value_type>::set(const set &s) {
    SetEmptyTree();
    *this = s;
}

template<class value_type>
set<value_type>::set(set &&s) {
    root_ = nullptr;
    number_of_items_ = 0;
    *this = std::move(s);
}

template<class value_type>
set<value_type>::~set() {
    DeleteAllItems(root_);
    SetEmptyTree();
}

template<class value_type>
typename set<value_type>::set &set<value_type>::operator=(const set &s) {
    DeleteAllItems(root_);
    root_ = nullptr;
    number_of_items_ = s.number_of_items_;
    CopyItems(s.root_);
    return *this;
}

template<class value_type>
typename set<value_type>::set &set<value_type>::operator=(set &&s) {
    if (s.root_ != nullptr) {
        DeleteAllItems(this->root_);
        this->root_ = s.root_;
        this->number_of_items_ = s.number_of_items_;
        s.root_ = nullptr;
        s.number_of_items_ = 0;
    }
    return *this;
}

template<class value_type>
bool set<value_type>::operator==(const set &s) const {
    return CompareBinaryTrees(root_, s.root_);
}

template<class value_type>
bool set<value_type>::operator!=(const set &s) const {
    return !CompareBinaryTrees(root_, s.root_);
}

//---- Set Iterators ----//
template<class value_type>
typename set<value_type>::iterator set<value_type>::begin() const {
    iterator it;
    it.ConvertBtreeToArr(root_, number_of_items_);
    it.SetIteratorBegin();
    return it;
}

template<class value_type>
typename set<value_type>::iterator set<value_type>::end() const {
    iterator it;
    it.ConvertBtreeToArr(root_, number_of_items_);
    it.SetIteratorEnd();
    return it;
}

template<class value_type>
typename set<value_type>::const_iterator set<value_type>::cbegin() const {
    const_iterator it;
    it.ConvertBtreeToArr(root_, number_of_items_);
    it.SetIteratorBegin();
    return it;
}

template<class value_type>
typename set<value_type>::const_iterator set<value_type>::cend() const {
    const_iterator it;
    it.ConvertBtreeToArr(root_, number_of_items_);
    it.SetIteratorEnd();
    return it;
}



//---- Set Modifiers ----//

template<class value_type>
void set<value_type>::clear() {
    DeleteAllItems(root_);
    SetEmptyTree();
}

template<class value_type>
std::pair<typename set<value_type>::iterator, bool> set<value_type>::insert(value_type data) {
    bool was_insert = true;
    root_ = PushItem(data, root_, was_insert);
    std::pair<iterator, bool> p;
    if (was_insert)
        number_of_items_++;
    p.first = this->find(data);
    p.second = was_insert;
    return p;
}

template<class value_type>
void set<value_type>::erase(iterator &pos) {
    set new_set;
    int index = 0;
    int was_erase = 0, erase_index = 0;
    for (auto it = this->begin(); it != this->end(); it++, index++) {
        if (it == pos) {
            was_erase = 1;
            erase_index = index;
            continue;
        }
        new_set.insert(*it);
    }
    *this = new_set;
    if (was_erase) {
        pos = this->begin();
        for (int i = 0; i < erase_index; i++)
            pos++;
    } else {
        pos = this->end();
    }
}

template<class value_type>
void set<value_type>::swap(set &other) {
    set tmp(other);
    other = (*this);
    *this = tmp;
}

template<class value_type>
void set<value_type>::merge(set &other) {
    if (root_ != other.root_ && other.root_) {
        for (auto it = other.begin(); it != other.end(); it++)
            this->insert(*it);
    }
}


//---- Set Lookup ----//
template<class value_type>
bool set<value_type>::contains(const value_type &key) const {
    if (root_) {
        for (iterator it((*this).begin()); it != (*this).end(); it++)
            if (*it == key) return true;
    }
    return false;
}

template<class value_type>
typename set<value_type>::iterator set<value_type>::find(const value_type &key) const {
    iterator it;
    for (it = this->begin(); it != this->end(); it++)
        if (*it == key) break;
    return it;
}

template<class value_type>
template<class ... Args>
std::pair<typename set<value_type>::iterator, bool> set<value_type>::emplace(Args &&... args) {
    std::pair<iterator, bool> p = insert(value_type({args...}));
    return p;
}


//####### Multiset class #######//
template<class value_type>
typename multiset<value_type>::Item *
multiset<value_type>::PushItem(const value_type data, Item *node, bool &was_insert) {
    if (!node)
        return this->CreateItem(data);
    else if (data < node->data)
        node->left = PushItem(data, node->left, was_insert);
    else
        node->right = PushItem(data, node->right, was_insert);
    if (was_insert) { ; }
    return node;
}


//####### Set Iterator #######//
template<class value_type>
void set<value_type>::const_iterator::SetPointersNull() {
    array_ = nullptr;
    arr_begin_ = nullptr;
    arr_end_ = nullptr;
    current_ = nullptr;
}

template<class value_type>
void set<value_type>::const_iterator::CreateArray(int nmb_of_items) {
    array_ = new Item *[nmb_of_items + 1];
    arr_begin_ = array_;
    arr_end_ = array_ + nmb_of_items;
    (*arr_end_) = nullptr;
}

template<class value_type>
void set<value_type>::const_iterator::CopyOtherIterator(const const_iterator &it) {
    if (it.array_) {
        int nmb_of_items = it.arr_end_ - it.arr_begin_;
        CreateArray(nmb_of_items);
        for (int i = 0; i < nmb_of_items; i++)
            array_[i] = it.array_[i];
        current_ = arr_begin_ + (it.current_ - it.arr_begin_);
    } else {
        SetPointersNull();
    }
}

template<class value_type>
void set<value_type>::const_iterator::FreeMemory() {
    if (array_) {
        delete[] array_;
        array_ = nullptr;
    }
    if (error_value_) {
        delete error_value_;
        error_value_ = nullptr;
    }
}

template<class value_type>
set<value_type>::const_iterator::SetConstIterator() {
    SetPointersNull();
    error_value_ = new value_type();
}

template<class value_type>
set<value_type>::const_iterator::SetConstIterator(const const_iterator &it) {
    CopyOtherIterator(it);
    error_value_ = new value_type();
}

template<class value_type>
set<value_type>::const_iterator::SetConstIterator(const iterator &it) {
    CopyOtherIterator(it);
    error_value_ = new value_type();
}

template<class value_type>
set<value_type>::const_iterator::~SetConstIterator() {
    FreeMemory();
}

template<class value_type>
void set<value_type>::const_iterator::AddNodesToArray(Item *node, int &cur_index) {
    if (node) {
        AddNodesToArray(node->left, cur_index);
        array_[cur_index++] = node;
        AddNodesToArray(node->right, cur_index);
    }
}

template<class value_type>
void set<value_type>::const_iterator::ConvertBtreeToArr(Item *root, size_t nmb_of_items) {
    if (root && array_ == nullptr) {
        CreateArray(nmb_of_items);
        int index = 0;
        AddNodesToArray(root, index);
    }
}

template<class value_type>
const value_type &set<value_type>::const_iterator::operator*() const {
    if (array_ && current_ != arr_end_)
        return (*current_)->data;
    else
        return *error_value_;
}

template<class value_type>
typename set<value_type>::const_iterator &set<value_type>::const_iterator::operator++() {
    if (current_ == arr_end_)  // When using iterator++ at end point, it returns to last item
        current_ -= 1;
    else
        current_ += 1;
    return (*this);
}

template<class value_type>
typename set<value_type>::const_iterator &set<value_type>::const_iterator::operator--() {
    if (current_ != arr_begin_)
        current_ -= 1;
    return (*this);
}

template<class value_type>
typename set<value_type>::const_iterator set<value_type>::const_iterator::operator++(int) {
    const_iterator prev_state((*this));
    operator++();
    return prev_state;
}

template<class value_type>
typename set<value_type>::const_iterator set<value_type>::const_iterator::operator--(int) {
    const_iterator prev_state((*this));
    operator--();
    return prev_state;
}

template<class value_type>
bool set<value_type>::const_iterator::operator==(const const_iterator &it) const {
    if ((this->array_ && !it.array_) || (!this->array_ && it.array_)) {
        return false;
    } else if (!this->array_ && !it.array_) {
        return true;
    } else {
        return (this->arr_begin_[0] == it.arr_begin_[0] &&
                ((this->arr_end_ - this->current_) == (it.arr_end_ - it.current_)));
    }
}

template<class value_type>
bool set<value_type>::const_iterator::operator!=(const const_iterator &it) const {
    return !(operator==(it));
}

template<class value_type>
typename set<value_type>::const_iterator &set<value_type>::const_iterator::
operator=(const const_iterator &it) {
    FreeMemory();
    CopyOtherIterator(it);
    error_value_ = new value_type();
    return (*this);
}

}  // namespace s21
