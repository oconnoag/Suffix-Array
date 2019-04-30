#include "suffix_array.h"
#include <iostream>
#include <algorithm>

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
    int num_suffixes = this->get_num_suffixes();
    Suffix suffixes[num_suffixes];

    for (int i=0; i < num_suffixes; i++) {
        suffixes[i].suffix = input_text + i;
        suffixes[i].index = i;
    }

    // Sort using std::sort in the algorithms header files,
    // this is a O(n*log(n)) sorting algorithm called the IntroSort
    // which, from what I understand is built using a combination of
    // of different comparison sorts in a way that guarantees
    // the linearithmic sort time
    //
    // The complexity of this algorithm is actually O(N^2 log(N)) though,
    // because string comparison using strcmp (see the Suffix struct in
    // the suffix_array.h file) is O(N) algorithm
    sort(suffixes, suffixes + num_suffixes);

    int* suffix_array = new int[num_suffixes];

    for (int i=0; i < num_suffixes; i++) {
        suffix_array[i] = suffixes[i].index;
    }

    return suffix_array;
}

int* Suffix_Array::lcp_builder(char* input_text) {
    int num_suffixes = this->get_num_suffixes();

    int* lcp_array = new int[num_suffixes];

    // Inverse Suffix Array
    int* suffix_array = this->get_index_array();
    int inv_sa[num_suffixes];

    // Create the inverse suffix array:
    //   this holds the indicies corresponding to each i
    //
    // Ex: Suffix Array - {(0) 5, (1) 3, (2) 1, (3) 0, (4) 4, (5) 2} - Indicies in ()
    //     Start at 0 -- find the index that is holding 0 -> it's index 3
    //     Then go to 1 -- that's at index 2
    //     Repeat until you've got all the suffixes
    //
    //     Result:
    //     inv_sa - {3, 2, 5, 1, 4, 0}
    //
    //     This reads:
    //      origin2l_text[0] is at index 3 in the suffix array
    //      original_text[1] is at index 2 in the suffix array
    //      ...
    for (int i=0; i < num_suffixes; i++) {
        inv_sa[suffix_array[i]] = i;
    }

    // Build the lcp
    int counter = 0;

    // Go through each prefix one by one
    for (int i=0; i < num_suffixes; i++) {
        int k = inv_sa[i];

        if ( k == 0 ) {
            lcp_array[k] = 0;
            continue;
        }

        int j = suffix_array[k-1];

        while ( input_text[i + counter] == input_text[j + counter] ) {
            counter++;
        }

        // The counter value will indicate the shared prefix between k and k-1
        lcp_array[k] = counter;

        if (counter > 0) {
            counter--;
        }

    }

    return lcp_array;

}

/************************************************************/
/*************** Constructors & Destructors ****************/
/************************************************************/
Suffix_Array::Suffix_Array(char* input_text) {

    // Set up attributes
    string input_str(input_text);
    this->orig_text = input_str;
    this->orig_text_length = this->orig_text.length();

    // If text is too long -- only catches the overflows of
    // unsigned->signed ints, not if the unsigned int overflows
    if (this->orig_text_length < 0 ) {
        // Catch this in main code when constructor called
        // https://www.tutorialspoint.com/cplusplus/cpp_exceptions_handling.htm
        throw "Length of text too long -> overflowed";
    }

    this->num_suffixes = this->orig_text_length;

    /******************* Construct Arrays ****************************/

    this->index_array = naive_builder(input_text);
    this->lcp = lcp_builder(input_text);
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

int Suffix_Array::get_num_suffixes() const {
    return this->num_suffixes;
}

int Suffix_Array::get_orig_text_length() const {
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
void Suffix_Array::print_suffix_array() {
    int* index_array = this->get_index_array();
    int num_suffixes = this->get_num_suffixes();

    for (int i=0; i < num_suffixes; i++) {
        cout << index_array[i] << " " << flush;
    }

    cout << endl;
}

void Suffix_Array::print_lcp() {
    int* lcp = this->get_lcp();
    int num_suffixes = this->get_num_suffixes();

    for (int i=0; i < num_suffixes; i++) {
        cout << lcp[i] << " " << flush;
    }

    cout << endl;
}

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
