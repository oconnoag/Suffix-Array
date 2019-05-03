
//
// suffix_array.cpp
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include "suffix_array.h"
#include <string>
#include <vector>
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

TEST_CASE("Suffix Array : Binary Search", "[binary_search]") {
    Suffix_Array* test_array = make_banana_sa();

    // Within the suffix range
    REQUIRE( test_array->binary_search("ban") == 3 );
    REQUIRE( test_array->binary_search("banana") == 3 );
    REQUIRE( test_array->binary_search("b") == 3 );
    REQUIRE( test_array->binary_search("a") == 0 );
    REQUIRE( test_array->binary_search("ana") == 1 );
    REQUIRE( test_array->binary_search("anana") == 2 );
    REQUIRE( test_array->binary_search("anan") == 2 );
    REQUIRE( test_array->binary_search("nana") == 5 );
    REQUIRE( test_array->binary_search("n") == 4 );
    REQUIRE( test_array->binary_search("na") == 4 );

    // Outside of the ranges of the suffixes
    REQUIRE( test_array->binary_search("zan") == 5 );
    REQUIRE( test_array->binary_search("J") == 0 );

    // Within the suffix range, but not actually matching
    REQUIRE( test_array->binary_search("fred") == 4 );
    REQUIRE( test_array->binary_search("cat") == 4 );

    delete test_array;

    /********************* Longer Test ************************/

    char gen_str[] = "cccccttttttagggcctgctgctgctgctgctg";
    Suffix_Array genetic = Suffix_Array(gen_str);

    // First letter sections
    REQUIRE( genetic.binary_search("a") == 0 );
    REQUIRE( genetic.binary_search("c") == 1 );
    REQUIRE( genetic.binary_search("g") == 13 );
    REQUIRE( genetic.binary_search("t") == 22 );

    // Matches
    REQUIRE( genetic.binary_search("ctg") == 6 );

    // Non Matches
    REQUIRE( genetic.binary_search("cta") == 6 );

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
    string str6 = "bar";
    string str7 = "xana";
    string str8 = " ";
    REQUIRE( test_array->search_exact(str5) == 0 );
    REQUIRE( test_array->search_exact(str6) == 0 );
    REQUIRE( test_array->search_exact(str7) == 0 );
    REQUIRE( test_array->search_exact(str8) == 0 );

    delete test_array;
}

TEST_CASE("Suffix Array : find_all_exact", "[find_all_exact]") {
    Suffix_Array* test_array = make_banana_sa();

    // Substrings present in string
    string str1 = "banana";
    string str2 = "ana";
    string str3 = "a";

    vector<int> str1_expected = {0};
    vector<int> str2_expected = {3, 1};
    vector<int> str3_expected = {5, 3, 1};

    vector<int> str1_locs = test_array->find_all_exact(str1);
    vector<int> str2_locs = test_array->find_all_exact(str2);
    vector<int> str3_locs = test_array->find_all_exact(str3);

    for (unsigned long i=0; i < str1_locs.size(); i++) {
        REQUIRE( str1_locs.at(i) == str1_expected.at(i) );
    }

    for (unsigned long i=0; i < str2_locs.size(); i++) {
        cout << str2_locs.at(i) << endl;
        REQUIRE( str2_locs.at(i) == str2_expected.at(i) );
    }

    for (unsigned long i=0; i < str3_locs.size(); i++) {
        REQUIRE( str3_locs.at(i) == str3_expected.at(i) );
    }

    // Character not in orig_string
    string str4 = "q";

    vector<int> str4_expected = test_array->find_all_exact(str4);

    REQUIRE(str4_expected.empty());

    delete test_array;
}

TEST_CASE("String Method : inexact_compare", "[inexact_compare]") {
    string str1 = "Alijah";
    string str2 = "Alijah";
    string str3 = "Alijar";
    string str4 = "Hajila";
    string str5 = "k";

    // Exact
    REQUIRE( inexact_compare(str1, str2, 6, 0) == 1);
    REQUIRE( inexact_compare(str1, str2, 6, 1) == 1);
    REQUIRE( inexact_compare(str1, str2, 3, 0) == 1);

    // Not Exact
    REQUIRE( inexact_compare(str1, str3, 6, 1) == 1);
    REQUIRE( inexact_compare(str1, str3, 6, 0) == 0);
    REQUIRE( inexact_compare(str1, str3, 3, 0) == 1);

    // Quite Different
    REQUIRE( inexact_compare(str1, str4, 6, 0) == 0);
    REQUIRE( inexact_compare(str1, str4, 6, 5) == 0);
    REQUIRE( inexact_compare(str1, str4, 6, 6) == 1);

    // Short String
    REQUIRE( inexact_compare(str1, str5, 6, 3) == 0);
    REQUIRE( inexact_compare(str5, str1, 6, 3) == 0);
    REQUIRE( inexact_compare(str5, str1, 2, 3) == 0);

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
    REQUIRE( test_array->search_inexact(str_q, 1) == 1 );

    // Empty string should return 1
    string empty = "";
    REQUIRE( test_array->search_inexact(empty, 1) == 1 );

    // Threshold must be positive
    REQUIRE( test_array->search_inexact(str_banant, -1) == 0 );

    delete test_array;
}

