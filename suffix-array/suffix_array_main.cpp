#include <iostream>
#include "suffix_array.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello World" << endl;

    Suffix_Array my_sa("banana");
    cout << my_sa.get_num_suffixes() << endl;

    // Testing - Delete this
    string test = "these are words";

    Suffix suffixes[test.length()];

    for (int i=0; i < test.length(); i++) {

    }


    return 0;
}
