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

TEST_CASE("Vector Basic Operations", "[vector]") {
    dsa::Vector<int> vec;
    
    SECTION("Default constructor") {
        REQUIRE(vec.size() == 0);
        REQUIRE(vec.capacity() == 0);
        REQUIRE(vec.empty());
    }
    
    SECTION("Push back and access") {
        vec.push_back(1);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec.at(0) == 1);
        REQUIRE_FALSE(vec.empty());
        
        vec.push_back(2);
        vec.push_back(3);
        REQUIRE(vec.size() == 3);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
        REQUIRE(vec[2] == 3);
    }
    
    SECTION("Front and back") {
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        
        REQUIRE(vec.front() == 10);
        REQUIRE(vec.back() == 30);
        
        const dsa::Vector<int>& const_vec = vec;
        REQUIRE(const_vec.front() == 10);
        REQUIRE(const_vec.back() == 30);
    }
    
    SECTION("Out of bounds access") {
        REQUIRE_THROWS_AS(vec.at(0), std::out_of_range);
        REQUIRE_THROWS_AS(vec.front(), std::out_of_range);
        REQUIRE_THROWS_AS(vec.back(), std::out_of_range);
        
        vec.push_back(1);
        REQUIRE_THROWS_AS(vec.at(1), std::out_of_range);
        REQUIRE_NOTHROW(vec.at(0));
    }
}

TEST_CASE("Vector Insert and Erase", "[vector]") {
    dsa::Vector<int> vec;
    
    SECTION("Insert at beginning") {
        vec.push_back(2);
        vec.push_back(3);
        vec.insert(0, 1);
        
        REQUIRE(vec.size() == 3);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
        REQUIRE(vec[2] == 3);
    }
    
    SECTION("Insert at middle") {
        vec.push_back(1);
        vec.push_back(3);
        vec.insert(1, 2);
        
        REQUIRE(vec.size() == 3);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
        REQUIRE(vec[2] == 3);
    }
    
    SECTION("Insert at end") {
        vec.push_back(1);
        vec.push_back(2);
        vec.insert(2, 3);
        
        REQUIRE(vec.size() == 3);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
        REQUIRE(vec[2] == 3);
    }
    
    SECTION("Erase elements") {
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        
        vec.erase(1);
        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 3);
        
        vec.erase(0);
        REQUIRE(vec.size() == 1);
        REQUIRE(vec[0] == 3);
    }
    
    SECTION("Invalid insert/erase") {
        REQUIRE_THROWS_AS(vec.insert(-1, 1), std::out_of_range);
        REQUIRE_THROWS_AS(vec.insert(1, 1), std::out_of_range);
        REQUIRE_THROWS_AS(vec.erase(0), std::out_of_range);
    }
}

TEST_CASE("Vector Pop Back", "[vector]") {
    dsa::Vector<int> vec;
    
    SECTION("Pop from non-empty vector") {
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        
        vec.pop_back();
        REQUIRE(vec.size() == 2);
        REQUIRE(vec.back() == 2);
        
        vec.pop_back();
        REQUIRE(vec.size() == 1);
        REQUIRE(vec.back() == 1);
    }
    
    SECTION("Pop from empty vector") {
        REQUIRE_THROWS_AS(vec.pop_back(), std::out_of_range);
    }
}

TEST_CASE("Vector Reserve and Capacity", "[vector]") {
    dsa::Vector<int> vec;
    
    SECTION("Reserve increases capacity") {
        vec.reserve(10);
        REQUIRE(vec.capacity() >= 10);
        REQUIRE(vec.size() == 0);
        
        // Add elements after reserve
        for(int i = 0; i < 5; i++) {
            vec.push_back(i);
        }
        REQUIRE(vec.size() == 5);
        REQUIRE(vec.capacity() >= 10);
    }
    
    SECTION("Automatic resizing during push_back") {
        // Small initial pushes
        for(int i = 0; i < 10; i++) {
            vec.push_back(i);
        }
        REQUIRE(vec.size() == 10);
        REQUIRE(vec.capacity() >= 10);
        
        // Force resize
        for(int i = 10; i < 20; i++) {
            vec.push_back(i);
        }
        REQUIRE(vec.size() == 20);
        REQUIRE(vec.capacity() >= 20);
    }
}

TEST_CASE("Vector Iterators", "[vector][iterator]") {
    dsa::Vector<int> vec;
    
    SECTION("Empty vector iterators") {
        REQUIRE(vec.begin() == vec.end());
    }
    
    SECTION("Iterator traversal") {
        for(int i = 0; i < 5; i++) {
            vec.push_back(i * 10);
        }
        
        int expected = 0;
        for(auto it = vec.begin(); it != vec.end(); ++it) {
            REQUIRE(*it == expected);
            expected += 10;
        }
        
        // Test post-increment
        auto it = vec.begin();
        REQUIRE(*it == 0);
        auto old_it = it++;
        REQUIRE(*old_it == 0);
        REQUIRE(*it == 10);
    }
    
    SECTION("Const iterators") {
        vec.push_back(1);
        vec.push_back(2);
        
        const dsa::Vector<int>& const_vec = vec;
        int sum = 0;
        for(auto it = const_vec.begin(); it != const_vec.end(); ++it) {
            sum += *it;
        }
        REQUIRE(sum == 3);
    }
    
    SECTION("Iterator insert and erase") {
        vec.push_back(1);
        vec.push_back(3);
        
        auto it = vec.begin();
        ++it; // points to 3
        vec.insert(it, 2);
        
        REQUIRE(vec.size() == 3);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 2);
        REQUIRE(vec[2] == 3);
        
        it = vec.begin();
        ++it; // points to 2
        vec.erase(it);
        
        REQUIRE(vec.size() == 2);
        REQUIRE(vec[0] == 1);
        REQUIRE(vec[1] == 3);
    }
}

