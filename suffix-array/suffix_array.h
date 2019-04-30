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

    // Performs the binary search for the
    bool search_exact_recursive(string& search_string, int l, int r);

public:

/************************************************************/
/*************** Constructors & Destructors ****************/
/************************************************************/
    Suffix_Array(char* input_text);
    ~Suffix_Array();

/************************************************************/
/*************** Getters ****************/
/************************************************************/
    string get_orig_text() const;
    int get_orig_text_length() const;
    int get_num_suffixes() const;
    int *get_index_array() const;
    int *get_lcp() const;

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
