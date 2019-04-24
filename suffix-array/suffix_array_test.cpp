
//
// suffix_array.cpp
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "suffix_array.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

TEST_CASE("Suffix Array: sanity check", "[sanity]") {
    REQUIRE(true);
}

TEST_CASE("Suffix Array: init_suffix_array", "[init]") {
    suffix_array* test_array = init_suffix_array(); 
    REQUIRE(test_array != NULL);
}
