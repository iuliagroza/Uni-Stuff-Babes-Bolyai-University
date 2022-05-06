#include "DynamicVector.h"
#include <crtdbg.h>
#include <string>
#include <cassert>
#include "repo.h"
#include "service.h"

int main()
{
	{
		/*
		DynamicVector v1{};

		DynamicVector v2{ v1 };

		DynamicVector v3{};
		v3 = v1; */

		DynamicVector v{};
		song s{ "abc", "def", 3.23, "url" };

		v.add(s);

		assert(v.getSize() == 1);
		assert(s.getTitle() == "def");

		assert(v[0].getTitle() == "def");

		repo r;
		service srv{ r };

		srv.add("abc", "def", 3.41, "link");
		assert(srv.getSize() == 1);

		assert(r.getSize() == 1);
	}

	_CrtDumpMemoryLeaks();

	return 0;
}