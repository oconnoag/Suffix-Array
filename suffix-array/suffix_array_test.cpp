
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

/************************************************************/
/*********** Forward Declaration of Test Fxns ***************/
/************************************************************/

Suffix_Array* make_banana_sa();

/************************************************************/
/*********** TESTS **************/
/************************************************************/

TEST_CASE("Suffix Array: sanity check", "[sanity]") {
    REQUIRE(true);
}

TEST_CASE("Suffix Array: init_suffix_array", "[init]") {
    string test_string = "banana";
    Suffix_Array* test_array = new Suffix_Array(test_string);

    REQUIRE(test_array != NULL);
    REQUIRE(test_array->get_orig_text() == test_string);
    REQUIRE(test_array->get_num_suffixes() == 6);

    // Test the generated index_array
    int expected_index_array[6] = {5,3,1,0,4,2};
    int num_indicies = test_array->get_num_suffixes();

    for (int i=0; i < num_indicies; i++) {
        REQUIRE(expected_index_array[i] == test_array->get_index_array()[i]);
    }

    // Test the generated lcp
    int expected_lcp_array[6] = {0,1,3,0,0,2};

    for (int i=0; i < num_indicies; i++) {
        REQUIRE(expected_lcp_array[i] == test_array->get_lcp()[i]);
    }

    // TODO Add more tests
    // - Genomic String, Edge Cases (empty string?), Non-ASCII?

    delete test_array;
}

TEST_CASE("Suffix Array : substrings", "[substrings]") {
    Suffix_Array* test_array = make_banana_sa();

    // 0-length substr
    REQUIRE(test_array->get_substring(0, 0) == "");

    // Normal
    REQUIRE(test_array->get_substring(0, 1) == "b");
    REQUIRE(test_array->get_substring(0, 2) == "ba");
    REQUIRE(test_array->get_substring(0, 6) == "banana");

    // Internal
    REQUIRE(test_array->get_substring(1, 1) == "a");
    REQUIRE(test_array->get_substring(2, 1) == "n");
    REQUIRE(test_array->get_substring(2, 3) == "nan");

    // Out of bounds substring returns full
    REQUIRE(test_array->get_substring(0, 8) == "banana");
    REQUIRE(test_array->get_substring(2, 8) == "nana");

    // Negative Index/length
    REQUIRE(test_array->get_substring(-1, 7) == "ERROR");
    REQUIRE(test_array->get_substring(1, -1) == "ERROR");

    delete test_array;

}

TEST_CASE("Suffix Array : search_exact", "[search_exact]") {
    Suffix_Array* test_array = make_banana_sa();

    // Substrings present in string
    REQUIRE( test_array->search_exact("banana") == 1 );
    REQUIRE( test_array->search_exact("anana") == 1 );
    REQUIRE( test_array->search_exact("ana") == 1 );
    REQUIRE( test_array->search_exact("a") == 1 );

    // Character not in orig_string
    REQUIRE( test_array->search_exact("q") == 0 );

    // Empty string should be handled as false
    REQUIRE( test_array->search_exact("") == 0 );

    delete test_array;

}

TEST_CASE("Suffix Array : search_inexact", "[search_inexact]") {
    Suffix_Array* test_array = make_banana_sa();

    // Substrings present in string with different thresholds
    REQUIRE( test_array->search_inexact("banana", 0) == 1 );
    REQUIRE( test_array->search_inexact("anana", 1) == 1 );
    REQUIRE( test_array->search_inexact("ana", 2) == 1 );
    REQUIRE( test_array->search_inexact("a", 3) == 1 );
    REQUIRE( test_array->search_inexact("bxxxx", 10) == 1 );

    // Substrings off by 1
    REQUIRE( test_array->search_inexact("br", 1) == 1 );
    REQUIRE( test_array->search_inexact("nar", 1) == 1 );
    REQUIRE( test_array->search_inexact("banant", 1) == 1 );

    // Substrings with intermittent mismatches
    REQUIRE( test_array->search_inexact("bxnxnx", 3) == 1 );

    // Substrings off by more than threshold
    REQUIRE( test_array->search_inexact("banant", 0) == 0 );
    REQUIRE( test_array->search_inexact("arara", 1) == 0 );
    REQUIRE( test_array->search_inexact("bxxxx", 3) == 0 );

    // Substrings with first letter mismatched
    REQUIRE( test_array->search_inexact("xanana", 3) == 0 );
    REQUIRE( test_array->search_inexact("xnana", 3) == 0 );

    // Character not in orig_string
    REQUIRE( test_array->search_inexact("q", 1) == 0 );

    // Empty string should be handled as false
    REQUIRE( test_array->search_inexact("", 1) == 0 );

    // Threshold must be positive
    REQUIRE( test_array->search_inexact("banant", -1) == 0 );

    delete test_array;

}

/************************************************************/
/********************* TEST FXNS ****************************/
/************************************************************/

Suffix_Array *make_banana_sa() {
    string test_string = "banana";
    Suffix_Array* test_array = new Suffix_Array(test_string);
    return test_array;
}
