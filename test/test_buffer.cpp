#include "test.h"
#include "ring_buffer.h"

TEST_CASE("test_case_name")
{
    Ring_buffer<int, 3> b;

    b.push(1);
    b.push(1);
    b.push(3);
    b.push(4);

    REQUIRE(b.pop() == 1);
    REQUIRE(b.pop() == 3);
}