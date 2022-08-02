namespace s21 {

    // ***************  Member functions  ******************** //

    template<class value_type>
    vector<value_type>::vector(const size_type n) : capacity_var_(n) {
        this->size_ = 0;
        Allocate_Memory();
    }

    template<class value_type>
    vector<value_type>::vector(std::initializer_list <value_type> const &items) {
        Zero_All_Data();
        if (items.size() == 0) {
            throw std::invalid_argument("Bad size of initializer list");
        } else {
            capacity_var_ = items.size();
            Allocate_Memory();
            for (auto element : items) {
                this->arr_[this->size_++] = element;
            }
        }
    }

    template<class value_type>
    vector<value_type>::vector(const vector &v) : capacity_var_(v.capacity_var_) {
        Allocate_Memory();
        Copy_Array(v.arr_, v.size_);
    }

    template<class value_type>
    vector<value_type>::vector(vector &&v) {
        Zero_All_Data();
        if (this != &v) {
            *this = std::move(v);
        }
    }

    template<class value_type>
    vector<value_type>::const_iterator::VectorConstIterator(const iterator &not_const) {
        this->iter_arr_ = not_const.iter_arr_;
        this->cur_pos_ = not_const.cur_pos_;
        this->max_elem_ = not_const.max_elem_;
    }

    template<class value_type>
    vector<value_type>::const_iterator::VectorConstIterator() {
        this->iter_arr_ = nullptr;
        this->cur_pos_ = this->max_elem_ = 0;
    }

    template<class value_type>
    vector<value_type>::iterator::VectorIterator() : VectorConstIterator() {}

    template<class value_type>
    vector<value_type>::iterator::VectorIterator(const const_iterator &other) :
            VectorConstIterator(other) {}

    template<class value_type>
    vector<value_type>::const_iterator::VectorConstIterator(const const_iterator &other) :
            iter_arr_(other.iter_arr_), cur_pos_(other.cur_pos_), max_elem_(other.max_elem_) {}

    template<class value_type>
    vector<value_type>::const_iterator::VectorConstIterator(const vector &vec, size_type cur_pos) {
        this->iter_arr_ = vec.arr_;
        this->max_elem_ = vec.size_ > 0 ? vec.size_ - 1 : 0;
        this->cur_pos_ = cur_pos;
    }

    template<class value_type>
    vector<value_type>::iterator::VectorIterator(const vector &vec, size_type cur_pos) :
            VectorConstIterator(vec, cur_pos) {
    }

    template<class value_type>
    typename vector<value_type>::iterator&
    vector<value_type>::iterator::operator=(const const_iterator &other) {
        this->iter_arr_ = other.iter_arr_;
        this->cur_pos_ = other.cur_pos_;
        this->max_elem_ = other.max_elem_;
        return *this;
    }

    template<class value_type>
    vector <value_type> vector<value_type>::operator=(vector &&v) {
        if (this != &v) {
            clear();
            this->capacity_var_ = v.capacity_var_;
            this->arr_ = v.arr_;
            this->size_ = v.size_;
            v.size_ = 0;
            v.capacity_var_ = 0;
            v.arr_ = nullptr;
        }
        return *this;
    }

    // ***************  Vector iterators  ******************** //

    template<class value_type>
    typename vector<value_type>::iterator vector<value_type>::begin() const {
        if (this->empty())
            throw std::invalid_argument("Vector is empty!");
        iterator iter_(*this, 0);
        return iter_;
    }

    template<class value_type>
    typename vector<value_type>::iterator vector<value_type>::end() const {
        if (this->empty())
            throw std::invalid_argument("Vector is empty!");
        size_type ind = this->size_ > 0 ? this->size_ : 0;
        iterator iter_(*this, ind);
        return iter_;
    }

    // ***************  Vector Capacity  ******************** //

    template<class value_type>
    void vector<value_type>::reserve(size_type size) {
        vector new_vec(size);
        new_vec.Copy_Array(this->arr_, this->size_);
        *this = std::move(new_vec);
    }

    template<class value_type>
    void vector<value_type>::shrink_to_fit() {
        if (this->size_ > 0) {
            vector new_vec(this->size_);
            new_vec.Copy_Array(this->arr_, this->size_);
            *this = std::move(new_vec);
        }
    }

    // ***************  Vector Modifiers  ******************** //

    template<class value_type>
    void vector<value_type>::clear() {
        if (this->arr_ != nullptr) {
            delete[] this->arr_;
        }
        this->arr_ = nullptr;
        this->size_ = capacity_var_ = 0;
    }

    template<class value_type>
    typename vector<value_type>::iterator
    vector<value_type>::insert(iterator &pos, const_reference value) {
        if (pos.iter_arr_ != this->arr_)
            throw std::invalid_argument("Wrong data");
        size_type pos_ind = pos.cur_pos_;
        if (pos_ind > this->size_)
            throw std::out_of_range("Bad position of Iterator!");
        value_type *tmp_arr = new value_type[this->size_ + 1]();  // [this->size_];
        for (size_type i = 0; i < this->size_; ++i) {
            tmp_arr[i] = this->arr_[i];
        }
        size_type old_size = this->size_;
        if (this->size_ >= this->capacity_var_) {
            vector reallocated(this->size_ + 5);
            *this = std::move(reallocated);
        }
        this->size_ = 0;
        for (size_type j = 0; j < old_size || j <= pos_ind; ++j) {
            if (j == pos_ind)
                this->arr_[this->size_++] = value;
            if (j < old_size)
                this->arr_[this->size_++] = tmp_arr[j];
        }
        delete [] tmp_arr;
        return pos;
    }

    template<class value_type>
    void vector<value_type>::erase(iterator &pos) {
        if (this->arr_ != pos.iter_arr_)
            throw std::invalid_argument("Iterator is pointing to different data");
        size_type ind = pos.cur_pos_;
        if (ind > this->size_ - 1 || this->size_ == 0)
            throw std::out_of_range("Out of range!");
        size_type tmp = this->size_;
        Copy_Array(this->arr_, this->size_, ind);
        this->size_ = tmp - 1;
        this->arr_[this->size_] = 0;
    }

    template<class value_type>
    void vector<value_type>::push_back(const_reference value) {
        if (this->size_ < capacity_var_) {
            this->arr_[this->size_++] = value;
        } else {
            vector new_vec(this->size_ + 5);
            new_vec.Copy_Array(this->arr_, this->size_);
            new_vec.arr_[new_vec.size_++] = value;
            *this = std::move(new_vec);
        }
    }

    template<class value_type>
    void vector<value_type>::pop_back() {
        if (!this->empty()) {
            this->arr_[--this->size_] = 0;
        }
    }

    template<class value_type>
    void vector<value_type>::swap(vector &other) {
        if (this->arr_ != other.arr_) {
            vector tmp(std::move(*this));
            *this = std::move(other);
            other = std::move(tmp);
        }
    }

    template<class value_type>
    template<typename... Args>
    typename vector<value_type>::iterator
    vector<value_type>::emplace(const const_iterator pos, Args &&... args) {
        iterator iter(pos);
        this->insert(iter, value_type(std::forward<Args>(args)...));
        return pos;
    }

    template<class value_type>
    template<typename... Args>
    void vector<value_type>::emplace_back(Args &&... args) {
        this->push_back(value_type(std::forward<Args>(args)...));
    }

    // ***************  Operators  ******************** //

    template<class value_type>
    typename vector<value_type>::const_iterator &
    vector<value_type>::const_iterator::operator==(const const_iterator &other) const {
        return (this->arr_ == other.arr_ && this->cur_pos_ == other.cur_pos_);
    }

    template<class value_type>
    typename vector<value_type>::const_iterator &vector<value_type>::const_iterator::operator++() {
        this->cur_pos_ += 1;
        return *this;
    }

    template<class value_type>
    typename vector<value_type>::const_iterator &vector<value_type>::const_iterator::operator--() {
        this->cur_pos_ -= 1;
        return *this;
    }

    template<class value_type>
    typename vector<value_type>::const_iterator vector<value_type>::const_iterator::operator++(int) {
        const_iterator tmp(*this);
        this->cur_pos_ += 1;
        return tmp;
    }

    template<class value_type>
    typename vector<value_type>::const_iterator vector<value_type>::const_iterator::operator--(int) {
        const_iterator tmp(*this);
        this->cur_pos_ -= 1;
        return tmp;
    }

    template<class value_type>
    value_type vector<value_type>::const_iterator::operator*() const {
        if (this->iter_arr_ == nullptr)
            throw std::invalid_argument("Iterator is pointing to null!");
        return (this->cur_pos_ > this->max_elem_) ? 0 : this->iter_arr_[this->cur_pos_];
    }

    template<class value_type>
    typename vector<value_type>::reference vector<value_type>::iterator::operator*() const {
        if (this->iter_arr_ == nullptr || this->cur_pos_ > this->max_elem_)
            throw std::invalid_argument("Bad parameters!");
        return this->iter_arr_[this->cur_pos_];
    }

    // ***************  Other functions  ******************** //

    template<class value_type>
    void vector<value_type>::Allocate_Memory() {
        if (!(this->arr_ = new value_type[this->capacity_var_ + 1]()))
            throw std::invalid_argument("Bad alloc");
    }

    template<class value_type>
    void vector<value_type>::Copy_Array(const value_type *arr, size_type end, int ignore) {
        size_type ind = 0;
        for (size_type i = 0; i < end && i < this->capacity_var_; i++) {
            if (ignore < 0 || (int) i != ignore) {
                this->arr_[ind++] = arr[i];
            }
        }
        this->size_ = ind;
    }

    template<class value_type>
    void vector<value_type>::Zero_All_Data() {
        this->arr_ = nullptr;
        this->size_ = this->capacity_var_ = 0;
    }
}  // namespace s21
