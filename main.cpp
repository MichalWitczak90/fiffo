#include "ring_buffer.h"
#include "queue.h"
#include "measurements.h"
#include "stdio.h"
#include "stdlib.h"
#include <deque>


// #define boost // w przypadku posiadania biblioteki boost mozna odkomentowac ta linijke

#ifdef boost

#include <boost/circular_buffer.hpp>

#endif

int main(int argc, char *argv[])
{
    system("clear");

    auto iterations = atoi(argv[1]);

    printf("Starting measurements over [%d] iterations\n", iterations);

    //---------------------------------------------| ring_buffer |---------------------------------------------//

    printf("Running custom Ring_buffer test ...\t");
    fflush(stdout);

    Ring_buffer ring_buffer;

    auto ring_buffer_push = [&](){ring_buffer.push(2);};
    auto ring_buffer_pop = [&](){ring_buffer.pop();};
    auto ring_buffer_is_empty = [&](){ring_buffer.is_empty();};
    auto ring_buffer_is_full = [&](){ring_buffer.is_full();};

    auto result_ring_buffer_push = measure(ring_buffer_push, iterations);
    auto result_ring_buffer_pop = measure(ring_buffer_pop, iterations);
    auto result_ring_buffer_is_empty = measure(ring_buffer_is_empty, iterations);
    auto result_ring_buffer_is_full = measure(ring_buffer_is_full, iterations);

    printf("\e[1;32mDone !\e[0m\n");

    //---------------------------------------------| circular_buffer |---------------------------------------------//

    #ifdef boost

    printf("Running COTS circular_buffer test ...\t");
    fflush(stdout);

    boost::circular_buffer<int> circular_buffer(3);

    auto circular_buffer_push = [&](){circular_buffer.push_back(2);};
    auto circular_buffer_pop = [&](){circular_buffer.pop_front();};
    auto circular_buffer_is_empty = [&](){circular_buffer.empty();};
    auto circular_buffer_is_full = [&](){circular_buffer.full();};

    auto result_circular_buffer_push = measure(circular_buffer_push, iterations);
    auto result_circular_buffer_pop = measure(circular_buffer_pop, iterations);
    auto result_circular_buffer_is_empty = measure(circular_buffer_is_empty, iterations);
    auto result_circular_buffer_is_full = measure(circular_buffer_is_full, iterations);    

    printf("\e[1;32mDone !\e[0m\n");

    #endif

    //---------------------------------------------| Queue |---------------------------------------------//

    printf("Running custom Queue test ...\t\t");
    fflush(stdout);

    Queue queue;

    auto queue_push = [&](){queue.push(2);};
    auto queue_pop = [&](){queue.pop();};
    auto queue_is_empty = [&](){queue.is_empty();};

    auto result_queue_push = measure(queue_push, iterations);
    auto result_queue_pop = measure(queue_pop, iterations);
    auto result_queue_is_empty = measure(queue_is_empty, iterations);

    printf("\e[1;32mDone !\e[0m\n");

    //---------------------------------------------| deque |---------------------------------------------//

    printf("Running COTS deque test ...\t\t");
    fflush(stdout);

    std::deque<int> deque;

    auto deque_push = [&](){deque.push_back(2);};
    auto deque_pop = [&](){deque.pop_front();};
    auto deque_is_empty = [&](){deque.empty();};

    auto result_deque_push = measure(deque_push, iterations);
    auto result_deque_pop = measure(deque_pop, iterations);
    auto result_deque_is_empty = measure(deque_is_empty, iterations);

    printf("\e[1;32mDone !\e[0m\n");

    //---------------------------------------------| results |---------------------------------------------//

    printf("----------------------------------------------------------------\n");
    printf("|\e[1;31m%-20s\e[0m|\e[1;31m%-20s\e[0m|\e[1;31m%-20s\e[0m|\n", "Container", "Method", "Execution time [us]");
    printf("----------------------------------------------------------------\n");

    printf("|%-20s|%-20s|%-20ld|\n", "Ring_buffer", "push_back()", result_ring_buffer_push);
    printf("|%-20s|%-20s|%-20ld|\n", "Ring_buffer", "pop_front()", result_ring_buffer_pop);
    printf("|%-20s|%-20s|%-20ld|\n", "Ring_buffer", "is_empty()", result_ring_buffer_is_empty);
    printf("|%-20s|%-20s|%-20ld|\n", "Ring_buffer", "is_full()", result_ring_buffer_is_full);
    printf("----------------------------------------------------------------\n");

    #ifdef boost

    printf("|%-20s|%-20s|%-20ld|\n", "Circular_buffer", "push_back()", result_circular_buffer_push);
    printf("|%-20s|%-20s|%-20ld|\n", "Circular_buffer", "pop_front()", result_circular_buffer_pop);
    printf("|%-20s|%-20s|%-20ld|\n", "Circular_buffer", "is_empty()", result_circular_buffer_is_empty);
    printf("|%-20s|%-20s|%-20ld|\n", "Circular_buffer", "is_full()", result_circular_buffer_is_full);
    printf("----------------------------------------------------------------\n");

    #endif

    printf("|%-20s|%-20s|%-20ld|\n", "Queue", "push_back()", result_queue_push);
    printf("|%-20s|%-20s|%-20ld|\n", "Queue", "pop_front()", result_queue_pop);
    printf("|%-20s|%-20s|%-20ld|\n", "Queue", "is_empty()", result_queue_is_empty);
    printf("----------------------------------------------------------------\n");

    printf("|%-20s|%-20s|%-20ld|\n", "Deque", "push_back()", result_deque_push);
    printf("|%-20s|%-20s|%-20ld|\n", "Deque", "pop_front()", result_deque_pop);
    printf("|%-20s|%-20s|%-20ld|\n", "Deque", "is_empty()", result_deque_is_empty);
    printf("----------------------------------------------------------------\n");

    return 0;
}
