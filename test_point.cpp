#include "doctest.h"
#include "point.h"

TEST_CASE("Testing the generation of a point") {
	P bob = P(1,2,3);
	CHECK(bob.x == 1);
	CHECK(bob.y == 2);
	CHECK(bob.q == 3);
}

