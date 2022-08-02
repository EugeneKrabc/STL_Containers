namespace s21 {
template <class T>
typename stack<T>::const_reference stack<T>::top() {
    return this->AbstractList<T>::back();
}
template <class T>
void stack<T>::pop() {
    this->AbstractList<T>::pop_back();
}
}  // namespace s21
