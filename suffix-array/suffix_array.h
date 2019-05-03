#include <string>
#include <vector>

using namespace std;

struct Suffix {
    char*  suffix;
    int     index;

    // Overload the < operator to allow for comparison
    bool operator <(const Suffix& suff) const {
		return strcmp(suffix, suff.suffix) < 0 ? 1 : 0;
	}
};

class Suffix_Array {
private:
/************************************************************/
/*************** Attributes ****************/
/************************************************************/
    string         orig_text;
    int     orig_text_length;
    int*         index_array;
    int         num_suffixes;
    int*                 lcp; // Longest common prefix

/************************************************************/
/*************** Private Methods ****************/
/************************************************************/

    // Used to build the canonical banana string for testing purposes
    // Stores an int array to heap
    int* test_builder();

    // Builds the suffix array (index_array) for the inputed orig_text
    // using a naive approach with comparison-based sorting O( n^2 log(n) )
    int* naive_builder(char* input_text);

    // TODO
    int* skew_builder();

    // Builds the lcp for the canonical banana string for testing purposes
    int* test_lcp_builder();

    // Builds the lcp array using the Kasai algorithm
    // In short:  this algorithm uses the built suffix array to
    // walk along the suffixes one by one while keeping track of the
    // longest prefixes -- when the next suffix is being traversed however,
    // the counter is not reset to 0, so certain comparisons are skipped.
    //
    // This yields a complexity of O(n)
    int* lcp_builder(char* input_text);

public:

/************************************************************/
/*************** Constructors & Destructors ****************/
/************************************************************/
    Suffix_Array(char* input_text);
    ~Suffix_Array();

/************************************************************/
/*************** Getters ****************/
/************************************************************/
    string          get_orig_text() const;
    int      get_orig_text_length() const;
    int          get_num_suffixes() const;
    int*          get_index_array() const;
    int*                  get_lcp() const;

/************************************************************/
/*************** Methods ****************/
/************************************************************/
    // Print out a string representation of the suffix array
    void print_suffix_array();

    // Print out a string representation of the lcp
    void print_lcp();

    // Returns the portion of the original text that is of a specified length
    string get_substring(int index, int substring_len) const;

    // Prints the a substring of a particular length to the standard output
    // stream
    void print_substring(int index, int substring_len) const;

    // Performs the binary search for seraching/finding fxns
    //
    // Returns a int that corresponds to the index in original string that
    // best matches the search string
    //
    // Run a simple string comparison to determine if the suffix at the
    // index begins/equals the search_string
    //
    // Runs with complexity O(P logN), where P is the length of the search string
    //    and N is the length of the original_text
    int binary_search(string search_string);

    //
    // Note: case-sensitive
    bool search_exact(string& search_string);

    //
    // Note: case-sensitive
    vector<int> find_all_exact(string& search_string);

    //
    // Note: case-sensitive
    bool search_inexact(string& search_string, int mismatch_threshold);

    //
    // Note: case-sensitive
    vector<int> find_all_inexact(string& search_string, int mismatch_threshold);

};

/************************************************************/
/****************** Extra Functions **********************/
/************************************************************/

// Used to compare two strings for an "inexact match" of up to compare_len
// characters.
//
// If one/both strings are shorter than the compare_len, returns 0
//
// The threshold specifies the number of characters than be different before
// returning 0
//
// Note: Comparisons are case sensitive threshold must be positive
//
// Important Note: This algorithm requires that the first letter of the
//                 two strings match for an "inexact match" to occur.
bool inexact_compare(const string& str1, const string& str2,
                     int compare_len, int threshold);

// Returns the complement sequence of the inputted string
//  {'a' -> 't', 't' -> 'a', 'c' -> 'g', 'g' -> 'c'}
//
// Input string must only include characters in the set {'a', 'c', 't', 'g'}
//    - Note that the letteres are lowercase
//    - Returns "ERROR" otherwise
string complementizer(const string& str);

// Returns the reverse of the inputted string
string reverser(const string& str);
