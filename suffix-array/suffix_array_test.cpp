
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
    char input_text[] = "banana";
    string test_string = "banana";
    Suffix_Array* test_array = new Suffix_Array(input_text);

    REQUIRE(test_array != NULL);
    REQUIRE(test_array->get_orig_text() == test_string);
    REQUIRE(test_array->get_orig_text_length() == 6);
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

    /******************************************/

    char input_text2[] = "aaccttgg";
    Suffix_Array genetic = Suffix_Array(input_text2);
    int genetic_num_suffixes = genetic.get_num_suffixes();

    REQUIRE(genetic.get_orig_text() == input_text2);
    REQUIRE(genetic.get_orig_text_length() == 8);

    REQUIRE(genetic_num_suffixes == 8);

    int genetic_expected_sa[8] = {0,1,2,3,7,6,5,4};
    int genetic_expected_lcp[8] = {0,1,0,1,0,1,0,1};

    for (int i=0; i < genetic_num_suffixes; i++) {
        REQUIRE(genetic.get_index_array()[i] == genetic_expected_sa[i]);
    }

    for (int i=0; i < genetic_num_suffixes; i++) {
        REQUIRE(genetic.get_lcp()[i] == genetic_expected_lcp[i]);
    }

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
    string str1 = "banana";
    string str2 = "anana";
    string str3 = "ana";
    string str4 = "a";
    REQUIRE( test_array->search_exact(str1) == 1 );
    REQUIRE( test_array->search_exact(str2) == 1 );
    REQUIRE( test_array->search_exact(str3) == 1 );
    REQUIRE( test_array->search_exact(str4) == 1 );

    // Character not in orig_string
    string str5 = "q";
    REQUIRE( test_array->search_exact(str5) == 0 );

    // Empty string should be handled as false
    string empty = "";
    REQUIRE( test_array->search_exact(empty) == 0 );

    delete test_array;

}

TEST_CASE("Suffix Array : search_inexact", "[search_inexact]") {
    Suffix_Array* test_array = make_banana_sa();

    // Substrings present in string with different thresholds
    string str_banana = "banana";
    string str_anana = "anana";
    string str_ana = "ana";
    string str_a = "a";
    string str_bxxxx = "bxxxx";
    REQUIRE( test_array->search_inexact(str_banana, 0) == 1 );
    REQUIRE( test_array->search_inexact(str_anana, 1) == 1 );
    REQUIRE( test_array->search_inexact(str_ana, 2) == 1 );
    REQUIRE( test_array->search_inexact(str_a, 3) == 1 );
    REQUIRE( test_array->search_inexact(str_bxxxx, 10) == 1 );

    // Substrings off by 1
    string str_br = "br";
    string str_nar = "nar";
    string str_banant = "banant";
    REQUIRE( test_array->search_inexact(str_br, 1) == 1 );
    REQUIRE( test_array->search_inexact(str_nar, 1) == 1 );
    REQUIRE( test_array->search_inexact(str_banant, 1) == 1 );

    // Substrings with intermittent mismatches
    string str_bxnxnx = "bxnxnx";
    REQUIRE( test_array->search_inexact(str_bxnxnx, 3) == 1 );

    // Substrings off by more than threshold
    string str_arara = "arara";
    REQUIRE( test_array->search_inexact(str_banant, 0) == 0 );
    REQUIRE( test_array->search_inexact(str_arara, 1) == 0 );
    REQUIRE( test_array->search_inexact(str_bxxxx, 3) == 0 );

    // Substrings with first letter mismatched
    string str_xanana = "xanana";
    string str_xnana = "xnana";
    REQUIRE( test_array->search_inexact(str_xanana, 3) == 0 );
    REQUIRE( test_array->search_inexact(str_xnana, 3) == 0 );

    // Character not in orig_string
    string str_q = "q";
    REQUIRE( test_array->search_inexact(str_q, 1) == 0 );

    // Empty string should be handled as false
    string empty = "";
    REQUIRE( test_array->search_inexact(empty, 1) == 0 );

    // Threshold must be positive
    REQUIRE( test_array->search_inexact(str_banant, -1) == 0 );

    delete test_array;

}

/************************************************************/
/********************* TEST FXNS ****************************/
/************************************************************/

Suffix_Array *make_banana_sa() {
    char test_string[] = "banana";
    Suffix_Array* test_array = new Suffix_Array(test_string);
    return test_array;
}
