#include <fstream>
#include <iostream>

#include "suffix_array.cpp"

using namespace std;

int main ( int argc, char *argv[] ) {
    // Ensure command line has the correct number of arguments
    if ( argc != 2 ) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
    } else {
        // Open the file
        ifstream input_file(argv[1]);

        if ( !input_file.is_open() ) {
            cout << "File " << argv[1] << " could not be opened. Exiting" << endl;
            return 0;
        } else {
            cout << "Building Suffix_Array" << endl;

            // Read in file contents to a string
            string input_str( (istreambuf_iterator<char>(input_file)),
                              istreambuf_iterator<char>() );

            // Convert string to char[]
            char input_char_array[input_str.length()];
            strcpy(input_char_array, input_str.c_str());

            // Remove last letter
            int len = strlen(input_char_array);
            if( input_char_array[len-1] == '\n' )
                input_char_array[len-1] = 0;

            // Build the Suffix Array
            Suffix_Array sa( input_char_array );

            cout << sa.get_orig_text() << endl;
            sa.print_suffix_array();
            sa.print_lcp();
        }

        input_file.close();
    }

    return 1;
}
