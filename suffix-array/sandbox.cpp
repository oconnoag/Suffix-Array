#include <iostream>
#include <algorithm>
#include "suffix_array.cpp"

using namespace std;

void test_fxn(char* char_array) {
    cout << sizeof(char_array) << endl;
}

int main(int argc, char* argv[]) {
    cout << "Hello World" << endl;

    char naner[] = "banana";
    Suffix_Array my_sa(naner);
    cout << my_sa.get_num_suffixes() << endl;

    // Testing - Delete this
    string test = "these are words";
    cout << (char) test[1] << endl;

    char tester[] = "these are words";
    cout << &tester << " " << &tester[1] << endl;
    char* t0 = tester;
    char* t1 = tester + 1;

    cout << t0 << " " << t1 << endl;

    Suffix suffixes[10];
    for (int i=0; i < 10; i++) {
        suffixes[i].suffix = tester + i;
        suffixes[i].index = i;
    }

    cout << endl << "Before sort" << endl;
    for ( const auto& suffix : suffixes ) {
        cout << suffix.suffix << endl;
    }

    // IntroSort
    sort(begin(suffixes), end(suffixes));

    cout << endl << "After sort" << endl;
    for ( const auto& suffix : suffixes ) {
        cout << suffix.suffix << endl;
    }

    // int test_len = test.length();
    //
    // Suffix suffixes[test_len];
    //
    // for (int i=0; i < test_len; i++) {
    //     suffixes[i] = &test[i];
    // }




    return 0;
}
