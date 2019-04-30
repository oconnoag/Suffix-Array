#include <iostream>
#include <algorithm>
#include "suffix_array.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello World" << endl;

    char naner[] = "banana";
    Suffix_Array my_sa(naner);
    int num_suffixes = my_sa.get_num_suffixes();
    my_sa.print_suffix_array();
    my_sa.print_lcp();

    // for (int i=0; i < num_suffixes; i++) {
    //     cout << my_sa.get_lcp()[i] << endl;
    // }
    //
    // cout << endl;
    //
    // for (int i=0; i < num_suffixes; i++) {
    //     cout << my_sa.get_index_array()[i] << endl;
    // }


    return 0;
}
