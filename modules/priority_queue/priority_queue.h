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

		Node (Variant avalue, int apriority) : value(avalue), priority(apriority), next(nullptr) {}
	};

	Node* _head;
	int num_elements;


protected:
	static void _bind_methods();

public:
	void push(Variant p_value, int p_priority = 0); // Add a new item to the queue
	//void push(Variant&& value, int priority);
	Variant pop(); // Remove and return the highest-priority item
	Variant peek() const; // View the highest-priority item without removing it
	bool is_empty() const; // Check if the queue is empty
	void clear(); // Remove all items from the queue
	int size() const; // Get the current size of the queue

	PriorityQueue();
	PriorityQueue(std::initializer_list<QueuePair> p_init);
	~PriorityQueue();
};

// Todo add it to variant.h types