TEST_CASE("Vector Rule of Five", "[vector]") {
    SECTION("Copy constructor") {
        dsa::Vector<int> original;
        original.push_back(1);
        original.push_back(2);
        original.push_back(3);
        
        dsa::Vector<int> copy(original);
        REQUIRE(copy.size() == original.size());
        for(int i = 0; i < original.size(); i++) {
            REQUIRE(copy[i] == original[i]);
        }
        
        // Ensure they are independent
        copy.push_back(4);
        REQUIRE(copy.size() == 4);
        REQUIRE(original.size() == 3);
    }
    
    SECTION("Copy assignment") {
        dsa::Vector<int> original;
        original.push_back(1);
        original.push_back(2);
        
        dsa::Vector<int> copy;
        copy = original;
        
        REQUIRE(copy.size() == original.size());
        for(int i = 0; i < original.size(); i++) {
            REQUIRE(copy[i] == original[i]);
        }
    }
    
    SECTION("Move constructor") {
        dsa::Vector<int> original;
        original.push_back(1);
        original.push_back(2);
        
        dsa::Vector<int> moved(std::move(original));
        REQUIRE(moved.size() == 2);
        REQUIRE(moved[0] == 1);
        REQUIRE(moved[1] == 2);
        REQUIRE(original.size() == 0); // NOLINT: intentional use after move
    }
    
    SECTION("Move assignment") {
        dsa::Vector<int> original;
        original.push_back(1);
        original.push_back(2);
        
        dsa::Vector<int> moved;
        moved = std::move(original);
        REQUIRE(moved.size() == 2);
        REQUIRE(moved[0] == 1);
        REQUIRE(moved[1] == 2);
        REQUIRE(original.size() == 0); // NOLINT: intentional use after move
    }
}

TEST_CASE("Matrix Basic Operations", "[matrix]") {
    SECTION("Valid matrix construction") {
        dsa::Matrix mat(2, 3);
        REQUIRE_NOTHROW(mat(0, 0) = 1);
        REQUIRE_NOTHROW(mat(1, 2) = 6);
        
        // Test that values are stored correctly
        mat(0, 0) = 5;
        REQUIRE(mat(0, 0) == 5);
    }
    
    SECTION("Invalid matrix construction") {
        REQUIRE_THROWS_AS(dsa::Matrix(-1, 2), std::out_of_range);
        REQUIRE_THROWS_AS(dsa::Matrix(2, -1), std::out_of_range);
        REQUIRE_THROWS_AS(dsa::Matrix(-1, -1), std::out_of_range);
    }
    
    SECTION("Matrix addition") {
        dsa::Matrix mat1(2, 2);
        dsa::Matrix mat2(2, 2);
        
        // Initialize matrices
        mat1(0, 0) = 1; mat1(0, 1) = 2;
        mat1(1, 0) = 3; mat1(1, 1) = 4;
        
        mat2(0, 0) = 5; mat2(0, 1) = 6;
        mat2(1, 0) = 7; mat2(1, 1) = 8;
        
        dsa::Matrix result = mat1 + mat2;
        
        REQUIRE(result(0, 0) == 6);
        REQUIRE(result(0, 1) == 8);
        REQUIRE(result(1, 0) == 10);
        REQUIRE(result(1, 1) == 12);
    }
    
    SECTION("Matrix addition dimension mismatch") {
        dsa::Matrix mat1(2, 2);
        dsa::Matrix mat2(3, 3);
        
        REQUIRE_THROWS_AS(mat1 + mat2, std::out_of_range);
    }
}

TEST_CASE("Matrix Edge Cases", "[matrix]") {
    SECTION("Zero dimension matrix") {
        REQUIRE_NOTHROW(dsa::Matrix(0, 0));
        REQUIRE_NOTHROW(dsa::Matrix(0, 5));
        REQUIRE_NOTHROW(dsa::Matrix(5, 0));
    }
    
    SECTION("Single element matrix") {
        dsa::Matrix mat(1, 1);
        mat(0, 0) = 42;
        REQUIRE(mat(0, 0) == 42);
    }
    
    SECTION("Large matrix") {
        dsa::Matrix mat(10, 10);
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                mat(i, j) = i * 10 + j;
            }
        }
        
        // Verify some values
        REQUIRE(mat(5, 5) == 55);
        REQUIRE(mat(9, 9) == 99);
    }
}

TEST_CASE("Integration: Vector of Vectors as Matrix", "[integration]") {
    dsa::Vector<dsa::Vector<int>> matrix;
    
    // Create a 3x3 matrix using vectors
    for(int i = 0; i < 3; i++) {
        dsa::Vector<int> row;
        for(int j = 0; j < 3; j++) {
            row.push_back(i * 3 + j);
        }
        matrix.push_back(row);
    }
    
    REQUIRE(matrix.size() == 3);
    for(int i = 0; i < 3; i++) {
        REQUIRE(matrix[i].size() == 3);
        for(int j = 0; j < 3; j++) {
            REQUIRE(matrix[i][j] == i * 3 + j);
        }
    }
}
