#include "stack.hpp"

void Stack::push(void *t)
{
	list.append(t);
}

void* Stack::pop() {
	List::Iterator it = list.begin();
	void * data = *it;
	list.remove(it);
	return data;
}

bool Stack::is_empty()
{
	return !(list.begin() != list.end());
}
