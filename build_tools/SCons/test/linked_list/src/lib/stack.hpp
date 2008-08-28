#ifndef STACK_HPP_
#define STACK_HPP_

#include "list.hpp"

class Stack
{
	public:
		void push(void * t);
		void* pop();
		bool is_empty();

	private:
		List list;
};

#endif
