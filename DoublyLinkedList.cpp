#include "DoublyLinkedList.h"

Node::Node(int value) : data(value), next(nullptr), prev(nullptr) {}

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

Node* DoublyLinkedList::push_back(int value) {
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

Node* DoublyLinkedList::push_front(int value) {
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

Node* DoublyLinkedList::get_number(int index) {
	Node* temp = head;
	int pos = 0;

	while (pos != index) {
		if (temp == nullptr) return temp;

		temp = temp->next;
		pos++;
	}
	return temp;
}

Node* DoublyLinkedList::insert(int index, int value) {
	Node* right = get_number(index);
	if (right == nullptr)
		return push_back(value);

	Node* left = right->prev;
	if (left == nullptr)
		return push_front(value);

	Node* new_node = new Node(value);

	new_node->prev = left;
	new_node->next = right;
	left->next = new_node;
	right->prev = new_node;

	return new_node;
}