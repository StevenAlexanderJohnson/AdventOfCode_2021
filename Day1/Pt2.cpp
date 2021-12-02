#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv) 
{
    // Check if file name was passed with the call.
    if(argc != 2)
    {
        cout << "Invalid use, ./Pt1 'FileName'" << endl;
    }
    // Open the input file.
    fstream inputFile;
    inputFile.open(argv[1], ios::in);
    // Check that the file was successfully opened.
    if(!inputFile.is_open())
    {
        cout << "Unable to open file." << endl;
    }
    // Create variables to hold the data.
    string line;
    int current, previous, counter = 0;
    int window[3];
    int index, sum = 0;
    // Read the file line by line.
    while(getline(inputFile, line))
    {
        current = stoi(line);
        window[index] = current;
        // Makes sure that the window is initialized before calculation.
        if(index < 2)
        {
            index++;
            continue;
        }
        // Sum the values in the window
        sum = 0;
        for(int i = 0; i < 3; i++)
        {
            sum += window[i];
        }
        // If the sum is greater than the previous sum increment the counter.
        if(sum > previous && previous != 0)
        {
            counter++;
        }
        // Assign the previous to work for next iteration and increment the index.
        previous = sum;
        index = (index + 1) % 3;
    }
    inputFile.close();
    // Print the answer.
    cout << counter << endl;

    return 0;
}