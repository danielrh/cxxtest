#ifndef LISTTEST_HPP_
#define LISTTEST_HPP_

#include <cxxtest/TestSuite.h>
#include <lib/list.hpp>

class ListTest : public CxxTest::TestSuite
{
public:
	void testListImplementation()
	{
		List l;

		l.append((void*)13);
		l.append((void*)12);
		l.append((void*)7);
		l.append((void*)5);
		l.append((void*)3);
		l.append((void*)2);

		List::Iterator it = l.find((void*)7);

		TS_ASSERT( it != l.end() );
		TS_ASSERT( ((int)*it) == 7);
		++it;
		TS_ASSERT( ((int)*it) == 12);
		it = l.remove(it);
		TS_ASSERT( ((int)*it) == 13);
	}
};

#endif
