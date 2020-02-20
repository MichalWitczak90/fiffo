#include "test.h"
#include "ring_buffer.h"
#include "queue.h"


TEST_CASE("test_case_name")
{
    Queue<int> q;

    for (int i = 0; i < 100; i++)
    {
        q.push(i);
    }

    REQUIRE(q.size_actual() == 100);

    for (int i = 0; i < 100; i++)
    {
        auto temp = q.pop();

        REQUIRE(temp == i);
    }

    REQUIRE(q.size_actual() == 0);
}