#include "priority_queue.h"

#include "core/os/memory.h"
#include "core/variant/array.h"
#include "core/variant/variant.h"

void PriorityQueue::push(Variant p_value, int p_priority)
{
	Node* n = memnew(Node(p_value, p_priority));

	if (!_head) {
		_head = n;
		num_elements++;
		return;
	}

	Node* prev_node = _head;
	while (prev_node->next && n->priority > prev_node->priority)
	{
		prev_node = prev_node->next;
	}

	n->next = prev_node->next;
	prev_node->next = n;

	num_elements++;
}

Variant PriorityQueue::pop()
{
	if (!_head)
	{
		ERR_PRINT("PriorityQueue is empty!");
		return Variant();
	}

	Node* head = _head;
	Variant value = std::move(head->value);
	_head = _head->next;

	num_elements--;

	return value;
}

Variant PriorityQueue::peek() const
{
	if (!_head)
	{
		ERR_PRINT("PriorityQueue is empty!");
		return Variant();
	}
	return _head->value;
}

Variant PriorityQueue::get(const Variant& p_value) const
{
	Node* current = _head;

	while (current)
	{
		if (current->value == p_value)
		{
			return current->value;
		}
		current = current->next;
	}
	return Variant();
}

int PriorityQueue::find_position(const Variant& p_value) const
{
	Node* current = _head;
	int position = 0;

	while (current)
	{
		if (current->value == p_value)
		{
			return position;
		}
		position++;
		current = current->next;
	}

	return -1;
}

bool PriorityQueue::is_empty() const
{
	return _head;
}

void PriorityQueue::clear()
{
	// No need to manually delete `current->value`, since its a Variant type — let Godot handle it
	_head = nullptr;
	num_elements = 0;
}

int PriorityQueue::size() const
{
	return num_elements;
}

void PriorityQueue::print_list() const
{
	Node* current = _head;
	while (current)
	{
		Object* obj = current->value.operator Object * ();
		if (obj)
		{
			print_line("Name: " + String(obj->get("name")) + ", Priority: " + String::num(current->priority));
		}
		else
		{
			print_line("Invalid object in Variant!");
		}
		current = current->next;
	}
}

void PriorityQueue::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("push", "value", "priority"), &PriorityQueue::push);
	ClassDB::bind_method(D_METHOD("pop"), &PriorityQueue::pop);
	ClassDB::bind_method(D_METHOD("peek"), &PriorityQueue::peek);
	ClassDB::bind_method(D_METHOD("find_position", "value"), &PriorityQueue::find_position);
	ClassDB::bind_method(D_METHOD("is_empty"), &PriorityQueue::is_empty);
	ClassDB::bind_method(D_METHOD("clear"), &PriorityQueue::clear);
	ClassDB::bind_method(D_METHOD("size"), &PriorityQueue::size);
	ClassDB::bind_method(D_METHOD("print_list"), &PriorityQueue::print_list);
}

PriorityQueue::PriorityQueue()
{
	_head = nullptr;
	num_elements = 0;
}

PriorityQueue::PriorityQueue(std::initializer_list<QueuePair> p_init)
{
	for (auto& el : p_init)
	{
		push(el.value, el.priority);
	}
}

PriorityQueue::~PriorityQueue()
{
	clear();
}
