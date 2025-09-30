// test_vector_iterator.cpp
//#define CATCH_CONFIG_MAIN // must be in one
#include "catch2/catch.hpp"
#include <algorithm>  //for std::max
#include "vector.hpp"
#include "matrix.hpp"

TEST_CASE("non-const iterator dereference") {
    dsa::Vector<int> v; bool ok{true};
    for (int i{1}; i<=5; i++) 
        v.push_back(i);
    auto it = v.begin();
    ok = ok && (*it == 1);
    *it = 10;
    ok = ok && (v[0] == 10);
    
    REQUIRE(ok);
}

