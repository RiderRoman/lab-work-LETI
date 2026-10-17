#pragma once
#include "DynamicArr.h"
#include <stdexcept>

template<typename T>
class Stack {
	DynamicArr<T> data;
public:
	size_t get_size() const { return data.get_size(); }

	void push_back(T value);
	void pop_back();
	const T& top() const;
	const T& front() const;
	void print_stack();
};

#include "Stack.hpp"