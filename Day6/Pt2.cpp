#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class LanturnFish
{
    public:
        int timer;
        unsigned long fishCount;

        LanturnFish(int initialTimer)
        {
            this->timer = initialTimer;
            this->fishCount = 0;
        }
        LanturnFish(int initialTimer, unsigned long initialFishCount)
        {
            this->timer = initialTimer;
            this->fishCount = initialFishCount;
        }

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

    fstream inputFile;
    inputFile.open(argv[1]);
    if(!inputFile.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    vector<LanturnFish*> fishPopulation = vector<LanturnFish*>();
    // Change the '8' value to whatever day offset you want for reproduction
    for(int i = 0; i < 7; i++)
    {
        fishPopulation.push_back(new LanturnFish(i));
    }
    string fileLine;
    while(getline(inputFile, fileLine))
    {
        string word;
        stringstream words(fileLine);
        while(getline(words, word, ','))
        {
            fishPopulation[stoi(word)]->fishCount++;
        }
    }

    // Number of days to iterate to
    int numberOfDays = stoi(argv[2]);
    // New fish population that is spawned
    vector<LanturnFish> fishSpawn = vector<LanturnFish>();
    // Loop over days
    for(int i = 0; i < numberOfDays; i++)
    {
        // Holds value of new fish
        unsigned long newFishPopulation = 0;
        // Loop over the fish population
        for(size_t i = 0; i < fishPopulation.size(); i++)
        {
            // If the fish population spawned more fish add their value to the temp holder
            if(fishPopulation[i]->DeincrementTimer() && fishPopulation[i]->fishCount != 0)
            {
                newFishPopulation += fishPopulation[i]->fishCount;
            }
        }
        // If there are new fish populations
        if(fishSpawn.size() != 0)
        {
            // Loop over the new fish population and deincrement their timers
            for(vector<LanturnFish>::iterator fish = fishSpawn.begin(); fish != fishSpawn.end(); fish++)
            {
                fish->DeincrementTimer();
            }
            // The lowest timer will always be the first one
            // If the first timer is 6
            if(fishSpawn[0].timer == 6)
            {
                // Find population with 6 days before reproduction and add the fish count
                for(size_t i = 0; i < fishPopulation.size(); i++)
                {
                    if(fishPopulation[i]->timer == 6)
                    {
                        fishPopulation[i]->fishCount += fishSpawn[0].fishCount;
                        fishSpawn.erase(fishSpawn.begin());
                        break;
                    }
                }
            }
        }
        if(newFishPopulation != 0)
        {
            fishSpawn.push_back(LanturnFish(8, newFishPopulation));
        }
    }

    unsigned long output = 0;
    for(size_t i = 0; i < fishPopulation.size(); i++)
    {
        output += fishPopulation[i]->fishCount;
    }
    for(size_t i = 0; i < fishSpawn.size(); i++)
    {
        output += fishSpawn[i].fishCount;
    }
    cout << output << endl;

    // Free memory
    for(LanturnFish* fish : fishPopulation)
    {
        delete fish;
    }
    return 0;
}