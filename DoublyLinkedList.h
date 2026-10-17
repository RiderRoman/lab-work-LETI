#pragma once

struct Node {
	int data;
	Node* next;
	Node* prev;
	Node(int value);
};

class DoublyLinkedList {
	Node* head;
	Node* tail;
public:
	DoublyLinkedList();
	~DoublyLinkedList() = default;

	Node* push_back(int value);
	Node* push_front(int value);
	Node* get_number(int index);
	Node* insert(int index, int value);

};