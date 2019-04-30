#include "suffix_array.h"
#include <iostream>

using namespace std;

/************************************************************/
/*************** Private Suffix Array Methods ***************/
/************************************************************/

int* Suffix_Array::test_builder() {
    string banana = "banana";
    int* banana_array = new int[banana.length()];
    banana_array[0] = 5;
    banana_array[1] = 3;
    banana_array[2] = 1;
    banana_array[3] = 0;
    banana_array[4] = 4;
    banana_array[5] = 2;

    return banana_array;
}

int* Suffix_Array::test_lcp_builder() {
    string banana =  "banana";
    int* banana_lcp = new int[banana.length()];
    banana_lcp[0] = 0;
    banana_lcp[1] = 1;
    banana_lcp[2] = 3;
    banana_lcp[3] = 0;
    banana_lcp[4] = 0;
    banana_lcp[5] = 2;

    return banana_lcp;
}

int* Suffix_Array::naive_builder(char* input_text) {
    unsigned num_suffixes = this->get_num_suffixes();
    Suffix suffixes[num_suffixes];

    for (unsigned i=0; i < num_suffixes; i++) {

    }
}

/************************************************************/
/*************** Constructors & Destructors ****************/
/************************************************************/
Suffix_Array::Suffix_Array(char* input_text) {
    // Set up attributes
    string input_str(input_text);
    this->orig_text = input_str;
    this->orig_text_length = (unsigned) this->orig_text.length();
    this->num_suffixes = this->orig_text_length;

    // Set up arrays
    this->index_array = this->test_builder();
    this->lcp = this->test_lcp_builder();
}

Suffix_Array::~Suffix_Array() {
    // Free the heap memory for the arrays
    delete this->index_array;
    delete this->lcp;
}

/************************************************************/
/*************** Getters ****************/
/************************************************************/

string Suffix_Array::get_orig_text() const {
    return this->orig_text;
}

unsigned int Suffix_Array::get_num_suffixes() const {
    return this->num_suffixes;
}

unsigned int Suffix_Array::get_orig_text_length() const {
    return this->orig_text_length;
}

int *Suffix_Array::get_index_array() const {
    return this->index_array;
}

int *Suffix_Array::get_lcp() const {
    return this->lcp;
}

/************************************************************/
/*************** Public Suffix Array Methods ****************/
/************************************************************/

string Suffix_Array::get_substring(int index, int substring_len) const {
    if (index < 0 || substring_len < 0) {
        cout << "Usage : index and substring must be positive" << endl;
        return "ERROR";
    }

    return this->orig_text.substr(index, substring_len);
}

void Suffix_Array::print_substring(int index, int substring_len) const {
    string substring;

    if ( (substring = this->get_substring(index, substring_len)) == "ERROR") {
        return;
    }

    cout << "(Index " << index << ") -> " << substring << " <- (Index " << index+substring_len-1 << ")" << endl;
}

bool Suffix_Array::search_exact(string search_string) {
    // TODO
    return 1;
}

vector<int> Suffix_Array::find_all_exact(string search_string) {
    vector<int> matches;

    // TODO

    return matches;
}

bool Suffix_Array::search_inexact(string search_string, int mismatch_threshold) {
    // TODO
    return 1;
}

vector<int> Suffix_Array::find_all_inexact(string search_string, int mismatch_threshold) {
    vector<int> matches;

    // TODO

    return matches;
}
