#define BOOST_TEST_MODULE SListTest
#include "../dst/slist.hpp"
#include "../utils/utils.hpp"
#include <boost/test/included/unit_test.hpp>
#include <chrono>


BOOST_AUTO_TEST_CASE(test_pushBack_removeBack_get) {
    const int LIST_LEN = 10;
    SList<int> slist;

    int randomValues[LIST_LEN];
    for (int i = 0; i < LIST_LEN; i++) {
        randomValues[i] = generateRandomNumber(0, 10000);
        slist.pushBack(randomValues[i]);
    }
    BOOST_CHECK_EQUAL(slist.size(), LIST_LEN);
    BOOST_CHECK_EQUAL(slist.getHead()->value, randomValues[0]);

    for (int i = 0; i < LIST_LEN; i++) {
        BOOST_CHECK_EQUAL(slist.get(i), randomValues[i]);
    }

    slist.removeBack();
    BOOST_CHECK_EQUAL(slist.size(), LIST_LEN-1);
}

BOOST_AUTO_TEST_CASE(test_pushForward_removeForward) {
    SList<int> slist;

    int secondVal = generateRandomNumber(0, 10000);
    slist.pushForward(secondVal);
    int firstVal = generateRandomNumber(0, 10000);
    slist.pushForward(firstVal);

    BOOST_CHECK_EQUAL(slist.size(), 2);
    BOOST_CHECK_EQUAL(slist.getHead()->value, firstVal);

    slist.removeForward();
    BOOST_CHECK_EQUAL(slist.size(), 1);
    BOOST_CHECK_EQUAL(slist.getHead()->value, secondVal);
}

BOOST_AUTO_TEST_CASE(test_removeValue) {
    SList<int> slist;

    for (int i = 0; i < 5; i++) {
        slist.pushBack(1);
    }
    slist.pushBack(3);
    for (int i = 0; i < 5; i++) {
        slist.pushBack(2);
    }
    BOOST_CHECK_EQUAL(slist.size(), 11);

    slist.removeValue(3);
    BOOST_CHECK_EQUAL(slist.size(), 10);

    slist.removeValue(1);
    BOOST_CHECK_EQUAL(slist.size(), 5);
    for (int i = 0; i < 5; i++) {
        BOOST_CHECK_NE(slist.get(i), 1);
    }

    slist.removeValue(2);
    BOOST_CHECK_EQUAL(slist.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_emptyList) {
    SList<int> slist;
    BOOST_CHECK_THROW(slist.removeBack(), runtime_error);
    BOOST_CHECK_THROW(slist.removeForward(), runtime_error);
    BOOST_CHECK_THROW(slist.removeValue(5), runtime_error);
    BOOST_CHECK_THROW(slist.get(0), runtime_error);
    BOOST_CHECK_THROW(slist.get(-1), runtime_error);
}

BOOST_AUTO_TEST_CASE(test_removeForward_removeBack_oneValue) {
    SList<int> slist;

    slist.pushBack(5);
    slist.removeForward();
    BOOST_CHECK_EQUAL(slist.size(), 0);

    slist.pushBack(10);
    slist.removeBack();
    BOOST_CHECK_EQUAL(slist.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_findByValue) {
    SList<int> slist;

    SNode<int>* findNode;
    int findNum = 10002;
    for (int i = 0; i < 5; i++) {
        if (i == 2) {
            slist.pushBack(findNum);
            auto head = slist.getHead();
            while (head->next != nullptr) {
                head = head->next;
            }
            findNode = head;
        } else {
            slist.pushBack(generateRandomNumber(0, 10000));
        }
    }
    BOOST_CHECK_EQUAL(slist.findByValue(findNum), findNode);

    // non-existing value test
    BOOST_CHECK_EQUAL(slist.findByValue(10001), nullptr);
}

BOOST_AUTO_TEST_CASE(benchmark_pushBack) {
    SList<int> slist;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++) {
        slist.pushBack(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Execution 100000 insert time: " << duration.count() << " microseconds" << endl;

    BOOST_CHECK(true);
}
