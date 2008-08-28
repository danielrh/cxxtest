#ifndef LIST_HPP_
#define LIST_HPP_

/*
 * A simple list implementation.
 *
 */

class Node;

class List
{
	public:
		class Iterator
		{
			public:
				bool operator!=(Iterator i);
				void* operator*();
				Iterator& operator++();
				Iterator operator--(int);

			private:
				Iterator(List* l, Node* node);
				Node* operator->();
				Node* node;
				List* list;

			friend class List;
		};

	public:
		List();
		~List();
		
		void append(void* t);
		List::Iterator remove(List::Iterator it);
		List::Iterator find(void* t);
		List::Iterator begin();
		List::Iterator end();

	private:
		Node* head;
};

#endif
