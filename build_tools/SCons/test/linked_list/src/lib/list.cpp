#include "list.hpp"

class Node
{
	public:
		void* data;
		Node* next;
};

List::List()
{
	head = 0;
}

List::~List()
{
	while (head) {
		Node* tmp = head;
		head = tmp->next;
		delete tmp;
	}	
}

void List::append(void* t)
{
	Node* node = new Node();
	node->data = t;
	node->next = head;
	head = node;
}

List::Iterator List::remove(List::Iterator it)
{
	if (it != begin()) {
		List::Iterator target = it--;
		it->next = target->next;
		delete target.node;
		return ++it;
	} else {
		Node* tmp = head->next;
		delete head;
		head = tmp;
		return begin();
	}
}

List::Iterator List::find(void* t)
{
	List::Iterator it = this->begin();
	
	while ( it != end()) {
		if ( it->data == t )
			break;
		++it;
	}
	return it;
}

List::Iterator List::begin()
{
	return List::Iterator(this, head);
}

List::Iterator List::end()
{
	return List::Iterator(this, 0);
}

List::Iterator::Iterator(List* list, Node* node) : list(list)
{
	this->node = node;
}

bool List::Iterator::operator!=(List::Iterator i)
{
	return (this->node != i.node);
}

List::Iterator& List::Iterator::operator++()
{
	node = node->next;
	return *this;
}

List::Iterator List::Iterator::operator--(int)
{
	List::Iterator cur = *this;
	List::Iterator it = list->begin();
	
	if (it != *this) {
		while ( it->next != node)
			++it;
		node = it.node;
	}
	return cur;
}

Node* List::Iterator::operator->()
{
	return node;
}

void* List::Iterator::operator*()
{
	return node->data;
}
