#define BOOST_TEST_MODULE StackTest
#include "../dst/stack.hpp"
#include <boost/test/included/unit_test.hpp>


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