TEST_CASE("Suffix Array : find_all_inexact", "[find_all_inexact]") {
    Suffix_Array* test_array = make_banana_sa();

    /************ substring in original -- no threshold *******************/
    string str1 = "banana";
    string str2 = "ana";
    string str3 = "na";

    vector<int> str1_expected = {0};
    vector<int> str2_expected = {3, 1};
    vector<int> str3_expected = {4, 2};

    vector<int> str1_locs = test_array->find_all_inexact(str1, 0);
    vector<int> str2_locs = test_array->find_all_inexact(str2, 0);
    vector<int> str3_locs = test_array->find_all_inexact(str3, 0);

    for (unsigned long i=0; i < str1_locs.size(); i++) {
        REQUIRE( str1_locs.at(i) == str1_expected.at(i) );
    }

    for (unsigned long i=0; i < str2_locs.size(); i++) {
        REQUIRE( str2_locs.at(i) == str2_expected.at(i) );
    }

    for (unsigned long i=0; i < str3_locs.size(); i++) {
        REQUIRE( str3_locs.at(i) == str3_expected.at(i) );
    }

    /************** Char not in string -- no threshold ******************/
    string str4 = "q";

    vector<int> str4_expected = test_array->find_all_inexact(str4, 0);

    REQUIRE(str4_expected.empty());

    /************** Inexact Strings with thresholds ******************/
    string str5 = "banant";
    string str6 = "arr";
    string str7 = "arara";

    vector<int> str5_expected = {0};
    vector<int> str6_expected = {3, 1};
    vector<int> str7_expected = {1};
    vector<int> str7_expected2 = {};

    vector<int> str5_locs = test_array->find_all_inexact(str5, 1);
    vector<int> str6_locs = test_array->find_all_inexact(str6, 2);
    vector<int> str7_locs = test_array->find_all_inexact(str7, 3);
    vector<int> str7_locs2 = test_array->find_all_inexact(str7, 1);

    for (unsigned long i=0; i < str5_locs.size(); i++) {
        REQUIRE( str5_locs.at(i) == str5_expected.at(i) );
    }

    for (unsigned long i=0; i < str6_locs.size(); i++) {
        REQUIRE( str6_locs.at(i) == str6_expected.at(i) );
    }

    for (unsigned long i=0; i < str7_locs.size(); i++) {
        REQUIRE( str7_locs.at(i) == str7_expected.at(i) );
    }

    REQUIRE( str7_locs2.empty() );

    delete test_array;

    /****************** Genetic **********************/
    /****************** More Complex **********************/

    char gen_str[] = "cccccttttttagggcctgctgctgctgctgctg";
    Suffix_Array genetic = Suffix_Array(gen_str);

    string str8 = "cctcc";

    vector<int> str8_locs0 = genetic.find_all_inexact(str8, 0);
    vector<int> str8_locs1 = genetic.find_all_inexact(str8, 1);
    vector<int> str8_locs2 = genetic.find_all_inexact(str8, 2);
    vector<int> str8_locs3 = genetic.find_all_inexact(str8, 3);

    vector<int> str8_expected1 = {0, 15};
    vector<int> str8_expected2 = {0, 1, 15, 3};
    vector<int> str8_expected3 = {0, 1, 2, 15, 3, 28, 25, 22, 19, 16, 4};

    REQUIRE( str8_locs0.empty() );

    for (unsigned long i=0; i < str8_locs1.size(); i++) {
        REQUIRE( str8_locs1.at(i) == str8_expected1.at(i) );
    }

    for (unsigned long i=0; i < str8_locs2.size(); i++) {
        REQUIRE( str8_locs2.at(i) == str8_expected2.at(i) );
    }

    for (unsigned long i=0; i < str8_locs3.size(); i++) {
        REQUIRE( str8_locs3.at(i) == str8_expected3.at(i) );
    }

    // Long searcher (point mutation)
    string pnt_mutation = "cccccttttttagggcctcctgctgctgctgctg";

    vector<int> pnt_mut_expected = {0};
    vector<int> pnt_mut_loc = genetic.find_all_inexact(pnt_mutation, 1);

    for (unsigned long i=0; i < pnt_mut_loc.size(); i++) {
        REQUIRE( pnt_mut_loc.at(i) == pnt_mut_expected.at(i) );
    }
}

/************************************************************/
/********************* TEST FXNS ****************************/
/************************************************************/

Suffix_Array *make_banana_sa() {
    char test_string[] = "banana";
    Suffix_Array* test_array = new Suffix_Array(test_string);
    return test_array;
}
