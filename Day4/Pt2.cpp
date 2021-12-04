#include <vector>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Object to hold the bingo board and do operations
class BingoBoard
{
    private:
        vector<vector<int>> board;
        vector<vector<bool>> used;

    public:
        // Constructor consisting of actual bingo boards and a board saying of that number has been called
        BingoBoard(vector<vector<int>> boardInput, vector<vector<bool>> usedInput)
        {
            this->board = boardInput;
            this->used = usedInput;
        }
        
        // Mark the number as called.
        bool Call_Number(int number)
        {
            // Used to break out of the nested loop
            bool breakValue = false;
            // Define the iterators here so that we can use them after
            // the loops are done.
            size_t i, j;
            // Find number in board
            for(i = 0; i < this->board.size(); i++)
            {
                for(j = 0; j < this->board[i].size(); j++)
                {
                    if(board[i][j] == number)
                    {
                        this->used[i][j] = true;
                        breakValue = true;
                        break;
                    }
                }
                if(breakValue)
                {
                    break;
                }
            }
            // Don't check for bingo if number not found
            if(!breakValue)
            {
                return false;
            }
            // Return if the board resulted in bingo.
            return CheckBingo(i, j);
        }

        // Check for bingo
        bool CheckBingo(int i, int j)
        {
            bool bingo = true;
            // Check the column of the number we just marked
            for(bool k : this->used[i])
            {
                // We only need one false for it not to be bingo
                if(k == false)
                {
                    bingo = false;
                    break;
                }
            }
            // If the row had a bingo return true.
            if(bingo)
            {
                return bingo;
            }

            // Reset the bingo variable
            bingo = true;
            // Check the column for bingo
            for(size_t k = 0; k < this->used.size(); k++)
            {
                if(used[k][j] == false)
                {
                    bingo = false;
                    break;
                }
            }
            // Return true or false
            return bingo;
        }
        
        // Sum all the numbers that were not called as requested by prompt.
        int Sum_Numbers()
        {
            int total = 0;
            for(size_t i = 0; i < this->board.size(); i++)
            {
                for(size_t j = 0; j < this->board.size(); j++)
                {
                    if(!used[i][j])
                    {
                        total += board[i][j];
                    }
                }
            }
            return total;
        }
};

int main(int argc, char** argv)
{
    // Throw error if file name was not passed
    if(argc != 2) 
    {
        cout << "Invalid use, ./Pt2 Input.txt" << endl;
        return 1;
    }

    // Open input file
    fstream inputFile;
    inputFile.open(argv[1], ios::in);
    // throw error if file was not opened
    if(!inputFile.is_open())
    {
        cout << "Error opening input file." << endl;
        return 1;
    }
    

    // Read file
    string line;
    // String to hold the bingo calls
    string bingoNumbers = "";
    // Vector to hold bingo boards
    // All of this is the same as pt1, read comments there
    vector<BingoBoard*> boardList = vector<BingoBoard*>();
    vector<vector<int>> tempBoard = vector<vector<int>>();
    vector<vector<bool>> tempUsed = vector<vector<bool>>();
    while(getline(inputFile, line))
    {
        if(line == "" || line == "\n" || line == " ")
        {
            if(tempBoard.size() == 0)
            {
                continue;
            }
            boardList.push_back(new BingoBoard(tempBoard, tempUsed));
            tempBoard = vector<vector<int>>();
            tempUsed = vector<vector<bool>>();
            continue;
        }
        else if(bingoNumbers.empty())
        {
            bingoNumbers = line;
            continue;
        }
        stringstream ss(line);
        string word;
        vector<int> insertVector = vector<int>();
        vector<bool> usedVector = vector<bool>();
        while(getline(ss, word, ' '))
        {
            if(word == "")
            {
                continue;
            }
            insertVector.push_back(stoi(word));
            usedVector.push_back(false);
        }
        tempBoard.push_back(insertVector);
        tempUsed.push_back(usedVector);
    }

    // Still the same I'll tell you when it's different
    stringstream ss(bingoNumbers);
    string bingoNumber;
    BingoBoard *winningBoard = NULL;
    bool breakValue = false;
    int winningNumber = -1;
    while(getline(ss, bingoNumber, ','))
    {
        // Still the same, I just used iterators instead of foreach
        for(vector<BingoBoard*>::iterator begin = boardList.begin(); begin != boardList.end(); begin++)
        {
            winningNumber = stoi(bingoNumber);
            if((*begin)->Call_Number(winningNumber))
            {
                // Once you got to the last board with bingo break from both loops
                if(boardList.size() == 1)
                {
                    breakValue = true;
                    break;
                }
                // Ok different here. If the board won, free it from memory and erase it from the list.
                delete *begin;
                boardList.erase(begin);
                // Move iterator back one
                begin--;
            }
            winningBoard = *begin;
        }
        if(breakValue == true)
        { 
            break; 
        }
    }

    // Return answer
    cout << winningNumber * winningBoard->Sum_Numbers() << endl;
    
    // Free the bingo board memory
    for(BingoBoard *board : boardList)
    {
        delete board;
    }

    return 0;
}