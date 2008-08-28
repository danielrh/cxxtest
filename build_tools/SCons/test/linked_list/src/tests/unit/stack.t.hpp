#ifndef STACKTEST_HPP_
#define STACKTEST_HPP_

#include <cxxtest/TestSuite.h>
#include <lib/stack.hpp>

class StackTest : public CxxTest::TestSuite
{
public:
	void testStackImplementation()
	{
		Stack stack;

		TS_ASSERT( stack.is_empty() );

		stack.push((void*)13);
		stack.push((void*)12);
		stack.push((void*)7);
		stack.push((void*)5);
		stack.push((void*)3);
		stack.push((void*)2);

		TS_ASSERT( !stack.is_empty() );
		
		TS_ASSERT( (int)stack.pop() == 2);
		TS_ASSERT( (int)stack.pop() == 3);
		TS_ASSERT( (int)stack.pop() == 5);
		TS_ASSERT( (int)stack.pop() == 7);
		TS_ASSERT( (int)stack.pop() == 12);
		TS_ASSERT( (int)stack.pop() == 13);
		
		TS_ASSERT( stack.is_empty() );
	}
};

#endif
