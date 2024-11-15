#define BOOST_TEST_MODULE StackTest
#include "../dst/stack.hpp"
#include <boost/test/included/unit_test.hpp>
#include <chrono>


BOOST_AUTO_TEST_CASE(test_stack) {
    Stack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    BOOST_CHECK_EQUAL(stack.size(), 3);
    BOOST_CHECK_EQUAL(stack.pop(), 3);
    BOOST_CHECK_EQUAL(stack.pop(), 2);
    BOOST_CHECK_EQUAL(stack.pop(), 1);

    BOOST_CHECK_THROW(stack.pop(), runtime_error);
}

BOOST_AUTO_TEST_CASE(benchmark_push) {
    Stack<int> stack;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++) {
        stack.push(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Execution 100000 insert time: " << duration.count() << " microseconds" << endl;

    BOOST_CHECK(true);
}
