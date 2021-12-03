#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cout << "Invalid use, ./Pt1 'Input file name'." << endl;
    }

    fstream inputFile;
    inputFile.open(argv[1]);
    if(!inputFile.is_open())
    {
        cout << "Unable to open the input file." << endl;
        return 1;
    }
    string line;
    int depth = 0, horizontal = 0;
    int counter = 0;
    string instruction;
    int magnitude = 0;
    while(getline(inputFile, line))
    {
        stringstream ss(line);
        string word;
        while(getline(ss, word, ' '))
        {
            switch (counter)
            {
                case 0:
                    instruction = word;
                    break;
                case 1:
                    magnitude = stoi(word);
                    break;
                default:
                    cout << "Error in the switch statement." << endl;
                    return 1;
            }
            counter = (counter + 1) % 2;
        }
        if(instruction == "forward")
        {
            horizontal += magnitude;
        }
        else if(instruction == "down")
        {
            depth += magnitude;
        }
        else if(instruction == "up") 
        {
            depth -= magnitude;
        }
    }
    cout << horizontal * depth << endl;
    return 0;
}