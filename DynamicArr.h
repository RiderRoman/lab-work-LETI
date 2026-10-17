#pragma once
#include <iostream>

template <typename T>
class DynamicArr {
	size_t size;
	T* data = nullptr;
public:
	DynamicArr();
	explicit DynamicArr(size_t start_size);
	DynamicArr(const DynamicArr& other);
	~DynamicArr();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	DynamicArr& operator=(DynamicArr arr);

	void push_back(T value);
	void push_front(T value);
	void insert(size_t index, T value);
	void pop_back();
	void pop_front();
	void delete_by_index(int index);
	void print_array();

	size_t get_size() const { return size; }
};

#include "DynamicArr.hpp"