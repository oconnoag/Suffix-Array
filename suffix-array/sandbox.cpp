#include <iostream>
#include <algorithm>
#include "suffix_array.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello World" << endl;

    char naner[] = "banana";
    Suffix_Array my_sa(naner);
    cout << my_sa.get_num_suffixes() << endl;

    cout << endl;

    for (int i=0; i < my_sa.get_num_suffixes(); i++) {
        cout << my_sa.get_lcp()[i] << endl;
    }
    return 0;
}
