#include <iostream>
#include <fstream>
#include <string>
#include "TextQuery.h"
#include "QueryResult.h"

using std::cout; using std::cin; using std::endl;
using std::ifstream; using std::ofstream;
using std::string;

void runQueries(ifstream& infile) {
    // infile is an ifstream that is the file we want to query
    TextQuery tq(infile);   // store the file and build the query map
    // iterate with the user: prompt for a word to find and print results
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        // stop if we hit end-of-file on the input or if a 'q' is entered
        if (!(cin >> s) || s == "q")
            break;
        // run the query and print the results
        print(cout, tq.query(s)) << endl;
    }
}

int main()
{
    ifstream infile("hello.txt");

    runQueries(infile);

    cin.get();
}

