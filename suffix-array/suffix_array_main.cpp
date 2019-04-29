#include <iostream>
#include "suffix_array.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello World" << endl;

    Suffix_Array my_sa("banana");

    cout << my_sa.get_num_suffixes() << endl;

    return 0;
}
