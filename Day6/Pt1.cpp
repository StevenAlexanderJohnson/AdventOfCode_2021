#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Class to handle individual fish
class LanturnFish
{
    public:
        int timer;

        LanturnFish()
        {
            this->timer = 8;
        }
        LanturnFish(int initialTimer)
        {
            this->timer = initialTimer;
        }

        // Deincrements the counter and signals when new fish needs to be created
        bool DeincrementTimer()
        {
            this->timer--;
            if(this->timer < 0)
            {
                this->timer = 6;
                return true;
            }
            return false;
        }
};

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "Invalid use, ./Pt1 InputFile.txt NumberOfDays" << endl;
        return 1;
    }

    // Open file
    fstream inputFile;
    inputFile.open(argv[1]);
    if(!inputFile.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    /****************************************
     * DO NOT USE THIS SOLUTION FOR PART 2  *
     * IT WILL USE UP ALL YOUR MEMORY       *
     ***************************************/
    // Create vector of LanturnFish pointers
    vector<LanturnFish*> fishPopulation = vector<LanturnFish*>();
    // Read file
    string fileLine;
    while(getline(inputFile, fileLine))
    {
        // Split line on commas
        string word;
        stringstream words(fileLine);
        while(getline(words, word, ','))
        {
            // Add fish to the vector
            fishPopulation.push_back(new LanturnFish(stoi(word)));
        }
    }

    // Iterate over days
    int numberOfDays = stoi(argv[2]);
    for(int i = 0; i < numberOfDays; i++)
    {
        // Iterate over whole population
        int populationSize = fishPopulation.size();
        for(int i = 0; i < populationSize; i++)
        {
            if(fishPopulation[i]->DeincrementTimer())
            {
                fishPopulation.push_back(new LanturnFish());
            }
        }
    }

    // Print fish population
    cout << fishPopulation.size() << endl;

    // Free memory
    for(LanturnFish* fish : fishPopulation)
    {
        delete fish;
    }
    return 0;
}