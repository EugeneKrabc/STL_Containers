namespace s21 {
template <class T>
void queue<T>::pop() {
    this->AbstractList<T>::pop_front();
}
}  // namespace s21
