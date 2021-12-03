#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Square and multiply algorithm for fast exponentiation
unsigned int Square_And_Multiply(int base, int exponent)
{
    // Convert the exponent to a binary string.
    string binary = "";
    while(exponent > 0)
    {
        binary += to_string(exponent % 2);
        exponent /= 2;
    }
    // Output variable
    unsigned int z = 1;
    // Traverse the binary string backward.
    for(int i = binary.length()-1; i >= 0; i--)
    {
        z = z * z;
        if(binary[i] == '1')
        {
            z = z * base;
        }
    }
    return z;
}

int main(int argc, char** argv)
{
    // Declare invalid use if necessary.
    if(argc != 3)
    {
        cout << "Invalid use, ./Pt1 InputFile BitStringLength" << endl;
        return 1;
    }

    // Open input file
    fstream inputFile;
    inputFile.open(argv[1], ios::in);
    // Notify if error occured when opening the file.
    if(!inputFile.is_open())
    {
        cout << "Input file could not be opened." << endl;
        return 1;
    }

    // Declare arrays and initialize them to zero.
    int bitStringSize = stoi(argv[2]);
    int zeroCount[bitStringSize], oneCount[bitStringSize];
    for(int i = 0; i < bitStringSize; i++)
    {
        zeroCount[i] = 0;
        oneCount[i] = 0;
    }

    // Read input file
    string line;
    while(getline(inputFile, line))
    {
        // Increment the bit counters accordingly
        for(int i = 0; i < bitStringSize; i++)
        {
            switch (line[i])
            {
                case '0':
                    zeroCount[i]++;
                    break;
                case '1':
                    oneCount[i]++;
                    break;
                default:
                    cout << "Error in switch statement." << endl;
                    return 1;
            }
        }
    }
    // Variables derived from the bits
    unsigned int gamma = 0;
    unsigned int epsilon = 0;
    // Convert bit string into decimal
    for(int i = bitStringSize-1; i > -1; i--)
    {
        if(oneCount[i] > zeroCount[i]) 
        {
            gamma += Square_And_Multiply(2, (bitStringSize-1)-i);
        }
    }
    // Bitwise and epsilon with bit string of all 1 to invert.
    epsilon = gamma ^ (Square_And_Multiply(2, bitStringSize)-1);
    // Print answer
    cout << gamma * epsilon << endl;
    return 0;
}