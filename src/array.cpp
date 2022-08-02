namespace s21 {

    // ***************  Capacity  ******************** //

    template<typename T, size_t size>
    array<T, size>::array() {
        Generic_Initialization();
    }

    template<typename T, size_t size>
    array<T, size>::array(std::initializer_list <value_type> const &items) {
        Generic_Initialization();
        size_type i = 0;
        for (auto element : items) {
            if (i == this->size_)
                break;
            this->arr_static_[i++] = element;
        }
    }

    template<typename T, size_t size>
    array<T, size>::array(const array &a) {
        Generic_Initialization();
        Copy_Array(a.arr_static_);
    }

    template<typename T, size_t size>
    array<T, size>::array(array &&a) {
        Generic_Initialization();
        if (this != &a) {
            *this = std::move(a);
        }
    }

    template<typename T, size_t size>
    typename array<T, size>::array &array<T, size>::operator=(array &&a) {
        if (this != &a) {
            Copy_Array(a.arr_);
            a.fill(T(0));
        }
        return *this;
    }

    // ***************  Array Modifiers  ******************** //

    template<typename T, size_t size>
    void array<T, size>::swap(array &other) {
        if (this->arr_ != other.arr_) {
            array tmp(std::move(other));
            other = std::move(*this);
            *this = std::move(tmp);
        }
    }

    template<typename T, size_t size>
    void array<T, size>::fill(const_reference value) {
        for (size_type i = 0; i < this->size_; i++) {
            this->arr_static_[i] = value;
        }
    }

    // ***************  Other Functions  ******************** //

    template<typename T, size_t size>
    void array<T, size>::Generic_Initialization() {
        Check_Size();
        this->size_ = size;
        fill(T(0));
        this->arr_ = arr_static_;
    }

    template<typename T, size_t size>
    void array<T, size>::Copy_Array(const T *arr) {
        for (size_type i = 0; i < this->size_; i++) {
            this->arr_static_[i] = arr[i];
        }
    }

    template<typename T, size_t size>
    void array<T, size>::Check_Size() {
        if (size < 1)
            throw std::invalid_argument("Bad size");
    }
}  // namespace s21
