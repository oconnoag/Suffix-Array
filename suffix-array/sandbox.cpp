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

    vector<int> test = {1,3};

    for (auto& tester : test) {
        cout << tester << endl;
    }

    string searcher = "nana";
    vector<int> found = my_sa.find_all_exact(searcher);

    for ( auto& founder: found ) {
        cout << "Found: " << founder << endl;
    }

    return 0;
}
