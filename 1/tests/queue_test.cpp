#define BOOST_TEST_MODULE QueueTest
#include "../dst/queue.hpp"
#include <boost/test/included/unit_test.hpp>
#include <chrono>



BOOST_AUTO_TEST_CASE(test_enqueue_dequeue_size) {
    Queue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    BOOST_CHECK_EQUAL(queue.size(), 3);

    BOOST_CHECK_EQUAL(queue.dequeue(), 1);
    BOOST_CHECK_EQUAL(queue.size(), 2);

    BOOST_CHECK_EQUAL(queue.dequeue(), 2);
    BOOST_CHECK_EQUAL(queue.size(), 1);

    BOOST_CHECK_EQUAL(queue.dequeue(), 3);
    BOOST_CHECK_EQUAL(queue.size(), 0);

    BOOST_CHECK_THROW(queue.dequeue(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(benchmark_push) {
    Queue<int> queue;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++) {
        queue.enqueue(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Execution 100000 insert time: " << duration.count() << " microseconds" << endl;

    BOOST_CHECK(true);
}
