// test_vector.cpp
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "vector.hpp"
#include <stdexcept>

// test cases from Part 1

TEST_CASE("Default constructor creates empty vector") {
    dsa::Vector<int> v;
    bool ok = (v.size() == 0) && (v.capacity() == 0) && v.empty();
    
    REQUIRE(ok);
}

