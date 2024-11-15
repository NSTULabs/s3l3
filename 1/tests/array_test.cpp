#define BOOST_TEST_MODULE DSTTest
#include "../dst/array.hpp"
#include "../utils/utils.hpp"
#include <chrono>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_add_get) {
    const int ARR_LEN = 20;

    Array<int> arr;
    
    // check add
    for (int i = 0; i < ARR_LEN; i++) {
        arr.pushBack(i);
    }
    BOOST_CHECK_EQUAL(arr.size(), ARR_LEN);
    arr.insert(3, 15);
    BOOST_CHECK_EQUAL(arr.size(), ARR_LEN + 1);
    BOOST_CHECK_EQUAL(arr.capacity(), 64);

    int wait[] = {0, 1, 2, 15, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    // check get
    for (int i = 0; i < ARR_LEN + 1; i++) {
        BOOST_CHECK_EQUAL(arr.get(i), wait[i]);
        BOOST_CHECK_EQUAL(arr[i], wait[i]);
    }
}

BOOST_AUTO_TEST_CASE(test_invalid_index) {
    Array<int> arr;
    arr.pushBack(1);
    BOOST_CHECK_THROW(arr.get(1), invalid_argument);
    BOOST_CHECK_THROW(arr[1], invalid_argument);
    BOOST_CHECK_THROW(arr.insert(2, 5), invalid_argument);
    BOOST_CHECK_THROW(arr.remove(54), invalid_argument);
    BOOST_CHECK_THROW(arr.set(54, 5), invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_remove) {
    const int ARR_LEN = 10;
    Array<int> arr;

    for (int i = 0; i < ARR_LEN; i++) {
        arr.pushBack(i);
    }

    int removeIndex = ARR_LEN - 2;
    arr.remove(removeIndex);
    BOOST_CHECK_EQUAL(arr.size(), ARR_LEN - 1);

    int want[] = {0, 1, 2, 3, 4, 5, 6, 7, 9};

    for (int i = 0; i < ARR_LEN - 1; i++) {
        BOOST_CHECK_EQUAL(arr[i], want[i]);
    }
}

BOOST_AUTO_TEST_CASE(test_set) {
    const int ARR_LEN = 10;
    Array<int> arr;

    for (int i = 0; i < ARR_LEN; i++) {
        arr.pushBack(i);
    }

    int setIndex = ARR_LEN - 2;
    int testValue = generateRandomNumber(0, 10000);
    arr.set(setIndex, testValue);

    BOOST_CHECK_EQUAL(arr.size(), ARR_LEN);
    BOOST_CHECK_EQUAL(arr[setIndex], testValue);
}

BOOST_AUTO_TEST_CASE(benchmark_pushBack) {
    Array<int> arr;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++) {
        arr.pushBack(i);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Execution 100000 insert time: " << duration.count() << " microseconds" << endl;

    BOOST_CHECK(true);
}