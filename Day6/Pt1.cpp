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

        LanturnFish()
        {
            this->timer = 8;
        }
        LanturnFish(int initialTimer)
        {
            this->timer = initialTimer;
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
    string fileLine;
    while(getline(inputFile, fileLine))
    {
        string word;
        stringstream words(fileLine);
        while(getline(words, word, ','))
        {
            fishPopulation.push_back(new LanturnFish(stoi(word)));
        }
    }

    int numberOfDays = stoi(argv[2]);
    for(int i = 0; i < numberOfDays; i++)
    {
        int populationSize = fishPopulation.size();
        for(int i = 0; i < populationSize; i++)
        {
            if(fishPopulation[i]->DeincrementTimer())
            {
                fishPopulation.push_back(new LanturnFish());
            }
        }
    }

    cout << fishPopulation.size() << endl;

    // Free memory
    for(LanturnFish* fish : fishPopulation)
    {
        delete fish;
    }
    return 0;
}