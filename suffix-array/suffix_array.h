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

    // Builds the lcp for the canonical banana string for testing purposes
    int* test_lcp_builder();

    // Builds the lcp array using the Kasai algorithm
    // In short:  this algorithm uses the built suffix array to
    // walk along the suffixes one by one while keeping track of the
    // longest prefixes -- when the next suffix is being traversed however,
    // the counter is not reset to 0, so certain comparisons are skipped.
    //
    // This yields a complexity of O(n)
    //
    // Source:  Kasai, T., Lee, G., Arimura, H., Arikawa, S., & Park, K. (2001, July). Linear-time longest-common-prefix computation in suffix arrays and its applications. In Annual Symposium on Combinatorial Pattern Matching (pp. 181-192). Springer, Berlin, Heidelberg.
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

    // Prints all of the suffixes from the original text in sorted order
    // with all of the suffix array indicies and the lcp values
    void print_suffixes();

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

    // Searches for a single exact match of the search string within
    // the original text.
    //
    // Complexity: O(P logN) + O(p)
    //   - First O: Binary Search,
    //   - Second O: string.compare
    //
    // Note: case-sensitive
    bool search_exact(string& search_string);

    // Find all of the locations of the matching search_strings within
    // the original text.
    //
    // This is done by binary searching for the location of the first
    // instance of the search_string in the original_text. Then,
    // iterate down the suffix array.  If the lcp for the i+1th suffix
    // is greater than or equal to the length of the search string, then
    // there is another exact match and that location is pushed to the
    // match vector.
    //
    // Complexity: O(P logN) + O(p) + O(1)
    //   - First O: Binary Search,
    //   - Second O: string.compare
    //   - third O: get lcp and compare
    //
    // Note: case-sensitive
    vector<int> find_all_exact(string& search_string);

    // Searches for a single inexact match (with a given mismatch threshold)
    // of the search string within the original text.
    //
    // Complexity: O(P logN) + O(p)
    //   - First O: Binary Search,
    //   - Second O: string.inexact_compare
    //
    // Note: case-sensitive
    bool search_inexact(string& search_string, int mismatch_threshold);

    // Find all of the locations of the "inexact" matching search_strings within
    // the original text based on the mismatch_threshold.
    //
    // This process differs from the exact find all algorithmically.  Because
    // it is possible that inexact matches can skip over certain suffixes,
    // it is very challenging to actually find all of the these matches.
    // In fact, only substrings that start with the same letter as the
    // search_string can actually be found.  A shortcoming of the procedure
    // but still an effective one in practice.
    //
    // Start by finding the first suffix that starts with the same letter
    // as the suffix string.  Then iterate down the suffix array until all of
    // the suffixes that start with that first letter have been parsed.
    // There are two scenarios for a comparison.
    //  1) If the previous suffix was an inexact match, and the i+1th suffix
    //     has an lcp greater than or equal to the search_string, then that
    //     suffix is also a match.
    //  2) If the previous suffix was not an inexact match, then we use
    //     the inexact_comparison function to determine if the i+1th suffix
    //     is a match
    //
    // Complexity: O(P logN) + O(p) + O(1)
    //   - First O: Binary Search,
    //   - Second O: inexact comparison (higher constant than the exact search,
    //               since there are likely going to be many of these going on)
    //   - third O: get lcp and compare
    //
    // Note: case-sensitive
    vector<int> find_all_inexact(string& search_string, int mismatch_threshold);

    // Wrapper function that brings all of the functionality to the search
    // function of the Suffix Array (inexact or exact).
    //
    // Users can specify to search for an (in)exact match of the complemented
    // and/or reversed search_string
    //
    // Note: case-sensitive
    bool special_search(string search_string,
                        bool exact=true, int mismatch_threshold=0,
                        bool complement=false, bool reverse=false);

    // Wrapper function that brings all of the functionality to the find_all
    // function of the Suffix Array (inexact or exact).
    //
    // Users can specify to search for all (in)exact matches of the complemented
    // and/or reversed search_string
    //
    // Note: case-sensitive
    vector<int> special_find_all(string search_string,
                                 bool exact=true, int mismatch_threshold=0,
                                 bool complement=false, bool reverse=false);

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
