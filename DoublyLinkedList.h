#pragma once

struct Node {
	int data;
	Node* next;
	Node* prev;
	Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
	Node* head;
	Node* tail;
public:
	DoublyLinkedList() : head(nullptr), tail(nullptr) {}
	~DoublyLinkedList() = default;

	Node* push_back(int value) {
		Node* new_node = new Node(value);

		if (!head) {
			head = tail = new_node;
		}
		else {
			tail->next = new_node;
			new_node->prev = tail;
			tail = new_node;
		}
		return new_node;
	}

	Node* push_front(int value) {
		Node* new_node = new Node(value);

		if (!head) {
			head = tail = new_node;
		}
		else {
			head->prev = new_node;
			new_node->next = head;
			head = new_node;
		}
		return new_node;
	}

	Node* insert(int index, int value) {

	}


};