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

    string ss = "xanana";
    // cout << my_sa.binary_search()
    cout << my_sa.search_inexact(ss, 1) << endl;

    cout << endl << endl;

    //
    string test_gen = "actg";

    for ( char& t : test_gen ) {
        cout << t << endl;
    }

    return 0;
}
