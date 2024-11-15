#define BOOST_TEST_MODULE MapTest
#include "../dst/map.hpp"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test_put_get_remove) {
    Map<int> map;

    map.put("1", 10);
    map.put("2", 20);
    map.put("3", 30);

    BOOST_CHECK_EQUAL(map.size(), 3);
    BOOST_CHECK_EQUAL(map.get("1"), 10);
    BOOST_CHECK_EQUAL(map.get("2"), 20);
    BOOST_CHECK_EQUAL(map.get("3"), 30);

    map.remove("2");
    BOOST_CHECK_EQUAL(map.size(), 2);
    BOOST_CHECK_THROW(map.get("2"), runtime_error);
}

BOOST_AUTO_TEST_CASE(test_rehash) {
    Map<int> map;

    for (int i = 0; i < 20; i++) {
        map.put(to_string(i), i+1);
    }

    BOOST_CHECK_EQUAL(map.size(), 20);
    BOOST_CHECK_EQUAL(map.capacity(), 64);

    for (int i = 0; i < 20; i++) {
        BOOST_CHECK_EQUAL(map.get(to_string(i)), i+1);
    }
}

BOOST_AUTO_TEST_CASE(test_collision) {
    Map<int> map;

    map.put("CiBdo", 2);
    map.put("O7SFr", 3);
    map.put("a", 1);
    map.put("a", 4);
    BOOST_CHECK_EQUAL(map.size(), 3);
    BOOST_CHECK_EQUAL(map.get("a"), 4);
    BOOST_CHECK_EQUAL(map.get("CiBdo"), 2);
    BOOST_CHECK_EQUAL(map.get("O7SFr"), 3);

    map.remove("a");
    BOOST_CHECK_THROW(map.get("a"), runtime_error);
}

BOOST_AUTO_TEST_CASE(test_rehash_with_collision) {
    Map<int> map;

    map.put("a", 1);
    map.put("id9JQ", 2);
    map.put("wsbkj", 3);

    for (int i = 0; i < 8; i++) {
        map.put(to_string(i), i+1);
    }

    BOOST_CHECK_EQUAL(map.get("a"), 1);
    BOOST_CHECK_EQUAL(map.get("id9JQ"), 2);
    BOOST_CHECK_EQUAL(map.get("wsbkj"), 3);
}

BOOST_AUTO_TEST_CASE(test_replace) {
    Map<int> map;

    map.put("2", 10);
    map.put("1", 10);
    map.put("1", 20);
    BOOST_CHECK_EQUAL(map.size(), 2);
    BOOST_CHECK_EQUAL(map.get("1"), 20);
}

BOOST_AUTO_TEST_CASE(test_empty) {
    Map<int> map;

    BOOST_CHECK_EQUAL(map.size(), 0);
    BOOST_CHECK_THROW(map.get("1"), runtime_error);
    BOOST_CHECK_THROW(map.remove("1"), runtime_error);
}