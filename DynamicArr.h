#pragma once
using namespace std;

template <typename T>
class DynamicArr {
	size_t size;
	T* data = nullptr;
public:
	DynamicArr() {
		size = 0;
		data = nullptr;
	}

	DynamicArr(size_t start_size) {
		size = start_size;
		if (start_size > 0) {
			data = new T[start_size]();
		}
	}

	~DynamicArr() { delete[] data; }

	T& operator[](size_t index) {
		return data[index];
	}

	const T& operator[](size_t index) const {
		return data[index];
	}

	void push_back(T value) {
		size++;
		T* new_arr = new T[size];

		for (int i = 0; i < (size - 1); i++) {
			new_arr[i] = data[i];
		}

		new_arr[size - 1] = value;
		delete[] data;
		data = new_arr;
	}

	void push_front(T value) {
		size++;
		T* new_arr = new T[size];
		new_arr[0] = value;

		for (int i = 0; i < (size - 1); i++) {
			new_arr[i + 1] = data[i];
		}

		delete[] data;
		data = new_arr;
	}

	void insert(int index, T value) {
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

	void pop_back() {
		if (size == 0) return;
		size--;
		T* new_arr = new T[size];

		for (int i = 0; i < size; i++) {
			new_arr[i] = data[i];
		}

		delete[] data;
		data = new_arr;
	}

	void pop_front() {
		if (size == 0) return;
		size--;
		T* new_arr = new T[size];

		for (int i = 1; i < size + 1; i++) {
			new_arr[i - 1] = data[i];
		}

		delete[] data;
		data = new_arr;
	}

	void delete_by_index(int index) {
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

	void print_array() {
		for (int i = 0; i < size; i++) {
			cout << data[i] << "\n";
		}
	}

	size_t get_size() const { return size; }
};