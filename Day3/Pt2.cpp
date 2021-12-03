#include <vector>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>
using namespace std;


class Tuple 
{
    public:
        int first;
        int second;

        Tuple(int firstValue, int secondValue)
        {
            this->first = firstValue;
            this->second = secondValue;
        }
};

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
    vector<string> validOxygen = vector<string>();
    vector<Tuple> validOxygenBits = vector<Tuple>();
    for(int i = 0; i < bitStringSize; i++)
    {
        validOxygenBits.push_back(Tuple(0, 0));
    }
    vector<string> validCO2 = vector<string>();
    vector<Tuple> validCO2Bits = vector<Tuple>();
    for(int i = 0; i < bitStringSize; i++)
    {
        validCO2Bits.push_back(Tuple(0, 0));
    }
    
    // Check if there are more ones than zeros in the MSB
    bool test = oneCount[0] >= zeroCount[0];
    // Initialize the vectors.
    int index = 0;
    for(auto bitString : bitStrings)
    {
        if((bitString[0]=='1') == test)
        {
            validOxygen.push_back(bitString);
        }
        else
        {
            validCO2.push_back(bitString);
        }
    }
    char mostCommonBit;
    for(int i = 1; i < bitStringSize; i++)
    {
        if(oneCount[i] >= zeroCount[i])
        {
            mostCommonBit = '1';
        }
        else
        {
            mostCommonBit = '0';
        }
        for(int j = 0; j < validOxygen.size(); j++)
        {
            // Break when there is only one left
            if(validOxygen.size() == 1)
            {
                break;
            }
            if(validOxygen[j][i] != mostCommonBit)
            {
                validOxygen.erase(validOxygen.begin() + j);
                j--;
            }
        }
        for(int j = 0; j < validCO2.size(); j++)
        {
            // Break when there is only one left.
            if(validCO2.size() == 1)
            {
                break;
            }
            if(validCO2[j][i] == mostCommonBit)
            {
                validCO2.erase(validCO2.begin() + j);
                j--;
            }
        }
        if(validCO2.size() == 1 && validOxygen.size() == 1)
        {
            break;
        }
    }
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
    cout << oxygenRating * co2Rating << endl;
    return 0;
}