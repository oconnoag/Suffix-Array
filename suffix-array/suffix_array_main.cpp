#include <fstream>
#include <iostream>
#include <limits> // for stream processing

// Used for "sleeping"
#include <chrono>
#include <thread>

#include "suffix_array.cpp"

using namespace std;

int int_choice_preprocessing( int lowest, int highest );
char yn_choice_preprocessing();
void process(int choice, Suffix_Array& sa);

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

            // Processing
            while (true) {
                cout << endl;
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "What would you like to do? (Type number of action) " << endl;
                cout << "\t" << "(1) See Suffix Array" << endl;
                cout << "\t" << "(2) Search for a substring" << endl;
                cout << "\t" << "(3) Find all locations of a substring" << endl;
                cout << "\t" << "(4) Exit" << endl;
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "Note, if you know your sequence you can just type all options separated by a space" << endl;
                cout << "Ex: '2 y y y' => Search for a reversed complemented version of the search string" << endl;
                cout << "Ex: '3 n 1 n n' => Find all inexact locations of the search_string" << endl;
                cout << "---------------------------------------------------------------------------" << endl;
                cout << endl;

                int choice = int_choice_preprocessing(1, 4);
                process(choice, sa);

                // Continue Searching?
                char cont;
                cout << "\nDo you want to continue? (y/n)" << endl;
                cont = yn_choice_preprocessing();

                if ( cont == 'n' ) {
                    break;
                }

            }

            // Close File
            cout << "Exiting . . . " << endl;
            input_file.close();
        }

    }
return 1;
}

// Handles getting the choice (int) input from the terminal -- including
// validation
int int_choice_preprocessing(int lowest, int highest) {
    // Process Requests
    int choice;
    cin >> choice;

    while (true) {
        if ( cin.fail() || choice < lowest || choice > highest ) {
            // Clear the error message
            cin.clear();
            // Discard the rest of the input string
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number {1,2,3...}." << endl;

            // Try again input
            cin >> choice;
        } else {
            return choice;
        }

    }
}

// Handles getting the choice ('y' or 'n') input from the terminal -- including
// validation
char yn_choice_preprocessing() {
    // Process Requests
    char choice;
    cin >> choice;

    while (true) {
        if ( cin.fail() || !(choice == 'y' || choice == 'n') ) {
            // Clear the error message
            cin.clear();
            // Discard the rest of the input string
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Enter 'y' for yes or 'n' for no." << endl;

            // Try again input
            cin >> choice;
        } else {
            return choice;
        }

    }
}

// Performs the action associated with the inputted choice
void process(int choice, Suffix_Array& sa) {

    if ( choice == 1 ) {
        sa.print_suffixes();
    } else if ( choice == 4 ) {
        cout << "Exiting . . . " << endl;
        exit(1);
    } else {
        // Exact Search
        cout << "\nWill this be an exact search? (y/n)" << endl;
        bool exact = (yn_choice_preprocessing() == 'y') ? 1 : 0;

        // Mismatch Threshold
        int mismatch_threshold;
        if ( !exact ) {
            cout << "\nWhat is the mismatch tolerance for the query?" << endl;
            cout << " - How many characters can be mismatched?" << endl;
            mismatch_threshold = int_choice_preprocessing(0, (1<<31) - 1 ); // Highest is the max signed int
        } else {
            mismatch_threshold = 0;
        }

        // Complement
        cout << "\nUse the complement of the inputted string? (y/n) " << flush;
        cout << "  (Note: String must only include characters in the set {a,c,t,g})" << endl;
        bool complement = (yn_choice_preprocessing() == 'y') ? 1 : 0;

        // Reverse
        cout << "\nUse the reverse of the inputted string? (y/n) " << endl;
        bool reverse = (yn_choice_preprocessing() == 'y') ? 1 : 0;

        // Flush the cin buffer and clear any flags
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.clear();

        // Get search string
        cout << "\nPlease enter the string you wish to search for: " << flush;
        cout << "  (Note: Be careful of spaces & accuracy of the string)" << endl;
        string search_string;
        getline(cin, search_string);

        cout << "\n\n--------------------------------------- Searching . . . -------------------------------------------------\n\n";

        // Process search/find_all
        if ( choice == 2 ) {
            // Search
            bool match = sa.special_search(search_string,
                                           exact, mismatch_threshold,
                                           complement, reverse);

            if (match) {
                cout << "'" << search_string << "'" << " has a match using your query criteria:" << endl;
            } else {
                cout << "'" << search_string << "'" << " does not have a match using your query criteria:" << endl;
            }

        } else {
            // Find All
            vector<int> locs = sa.special_find_all(search_string,
                                                   exact, mismatch_threshold,
                                                   complement, reverse);

            if ( !locs.empty() ) {
                cout << "'" << search_string << "'" << " has match(es) at indicies: [ " << flush;
                for ( const auto& loc : locs ) {
                    cout << loc << " " << flush;
                }
                cout << "] using your query criteria:" << endl;
            } else {
                cout << "'" << search_string << "'"<< " does not have any matches using your query criteria:" << endl;
            }

        }

        // Query Criteria
        cout << "{" << endl;
        cout << setw(25) << "Search String: " << search_string << "," << endl;
        cout << setw(25) << "Search Type: " << ((exact) ? "Exact" : "Inexact") << "," << endl;
        cout << setw(25) << "Mismatch Threshold: " << mismatch_threshold << "," << endl;
        cout << setw(25) << "String Complemented: " << ((complement) ? "Yes" : "No") << "," << endl;
        cout << setw(25) << "String Reversed: " << ((reverse) ? "Yes" : "No") << endl;
        cout << "}" << endl;
        cout << endl;

    }

    // Cross-platform way to sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}
