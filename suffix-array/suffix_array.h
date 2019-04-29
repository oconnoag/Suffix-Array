#include <string>
#include <vector>

using namespace std;

struct Suffix {
    char* suffix;
    int   index;
};

class Suffix_Array {
private:
/************************************************************/
/*************** Attributes ****************/
/************************************************************/
    string   orig_text;
    int      orig_text_length;
    int*     index_array;
    int      num_suffixes;
    int*     lcp; // Longest common prefix

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
    int* skew_builder(char* input_text);

    // Builds the lcp for the canonical banana string for testing purposes
    int* test_lcp_builder();

    // TODO
    int* lcp_builder();

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
    // Returns the portion of the original text that is of a specified length
    string get_substring(int index, int substring_len) const;

    // Prints the a substring of a particular length to the standard output
    // stream
    void print_substring(int index, int substring_len) const;

    //
    // Note: case-sensitive
    bool search_exact(string search_string);

    //
    // Note: case-sensitive
    vector<int> find_all_exact(string search_string);

    //
    // Note: case-sensitive
    bool search_inexact(string search_string, int mismatch_threshold);

    //
    // Note: case-sensitive
    vector<int> find_all_inexact(string search_string, int mismatch_threshold);

};
