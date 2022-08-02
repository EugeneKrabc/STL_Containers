namespace s21 {

    // ***************  Element Access  ******************** //

    template<class T>
    typename BaseClassVecArr<T>::reference BaseClassVecArr<T>::at(size_type at) const {
        if (at >= size())
            throw std::out_of_range("Out of range!");
        return *(arr_ + at);
    }

    template<class T>
    typename BaseClassVecArr<T>::reference BaseClassVecArr<T>::operator[](size_type pos) const {
        return at(pos);
    }

    template<class T>
    typename BaseClassVecArr<T>::const_reference BaseClassVecArr<T>::front() const {
        if (empty())
            throw std::invalid_argument("Object is empty!");
        return at(0);
    }

    template<class T>
    typename BaseClassVecArr<T>::const_reference BaseClassVecArr<T>::back() const {
        if (empty())
            throw std::invalid_argument("Object is empty!");
        return at(size_ - 1);
    }

    // ***************  Capacity  ******************** //

    template<class T>
    bool BaseClassVecArr<T>::empty() const {
        return (size_ == 0);
    }

    template<class T>
    typename BaseClassVecArr<T>::size_type BaseClassVecArr<T>::size() const {
        return size_;
    }

    template<class T>
    typename BaseClassVecArr<T>::size_type BaseClassVecArr<T>::max_size() const {
        return (MAX_ALLOCATED / sizeof(T));
    }
}  // namespace s21
