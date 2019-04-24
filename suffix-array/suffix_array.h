#include <string>

using namespace std;

struct suffix_array {
    string original_text;
    int* index_array;

};

suffix_array* init_suffix_array();
