#pragma once

#include "core/object/ref_counted.h"

#include <initializer_list>

class Array;
class Variant;

struct QueuePair
{
	Variant value;
	int priority;
};

class PriorityQueue : public RefCounted
{
	GDCLASS(PriorityQueue, RefCounted);
	
	struct Node
	{
		Variant value;
		int priority;
		Node* next;

		Node (Variant p_value, int p_priority = 0) : value(p_value), priority(p_priority), next(nullptr) {}
		Node (Variant&& p_value, int p_priority = 0) : value(std::move(p_value)), priority(p_priority), next(nullptr) {}
	};

	Node* _head;
	int num_elements;


protected:
	static void _bind_methods();

public:
	void push(Variant p_value, int p_priority); // Add a new node to the queue
	Variant pop(); // Remove and return the highest-priority node
	Variant peek() const; // View the highest-priority node without removing it
	Variant get_item(const Variant& p_value) const; // Gets an node from the Queue
	Variant remove(const Variant& p_value); // Gets an node from the Queue
	int find_position(const Variant& p_value) const; // Finds the position of an node, if it is found in the Queue
	bool is_empty() const; // Check if the queue is empty
	void clear(); // Remove all nodes from the queue
	int size() const; // Get the current size of the queue

	void print_list() const;

	PriorityQueue();
	PriorityQueue(std::initializer_list<QueuePair> p_init);
	~PriorityQueue();

private:
	void delete_node(Node* node);
};
