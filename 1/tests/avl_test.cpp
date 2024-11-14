#define BOOST_TEST_MODULE AVLTest
#include "../dst/avl.hpp"
#include "../utils/utils.hpp"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test_right_rotate) {
    AVLTree avl;

    avl.insert(1);
    avl.insert(2);
    avl.insert(3);

    auto head = avl.getHead();
    head = avl.balanceNode(head);
    BOOST_CHECK_EQUAL(head->value, 2);
    BOOST_CHECK_EQUAL(head->left->value, 1);
    BOOST_CHECK_EQUAL(head->right->value, 3);
}

BOOST_AUTO_TEST_CASE(test_right_left_rotate) {
    AVLTree avl;

    avl.insert(2);
    avl.insert(4);
    avl.insert(3);

    auto head = avl.getHead();
    head = avl.balanceNode(head);
    BOOST_CHECK_EQUAL(head->value, 3);
    BOOST_CHECK_EQUAL(head->left->value, 2);
    BOOST_CHECK_EQUAL(head->right->value, 4);
}

BOOST_AUTO_TEST_CASE(test_left_rotate) {
    AVLTree avl;

    avl.insert(3);
    avl.insert(2);
    avl.insert(1);

    auto head = avl.getHead();
    head = avl.balanceNode(head);
    BOOST_CHECK_EQUAL(head->value, 2);
    BOOST_CHECK_EQUAL(head->left->value, 1);
    BOOST_CHECK_EQUAL(head->right->value, 3);
}

BOOST_AUTO_TEST_CASE(test_left_right_rotate) {
    AVLTree avl;

    avl.insert(4);
    avl.insert(2);
    avl.insert(3);

    auto head = avl.getHead();
    head = avl.balanceNode(head);
    BOOST_CHECK_EQUAL(head->value, 3);
    BOOST_CHECK_EQUAL(head->left->value, 2);
    BOOST_CHECK_EQUAL(head->right->value, 4);
}

BOOST_AUTO_TEST_CASE(test_insert_duplicate) {
    AVLTree avl;

    avl.insert(4);
    avl.insert(4);

    auto head = avl.getHead();
    BOOST_CHECK_EQUAL(head->value, 4);
    BOOST_CHECK_EQUAL(head->left, nullptr);
    BOOST_CHECK_EQUAL(head->right, nullptr);
}

BOOST_AUTO_TEST_CASE(test_remove) {
    AVLTree avl;

    for (int i = 0; i < 5; i++) {
        avl.insert(i);
    }

    avl.remove(1);
    avl.remove(4);
    avl.remove(5);

    auto head = avl.getHead();
    BOOST_CHECK_EQUAL(head->value, 2);
    BOOST_CHECK_EQUAL(head->left->value, 0);
    BOOST_CHECK_EQUAL(head->right->value, 3);

    avl.remove(2);
    head = avl.getHead();
    BOOST_CHECK_EQUAL(head->value, 3);
    BOOST_CHECK_EQUAL(head->left->value, 0);
}