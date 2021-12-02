#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv) 
{
    // Check if file name was passed in command line
    if(argc != 2)
    {
        cout << "Invalid use, ./Pt1 'FileName'" << endl;
    }
    // Open in put file
    fstream inputFile;
    inputFile.open(argv[1], ios::in);
    // Create variables to hold values;
    string line;
    int current, previous, counter = 0;
    // Read file
    while(getline(inputFile, line))
    {
        current = stoi(line);
        // If the current number is greater than the previous increment.
        if(current > previous && previous != 0)
        {
            counter++;
        }
        previous = current;
    }
    // Print answer
    cout << counter << endl;
}