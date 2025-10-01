#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "vector.hpp"
#include <stdexcept>

TEST_CASE("Default constructor creates empty vector") {
    dsa::Vector<int> v;
    REQUIRE(v.empty());
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
}

TEST_CASE("Capacity and size functions") {
    dsa::Vector<int> v;
    
    SECTION("Empty vector") {
        REQUIRE(v.capacity() == 0);
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty() == true);
    }
    
    SECTION("After adding elements") {
        v.reserve(10);
        REQUIRE(v.capacity() == 10);
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty() == true);
        
        v.push_back(1);
        REQUIRE(v.size() == 1);
        REQUIRE(v.empty() == false);
    }
}

TEST_CASE("Empty function") {
    dsa::Vector<int> v;
    
    SECTION("New vector is empty") {
        REQUIRE(v.empty() == true);
    }
    
    SECTION("Vector with elements is not empty") {
        v.push_back(10);
        REQUIRE(v.empty() == false);
        
        v.pop_back();
        REQUIRE(v.empty() == true);
    }
}

TEST_CASE("Operator[] access") {
    dsa::Vector<int> v;
    
    SECTION("Non-const access for modification") {
        v.push_back(1);
        v.push_back(2);
        v[0] = 10;
        v[1] = 20;
        
        REQUIRE(v[0] == 10);
        REQUIRE(v[1] == 20);
    }
    
    SECTION("Const access for reading") {
        v.push_back(5);
        v.push_back(15);
        
        const dsa::Vector<int>& const_v = v;
        REQUIRE(const_v[0] == 5);
        REQUIRE(const_v[1] == 15);
    }
}

TEST_CASE("At function with bounds checking") {
    dsa::Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    SECTION("Valid indices") {
        REQUIRE(v.at(0) == 10);
        REQUIRE(v.at(2) == 30);
        
        const dsa::Vector<int>& const_v = v;
        REQUIRE(const_v.at(1) == 20);
    }
    
    SECTION("Invalid indices throw exceptions") {
        REQUIRE_THROWS_AS(v.at(-1), std::out_of_range);
        REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
        REQUIRE_THROWS_AS(v.at(100), std::out_of_range);
    }
}

TEST_CASE("Front and back functions") {
    dsa::Vector<int> v;
    
    SECTION("Single element vector") {
        v.push_back(42);
        
        REQUIRE(v.front() == 42);
        REQUIRE(v.back() == 42);
        
        v.front() = 100;
        REQUIRE(v.front() == 100);
        REQUIRE(v.back() == 100);
    }
    
    SECTION("Multiple element vector") {
        v.push_back(10);
        v.push_back(20);
        v.push_back(30);
        
        REQUIRE(v.front() == 10);
        REQUIRE(v.back() == 30);
        
        const dsa::Vector<int>& const_v = v;
        REQUIRE(const_v.front() == 10);
        REQUIRE(const_v.back() == 30);
    }
}

TEST_CASE("Push back function") {
    dsa::Vector<int> v;
    
    SECTION("Adding to empty vector") {
        v.push_back(5);
        REQUIRE(v.size() == 1);
        REQUIRE(v[0] == 5);
        REQUIRE(v.capacity() >= 1);
    }
    
    SECTION("Multiple additions with capacity growth") {
        // Initial capacity is 0, should grow to 1, then 2, then 4, etc.
        for (int i = 0; i < 10; ++i) {
            v.push_back(i * 10);
            REQUIRE(v.size() == i + 1);
            REQUIRE(v[i] == i * 10);
        }
        REQUIRE(v.capacity() >= 10);
    }
}

TEST_CASE("Pop back function") {
    dsa::Vector<int> v;
    
    SECTION("Single pop from multiple elements") {
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        
        v.pop_back();
        REQUIRE(v.size() == 2);
        REQUIRE(v.back() == 2);
    }
    
    SECTION("Multiple pops until empty") {
        v.push_back(10);
        v.push_back(20);
        
        v.pop_back();
        REQUIRE(v.size() == 1);
        REQUIRE(v.back() == 10);
        
        v.pop_back();
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty() == true);
    }
}

