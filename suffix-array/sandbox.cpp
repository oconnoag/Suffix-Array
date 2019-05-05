#include <iostream>
#include <map>
#include <algorithm>
#include "suffix_array.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello World" << endl;

    // char naner[] = "banana";
    char naner[] = "banana";
    Suffix_Array my_sa(naner);

    string ss = "ana";
    // cout << my_sa.binary_search()
    // cout << my_sa.search_inexact(ss, 1) << endl;

    vector<int> naner_found = my_sa.find_all_inexact(ss, 1);
    // vector<int> naner_found = my_sa.find_all_exact(ss);

    cout << "Found: " << endl;
    for (auto& founders : naner_found) {
        cout << "f: " << founders << endl;
    }

    cout << "test " << (int)'a' << endl;


    cout << endl << endl;

    my_sa.print_suffixes();

    string test_str;
    cout << "enter string" << endl;
    getline(cin, test_str);

    for (int i=0; i <= test_str.length(); i++) {
        cout << (int) test_str[i] << endl;
    }
    cout << test_str << endl;
    /////////////////////////////////////////////////////////////////
    ////////////////////// gens ////////////////////////////
    /////////////////////////////////////////////////////////////////

    // cout << reverser("cccccttttttagggcctgctgctgctgctgctg") << endl;
    // cout << reverser("tcgtcgtcg") << endl;
    //
    // char gen_str[] = "cccccttttttagggcctgctgctgctgctgctg";
    // Suffix_Array genetic(gen_str);
    //
    // string search_string = "gctgctgct";
    // vector<int> found = genetic.find_all_inexact(search_string, 2);
    //
    // cout << "found:" << endl;
    // for ( auto& founder : found ) {
    //     cout << founder << endl;
    // }



    return 0;
}
