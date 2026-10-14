#pragma once
#include "DynamicArr.h"

template<typename T>
class Stack {
	DynamicArr<T> data;
public:
	void push_back(T value) { data.push_back(value); }
	void pop_back() { data.pop_back(); }
	size_t get_size() const { return data.get_size(); }
	T top() { return data[data.get_size() - 1]; }
	T front() { return data[0]; }
	void print_stack() {
		data.print_array();
	}
};