TEST_CASE("Insert function") {
    dsa::Vector<int> v;
    
    SECTION("Insert at beginning") {
        v.push_back(2);
        v.push_back(3);
        v.insert(0, 1);
        
        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
    }
    
    SECTION("Insert in middle with capacity growth") {
        v.push_back(1);
        v.push_back(4);
        
        // Force small capacity to test growth during insert
        v.shrink_to_fit();
        v.insert(1, 2);
        v.insert(2, 3);
        
        REQUIRE(v.size() == 4);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(v[3] == 4);
    }
}

TEST_CASE("Erase function") {
    dsa::Vector<int> v;
    
    SECTION("Erase from beginning") {
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        
        v.erase(0);
        REQUIRE(v.size() == 2);
        REQUIRE(v[0] == 2);
        REQUIRE(v[1] == 3);
    }
    
    SECTION("Erase from middle and end") {
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        
        v.erase(1); // Remove element at index 1 (value 2)
        REQUIRE(v.size() == 3);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 3);
        REQUIRE(v[2] == 4);
        
        v.erase(2); // Remove last element
        REQUIRE(v.size() == 2);
        REQUIRE(v.back() == 3);
    }
}

TEST_CASE("Reserve function") {
    dsa::Vector<int> v;
    
    SECTION("Reserve increases capacity") {
        REQUIRE(v.capacity() == 0);
        
        v.reserve(10);
        REQUIRE(v.capacity() == 10);
        REQUIRE(v.size() == 0);
    }
    
    SECTION("Reserve preserves existing elements") {
        v.push_back(1);
        v.push_back(2);
        
        v.reserve(20);
        REQUIRE(v.capacity() == 20);
        REQUIRE(v.size() == 2);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
    }
    
    SECTION("Smaller reserve doesn't reduce capacity") {
        v.reserve(10);
        int old_cap = v.capacity();
        
        v.reserve(5); // Should not reduce capacity
        REQUIRE(v.capacity() == old_cap);
    }
}

TEST_CASE("Shrink function") {
    dsa::Vector<int> v;
    
    SECTION("Shrink when size <= capacity/4") {
        // Fill vector to get reasonable capacity
        for (int i = 0; i < 10; ++i) {
            v.push_back(i);
        }
        int original_cap = v.capacity();
        
        // Remove elements until size <= capacity/4
        while (v.size() > original_cap / 4) {
            v.pop_back();
        }
        
        // Trigger shrink
        v.shrink();
        REQUIRE(v.capacity() < original_cap);
        REQUIRE(v.capacity() >= v.size());
    }
    
    SECTION("No shrink when size > capacity/4") {
        v.push_back(1);
        v.push_back(2);
        int original_cap = v.capacity();
        
        v.shrink(); // Should not shrink since size > capacity/4
        REQUIRE(v.capacity() == original_cap);
    }
}

TEST_CASE("Shrink to fit function") {
    dsa::Vector<int> v;
    
    SECTION("Shrink to exact size") {
        for (int i = 0; i < 5; ++i) {
            v.push_back(i);
        }
        int original_cap = v.capacity();
        
        // Remove some elements to create unused capacity
        v.pop_back();
        v.pop_back();
        
        REQUIRE(v.capacity() == original_cap); // Capacity unchanged
        v.shrink_to_fit();
        REQUIRE(v.capacity() == v.size());
        REQUIRE(v.capacity() >= 1);
    }
    
    SECTION("Shrink empty vector") {
        v.reserve(10);
        REQUIRE(v.capacity() == 10);
        
        v.shrink_to_fit();
        REQUIRE(v.capacity() == 1); // Minimum capacity of 1
    }
}

TEST_CASE("Integration test - complex operations") {
    dsa::Vector<int> v;
    
    SECTION("Mixed operations") {
        // Start empty
        REQUIRE(v.empty());
        
        // Add elements
        for (int i = 0; i < 5; ++i) {
            v.push_back(i * 10);
        }
        REQUIRE(v.size() == 5);
        REQUIRE(v.front() == 0);
        REQUIRE(v.back() == 40);
        
        // Insert in middle
        v.insert(2, 25);
        REQUIRE(v[2] == 25);
        REQUIRE(v.size() == 6);
        
        // Erase from beginning
        v.erase(0);
        REQUIRE(v.front() == 10);
        
        // Pop from end
        v.pop_back();
        REQUIRE(v.back() == 30);
        
        // Modify elements
        v[1] = 100;
        REQUIRE(v[1] == 100);
        
        // Final validation
        REQUIRE(v.size() == 4);
        REQUIRE_FALSE(v.empty());
    }
}
