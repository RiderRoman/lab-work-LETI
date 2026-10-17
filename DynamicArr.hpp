#pragma once

template<typename T>
DynamicArr<T>::DynamicArr() {
	size = 0;
	data = nullptr;
}

template<typename T>
DynamicArr<T>::DynamicArr(size_t start_size) {
	size = start_size;
	if (start_size > 0) {
		data = new T[start_size]();
	}
}

template<typename T>
DynamicArr<T>::DynamicArr(const DynamicArr& other) {
	size = other.size;
	data = nullptr;
	if (size > 0) {
		data = new T[size];
		for (size_t i = 0; i < size; i++) {
			data[i] = other.data[i];
		}
	}
}

template<typename T>
DynamicArr<T>::~DynamicArr() {
	delete[] data;
}

template<typename T>
T& DynamicArr<T>::operator[](size_t index) { 
	return data[index]; 
}

template<typename T>
const T& DynamicArr<T>::operator[](size_t index) const { 
	return data[index];
}

template<typename T>
DynamicArr<T>& DynamicArr<T>::operator=(DynamicArr arr) {
	std::swap(size, arr.size);
	std::swap(data, arr.data);
	return *this;
}

template<typename T>
void DynamicArr<T>::push_back(T value) {
	size++;
	T* new_arr = new T[size];

	for (int i = 0; i < (size - 1); i++) {
		new_arr[i] = data[i];
	}

	new_arr[size - 1] = value;
	delete[] data;
	data = new_arr;
}

template<typename T>
void DynamicArr<T>::push_front(T value) {
	size++;
	T* new_arr = new T[size];
	new_arr[0] = value;

	for (int i = 0; i < (size - 1); i++) {
		new_arr[i + 1] = data[i];
	}

	delete[] data;
	data = new_arr;
}

template<typename T>
void DynamicArr<T>::insert(size_t index, T value) {
	if (index > size) return;
	size++;
	T* new_arr = new T[size];

	for (int i = 0; i < index; i++) {
		new_arr[i] = data[i];
	}
	new_arr[index] = value;

	for (int i = index; i < size - 1; i++) {
		new_arr[i + 1] = data[i];
	}

	delete[] data;
	data = new_arr;
}

template<typename T>
void DynamicArr<T>::pop_back() {
	if (size == 0) return;
	size--;
	data[size] = T();
}

template<typename T>
void DynamicArr<T>::pop_front() {
	if (size == 0) return;
	delete_by_index(0);
}

template<typename T>
void DynamicArr<T>::delete_by_index(int index) {
	if (size == 0) return 0;
	size--;
	T* new_arr = new T[size];

	for (int i = 0; i < index; i++) {
		new_arr[i] = data[i];
	}

	for (int i = index; i < size; i++) {
		new_arr[i] = data[i + 1];
	}

	delete[] data;
	data = new_arr;
}

template<typename T>
void DynamicArr<T>::print_array() {
	for (int i = 0; i < size; i++) {
		if (i == size - 1) {
			std::cout << data[i];
			break;
		}
		std::cout << data[i] << ", ";
	}
}