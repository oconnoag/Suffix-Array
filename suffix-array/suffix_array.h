#include <string>

using namespace std;

class Suffix_Array {
private:
/************************************************************/
/*************** Attributes ****************/
/************************************************************/
    string orig_text;
    int* index_array;
    int* lcp; // Longest common prefix

/************************************************************/
/*************** Private Methods ****************/
/************************************************************/

    // Used to build the canonical banana string for testing purposes
    // Stores an int array to heap
    int* test_builder();

    // Builds the suffix array (index_array) for the inputed orig_text
    // using a naive approach with comparison-based sorting O( n^2 log(n) )
    int* naive_builder(string orig_text);


    // int* skew_builder(string orig_text);

    // Builds the lcp for the canonical banana string for testing purposes
    int* test_lcp_builder();


    // int* lcp_builder();

public:

/************************************************************/
/*************** Constructors & Destructors ****************/
/************************************************************/
    Suffix_Array(string orig_text);
    ~Suffix_Array();

/************************************************************/
/*************** Getters ****************/
/************************************************************/
    string get_orig_text() const;
    int get_num_suffixes() const;
    int *get_index_array() const;
    int *get_lcp() const;

/************************************************************/
/*************** Methods ****************/
/************************************************************/
    string get_substring(int index, int substring_len) const;
    void print_substring() const;
};
