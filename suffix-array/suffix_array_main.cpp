#include <iostream>
#include "suffix_array.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello World" << endl;

    Suffix_Array my_sa("banana");
    cout << my_sa.get_num_suffixes() << endl;

    // Testing - Delete this
    string test = "these are words";
    cout << (char) test[1] << endl;

    char tester[] = "these are words";
    cout << tester << endl;

    // int test_len = test.length();
    //
    // Suffix suffixes[test_len];
    //
    // for (int i=0; i < test_len; i++) {
    //     suffixes[i] = &test[i];
    // }




    return 0;
}
