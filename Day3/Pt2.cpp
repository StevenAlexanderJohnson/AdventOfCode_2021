#include <vector>
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

// Count the bits from the passed vector
void Count_Bits(vector<string> bitStrings, int *oneCount, int *zeroCount, int bitStringSize)
{
    // Reset the bit counts
    for(int i = 0; i < bitStringSize; i++)
    {
        oneCount[i] = 0;
        zeroCount[i] = 0;
    }
    // Loop over each string and count its bits
    for(int j = 0; j < bitStringSize; j++)
    {
        for(size_t i = 0; i < bitStrings.size(); i++)
        {
            switch (bitStrings[i][j])
            {
                case '1':
                    oneCount[j]++;
                    break;
                case '0':
                    zeroCount[j]++;
                    break;
                default:
                    cout << "Error counting bits." << endl;
                    return;
            }
        }
    }
    return;
}

int main(int argc, char** argv)
{
    // Declare invalid use if necessary.
    if(argc != 3)
    {
        cout << "Invalid use, ./Pt2 InputFile BitStringLength" << endl;
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
    vector<string> bitStrings = vector<string>();
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
            // Add bit strings to vector to be used later.
        }
        bitStrings.push_back(line);
    }

    // Vectors to keep track of valid options for both oxygen and co2
    vector<string> validOxygen = vector<string>();
    vector<string> validCO2 = vector<string>();
    
    // Initialize the valid options for both
    bool testCondition = oneCount[0] >= zeroCount[0];
    for(auto bitString : bitStrings)
    {
        if((bitString[0]=='1') == testCondition)
        {
            validOxygen.push_back(bitString);
        }
        else
        {
            validCO2.push_back(bitString);
        }
    }
    
    // Loop over the valid options and remove those who do not meet the criteria
    while(validOxygen.size() != 1)
    {
        // Loop over every bit
        for(int i = 1; i < bitStringSize; i++)
        {
            // Get most common bits for oxygen
            Count_Bits(validOxygen, oneCount, zeroCount, bitStringSize);
            // Loop over every bit string
            for(size_t j = 0; j < validOxygen.size(); j++)
            {
                // If there is only one left break
                if(validOxygen.size() == 1)
                {
                    break;
                }
                if((validOxygen[j][i] == '1') != (oneCount[i] >= zeroCount[i]))
                {
                    validOxygen.erase(validOxygen.begin() + j);
                    j--;
                }
            }
            if(validOxygen.size() == 1)
            {
                break;
            }
        }
    }
    while(validCO2.size() != 1)
    {
        // Loop over every bit
        for(int i = 1; i < bitStringSize; i++)
        {
            // Get most common bits for co2
            Count_Bits(validCO2, oneCount, zeroCount, bitStringSize);
            // Loop over every bit string
            for(size_t j = 0; j < validCO2.size(); j++)
            {
                if(validCO2.size() == 1)
                {
                    break;
                }
                if((validCO2[j][i] == '1') == (oneCount[i] >= zeroCount[i]))
                {
                    validCO2.erase(validCO2.begin() + j);
                    j--;
                }
            }
            if(validCO2.size() == 1)
            {
                break;
            }
        }
    }
    // Convert the bit strings to decimal
    unsigned int oxygenRating;
    unsigned int co2Rating;
    for(int i = bitStringSize-1; i > -1; i--)
    {
        if(validOxygen[0][i] == '1') 
        {
            oxygenRating += Square_And_Multiply(2, (bitStringSize-1)-i);
        }
        if(validCO2[0][i] == '1')
        {
            co2Rating += Square_And_Multiply(2, (bitStringSize-1)-i);
        }
    }
    // Return answer
    cout << oxygenRating * co2Rating << endl;
    return 0;
}