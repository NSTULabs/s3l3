#define BOOST_TEST_MODULE DlistTest
#include "../dst/dlist.hpp"
#include "../utils/utils.hpp"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test_pushBack_removeBack_get) {
    const int LIST_LEN = 10;
    DList<int> dlist;

    int randomValues[LIST_LEN];
    for (int i = 0; i < LIST_LEN; i++) {
        randomValues[i] = generateRandomNumber(0, 10000);
        dlist.pushBack(randomValues[i]);
    }
    BOOST_CHECK_EQUAL(dlist.size(), LIST_LEN);
    BOOST_CHECK_EQUAL(dlist.getHead()->value, randomValues[0]);
    BOOST_CHECK_EQUAL(dlist.getTail()->value, randomValues[LIST_LEN - 1]);

    for (int i = 0; i < LIST_LEN; i++) {
        BOOST_CHECK_EQUAL(dlist.get(i), randomValues[i]);
    }

    dlist.removeBack();
    BOOST_CHECK_EQUAL(dlist.size(), LIST_LEN-1);
    BOOST_CHECK_EQUAL(dlist.getTail()->value, randomValues[LIST_LEN - 2]);
}

BOOST_AUTO_TEST_CASE(test_pushForward_removeForward) {
    DList<int> dlist;

    int secondVal = generateRandomNumber(0, 10000);
    dlist.pushForward(secondVal);
    int firstVal = generateRandomNumber(0, 10000);
    dlist.pushForward(firstVal);

    BOOST_CHECK_EQUAL(dlist.size(), 2);
    BOOST_CHECK_EQUAL(dlist.getHead()->value, firstVal);
    BOOST_CHECK_EQUAL(dlist.getTail()->value, secondVal);

    dlist.removeForward();
    BOOST_CHECK_EQUAL(dlist.size(), 1);
    BOOST_CHECK_EQUAL(dlist.getHead()->value, secondVal);
}

BOOST_AUTO_TEST_CASE(test_removeValue) {
    DList<int> dlist;

    for (int i = 0; i < 5; i++) {
        dlist.pushBack(1);
    }
    dlist.pushBack(3);
    for (int i = 0; i < 5; i++) {
        dlist.pushBack(2);
    }
    BOOST_CHECK_EQUAL(dlist.size(), 11);

    dlist.removeValue(3);
    BOOST_CHECK_EQUAL(dlist.size(), 10);

    dlist.removeValue(1);
    BOOST_CHECK_EQUAL(dlist.size(), 5);
    for (int i = 0; i < 5; i++) {
        BOOST_CHECK_NE(dlist.get(i), 1);
    }

    dlist.removeValue(2);
    BOOST_CHECK_EQUAL(dlist.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_emptyList) {
    DList<int> dlist;
    BOOST_CHECK_THROW(dlist.removeBack(), runtime_error);
    BOOST_CHECK_THROW(dlist.removeForward(), runtime_error);
    BOOST_CHECK_THROW(dlist.removeValue(5), runtime_error);
    BOOST_CHECK_THROW(dlist.get(0), invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_removeForward_removeBack_oneValue) {
    DList<int> dlist;

    dlist.pushBack(5);
    dlist.removeForward();
    BOOST_CHECK_EQUAL(dlist.size(), 0);

    dlist.pushBack(10);
    dlist.removeBack();
    BOOST_CHECK_EQUAL(dlist.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_findByValue) {
    DList<int> dlist;

    DNode<int>* findNode;
    int findNum = 10002;
    for (int i = 0; i < 5; i++) {
        if (i == 2) {
            dlist.pushBack(findNum);
            findNode = dlist.getTail();
        } else {
            dlist.pushBack(generateRandomNumber(0, 10000));
        }
    }
    BOOST_CHECK_EQUAL(dlist.findByValue(findNum), findNode);

    // non-existing value test
    BOOST_CHECK_EQUAL(dlist.findByValue(10001), nullptr);
}