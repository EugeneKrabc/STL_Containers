namespace s21 {
template <class T>
class AbstractList<T>::ListIterator {
 private:
    friend ListIterator AbstractList<T>::insert(iterator pos,
                                                 const_reference value);
    friend void AbstractList<T>::erase(ListIterator pos);
    friend void AbstractList<T>::reverse();
    friend void AbstractList<T>::unique();

 protected:
    Node* ptr_;
    value_type itr_value_;

 public:
    ListIterator();
    ~ListIterator();
    value_type& operator*();
    void operator=(Node& node);
    void operator++();
    void operator--();
    bool operator==(const ListIterator& other);
    bool operator!=(const ListIterator& other);
};
template <class T>
class AbstractList<T>::ListConstIterator : public ListIterator {
 public:
    const value_type& operator*() { return ListIterator::operator*(); }
};

template <class T>
AbstractList<T>::iterator::ListIterator() {
    this->ptr_ = nullptr;
    itr_value_ = value_type();
}
template <class T>
AbstractList<T>::iterator::~ListIterator() {
    this->ptr_ = nullptr;
}
template <class T>
typename AbstractList<T>::value_type& AbstractList<T>::iterator::operator*() {
    value_type& return_value = ptr_ ? ptr_->value : itr_value_;
    return return_value;
}
template <class T>
bool AbstractList<T>::iterator::operator==(const ListIterator& other) {
    return this->ptr_ ? other.ptr_ ? (this->ptr_->value == other.ptr_->value)
                                   : (this->ptr_->value == other.itr_value_)
                      : (this->itr_value_ == other.itr_value_);
}
template <class T>
bool AbstractList<T>::iterator::operator!=(const ListIterator& other) {
    return this->ptr_ ? other.ptr_ ? (this->ptr_->value != other.ptr_->value)
                                   : (this->ptr_->value != other.itr_value_)
                      : (this->itr_value_ != other.itr_value_);
}
template <class T>
void AbstractList<T>::iterator::operator=(Node& node) {
    this->ptr_ = &node;
    this->itr_value_ = node.value;
}
template <class T>
void AbstractList<T>::iterator::operator++() {
    if (this->ptr_) {
        if (this->ptr_->next || this->ptr_->prev) {
            if (this->ptr_->next) {
                this->ptr_ = this->ptr_->next;
                this->itr_value_ = this->ptr_->Node::value;
            } else {
                while (this->ptr_->prev) {
                    this->ptr_ = this->ptr_->prev;
                    this->itr_value_ = this->ptr_->Node::value;
                }
            }
        }
    }
}
template <class T>
void AbstractList<T>::iterator::operator--() {
    if (this->ptr_) {
        if (this->ptr_->next || this->ptr_->prev) {
            if (this->ptr_->prev) {
                this->ptr_ = this->ptr_->prev;
                this->itr_value_ = this->ptr_->Node::value;
            } else {
                while (this->ptr_->next) {
                    this->ptr_ = this->ptr_->next;
                    this->itr_value_ = this->ptr_->Node::value;
                }
            }
        }
    }
}

//=========================================================================
// List Functions
//=========================================================================
template <class T>
AbstractList<T>::AbstractList() {
    this->head_ = this->tail_ = new Node;
    this->head_->prev = this->head_->next = nullptr;
    this->head_->value = value_type();
}
template <class T>
AbstractList<T>::AbstractList(size_type n) {
    if (n == 0) {
        this->DefaultConstructor();
    } else {
        this->head_ = new Node;
        this->head_->prev = this->head_->next = nullptr;
        Node* tmp = this->head_;
        for (; n > 0; n--) {
            this->CreateEmptyNode(tmp);
        }
        this->tail_ = tmp;
    }
}
template <class T>
AbstractList<T>::AbstractList(
    std::initializer_list<value_type> const& items) {
    if (items.size() == 0) {
        this->DefaultConstructor();
    } else {
        this->head_ = this->tail_ = new Node;
        this->head_->prev = this->head_->next = nullptr;
        Node* tmp = this->head_;
        auto i = items.begin();
        for (auto element : items) {
            tmp->value = element;
            CreateNewNode(tmp);
            i++;
        }
        this->tail_ = tmp;
    }
}
template <class T>
AbstractList<T>::AbstractList(const AbstractList& l) {
    CopyConstructor(l);
}
template <class T>
AbstractList<T>::AbstractList(AbstractList&& l) {
    if (this != &l) {
        this->head_ = l.head_;
        this->tail_ = l.tail_;
        l.head_ = l.tail_ = nullptr;
    }
}
template <class T>
AbstractList<T>::~AbstractList() {
    this->clear();
    delete this->head_;
}
template <class T>
const AbstractList<T>& AbstractList<T>::operator=(AbstractList& l) {
    if (this != &l) {
        this->clear();
        delete this->head_;
        this->CopyConstructor(l);
    }
    return *this;
}
template <class T>
bool AbstractList<T>::operator==(const AbstractList& other) {
    bool return_value = true;
    if (this != &other) {
        Node* tmp = this->head_;
        Node* tmp2 = other.head_;
        while (tmp || tmp2) {
            if ((((tmp == nullptr || tmp2 == nullptr) &&
                  !(tmp == nullptr && tmp2 == nullptr))) ||
                tmp->value != tmp2->value) {
                return_value = false;
                break;
            }
            tmp = tmp->next;
            tmp2 = tmp2->next;
        }
    }
    return return_value;
}

template <class T>
void AbstractList<T>::DefaultConstructor() {
    this->head_ = this->tail_ = new Node;
    this->head_->prev = this->head_->next = nullptr;
    this->head_->value = value_type();
}
template <class T>
void AbstractList<T>::CopyConstructor(const AbstractList& l) {
    if (this != &l) {
        if (l.head_ != l.tail_) {
            this->head_ = new Node;
            this->head_->prev = this->head_->next = nullptr;
            Node* tmp = this->head_;
            Node* l_tmp = l.head_;
            while (l_tmp) {
                tmp->value = l_tmp->value;
                if (l_tmp->next) {
                    CreateNewNode(tmp);
                    l_tmp = l_tmp->next;
                } else {
                    break;
                }
            }
            this->tail_ = tmp;
        } else {
            this->head_ = this->tail_ = new Node;
            this->head_->prev = this->head_->next = nullptr;
            this->head_->value = l.head_->value;
        }
    }
}
template <class T>
void AbstractList<T>::CreateNewNode(Node*& tmp) {
    tmp->next = new Node;
    tmp->next->prev = tmp;
    tmp = tmp->next;
    tmp->next = nullptr;
}
template <class T>
void AbstractList<T>::CreateEmptyNode(Node*& tmp) {
    tmp->value = value_type();
    CreateNewNode(tmp);
}

//=========================================================================
// List Element access
//=========================================================================
template <class T>
typename AbstractList<T>::const_reference AbstractList<T>::front() const {
    return this->head_->value;
}
template <class T>
typename AbstractList<T>::const_reference AbstractList<T>::back() const {
    return this->tail_->prev ? this->tail_->prev->value
                              : this->tail_->value;
}

//=========================================================================
// List Iterators
//=========================================================================
template <class T>
typename AbstractList<T>::iterator AbstractList<T>::begin() const {
    iterator itr;
    itr = *this->head_;
    return itr;
}
template <class T>
typename AbstractList<T>::iterator AbstractList<T>::end() const {
    iterator itr;
    itr = *this->tail_;
    return itr;
}

//=========================================================================
// List Capacity
//=========================================================================
template <class T>
bool AbstractList<T>::empty() const {
    return (this->head_ == this->tail_);
}
template <class T>
typename AbstractList<T>::size_type AbstractList<T>::size() const {
    size_type counter = 0;
    if (this->head_ != this->tail_) {
        Node* tmp = this->head_;
        while (tmp->next) {
            tmp = tmp->next;
            counter++;
        }
    }
    return counter;
}
template <class T>
typename AbstractList<T>::size_type AbstractList<T>::max_size() const {
    int x = (int)((7 + sizeof(value_type)) / 8);
    return MAX_SIZE / x;
}

//=========================================================================
// List Modifiers
//=========================================================================
template <class T>
void AbstractList<T>::clear() {
    if (this->head_ != this->tail_) {
        Node* tmp = this->head_;
        while (tmp->next) {
            Node* tmp2 = tmp->next;
            delete tmp;
            tmp = tmp2;
        }
        this->tail_->value = value_type();
        this->head_ = this->tail_;
    }
}
template <class T>
typename AbstractList<T>::iterator AbstractList<T>::insert(
    iterator pos, const_reference value) {
    Node* tmp = new Node;
    tmp->next = pos.ptr_;
    if ((pos.ptr_)->prev) {
        tmp->prev = pos.ptr_->prev;
        pos.ptr_->prev->next = tmp;
    } else {
        this->head_ = tmp;
        tmp->prev = nullptr;
    }
    pos.ptr_->prev = tmp;

    tmp->value = value;
    iterator return_value;
    return_value = *tmp;
    return return_value;
}
template <class T>
void AbstractList<T>::erase(iterator pos) {
    if (pos.ptr_->next || pos.ptr_->prev) {
        if (pos.ptr_->next && pos.ptr_->prev) {
            pos.ptr_->prev->next = pos.ptr_->next;
            pos.ptr_->next->prev = pos.ptr_->prev;
        } else if (pos.ptr_->next) {
            this->head_ = pos.ptr_->next;
            pos.ptr_->next->prev = nullptr;
        } else if (pos.ptr_->prev) {
            pos.ptr_->prev->next = nullptr;
        } else {
            this->head_ = this->tail_ = nullptr;
        }
        delete pos.ptr_;
    }
}
template <class T>
void AbstractList<T>::push_back(const_reference value) {
    iterator itr = this->end();
    this->insert(itr, value);
}
template <class T>
void AbstractList<T>::pop_back() {
    iterator itr;
    itr = this->end();
    --itr;
    this->erase(itr);
}
template <class T>
void AbstractList<T>::push_front(const_reference value) {
    iterator itr = this->begin();
    this->insert(itr, value);
}
template <class T>
void AbstractList<T>::pop_front() {
    iterator itr;
    itr = this->begin();
    this->erase(itr);
}
template <class T>
void AbstractList<T>::swap(AbstractList& other) {
    if (this != &other) {
        AbstractList tmp(*this);
        this->clear();
        delete this->head_;
        this->CopyConstructor(other);
        other.clear();
        delete other.head_;
        other.CopyConstructor(tmp);
    }
}
template <class T>
void AbstractList<T>::merge(AbstractList& other) {
    iterator itr;
    for (itr = other.begin(); itr != other.end(); ++itr) {
        this->push_back(*itr);
    }
}
template <class T>
void AbstractList<T>::splice(iterator pos, AbstractList& other) {
    iterator itr;
    for (itr = other.begin();
    itr != other.end();
    ++itr) {
        this->insert(pos, *itr);
    }
}
template <class T>
void AbstractList<T>::reverse() {
    if (this->size() > 1) {
        iterator itr_begin, itr_end;
        itr_begin = this->begin();
        itr_end = this->end();
        --itr_end;
        for (; itr_begin.ptr_->prev != itr_end.ptr_ &&
               itr_begin.ptr_ != itr_end.ptr_;
             ++itr_begin, --itr_end) {
            value_type tmp = itr_begin.ptr_->value;
            itr_begin.ptr_->value = itr_end.ptr_->value;
            itr_end.ptr_->value = tmp;
        }
    }
}
template <class T>
void AbstractList<T>::unique() {
    if (this->size() > 1) {
        iterator itr_begin, itr_end;
        itr_begin = this->begin();
        itr_end = this->end();
        iterator itr_cnt;
        for (itr_cnt = this->begin(); itr_cnt.ptr_ != itr_end.ptr_; ++itr_cnt) {
            iterator element = itr_cnt;
            ++element;
            while (element.ptr_ != itr_end.ptr_) {
                if (itr_cnt.itr_value_ == element.itr_value_) {
                    iterator tmp;
                    ++element;
                    tmp = element;
                    --tmp;
                    this->erase(tmp);
                } else {
                    ++element;
                }
            }
        }
    }
}
// bubble sort is implemented, since there is no access to the AbstractList
// elements by indexes.
template <class T>
void AbstractList<T>::sort() {
    size_type size = this->size();
    if (size > 1) {
        for (size_type i = 0; i < size; i++) {
            Node* tmp_node_ptr = this->head_;
            for (size_type j = 0; j < size - 1; j++) {
                if (tmp_node_ptr->value > tmp_node_ptr->next->value) {
                    value_type tmp_value = tmp_node_ptr->value;
                    tmp_node_ptr->value = tmp_node_ptr->next->value;
                    tmp_node_ptr->next->value = tmp_value;
                }
                tmp_node_ptr = tmp_node_ptr->next;
            }
        }
    }
}
template <class T>
void AbstractList<T>::push(const_reference value) {
    this->push_back(value);
}
template <class T>
template <typename... Args>
typename AbstractList<T>::iterator AbstractList<T>::emplace(iterator pos,
                                                              Args&&... args) {
    return this->insert(pos, value_type(std::forward<Args>(args)...));
}
template <class T>
template <typename... Args>
void AbstractList<T>::emplace_back(Args&&... args) {
    iterator itr;
    itr = this->end();
    this->emplace(itr, args...);
}
template <class T>
template <typename... Args>
void AbstractList<T>::emplace_front(Args&&... args) {
    iterator itr;
    itr = this->begin();
    this->emplace(itr, args...);
}
}  // namespace s21
