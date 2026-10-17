template<typename T>
void Stack<T>::push_back(T value) {
	data.push_back(value);
}

template<typename T>
void Stack<T>::pop_back() {
	data.pop_back();
}

template<typename T>
const T& Stack<T>::top() const {
	if (data.get_size() == 0) throw std::underflow_error("empty stack");
	return data[data.get_size() - 1];
}

template<typename T>
const T& Stack<T>::front() const {
	if (data.get_size() == 0) throw std::underflow_error("empty stack");
	return data[0];
}

template<typename T>
void Stack<T>::print_stack() {
	data.print_array();
}