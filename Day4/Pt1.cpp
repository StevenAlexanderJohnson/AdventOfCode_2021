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
            int i = 0, j = 0;
            // Find number in board
            for(i; i < this->board.size(); i++)
            {
                for(j; j < this->board[i].size(); j++)
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
                // Have to reset the j iterator manually;
                j = 0;
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
    // If file name was not passed as parameter throw error.
    if(argc != 2) 
    {
        cout << "Invalid use, ./Pt1 Input.txt" << endl;
        return 1;
    }

    // Open file
    fstream inputFile;
    inputFile.open(argv[1], ios::in);
    // If file cannot be opened throw error
    if(!inputFile.is_open())
    {
        cout << "Error opening input file." << endl;
        return 1;
    }
    
    // Read the file
    string line;
    // String to hold the bingo numbers
    string bingoNumbers = "";
    // Vector to hold bingo boards
    vector<BingoBoard*> boardList = vector<BingoBoard*>();
    // Temp board vector to initialize bingo board
    vector<vector<int>> tempBoard = vector<vector<int>>();
    // Temp used vector to initialize bingo board
    vector<vector<bool>> tempUsed = vector<vector<bool>>();
    BingoBoard *board;
    while(getline(inputFile, line))
    {
        // Input file should end with a space on a new line to denote end of file.
        // If on new line handle here
        if(line == "" || line == "\n" || line == " ")
        {
            // This is hit right after reading the bingo numbers, signals the start of building the boards
            if(tempBoard.size() == 0)
            {
                continue;
            }
            // Add the board to the board list
            boardList.push_back(new BingoBoard(tempBoard, tempUsed));
            // Reset the temp boards
            tempBoard = vector<vector<int>>();
            tempUsed = vector<vector<bool>>();
            continue;
        }
        // If the numbers had not been read yet assign the variable
        else if(bingoNumbers.empty())
        {
            bingoNumbers = line;
            continue;
        }
        // Create string stream with the line
        stringstream ss(line);
        // Variable to read the word into
        string word;
        // Initialize the vectors to be added to temp vectors
        vector<int> insertVector = vector<int>();
        vector<bool> usedVector = vector<bool>();
        // Split the line on spaces and read
        while(getline(ss, word, ' '))
        {
            // Occurs if you added an extra space before a single digit number.
            // It will read number after continue.
            if(word == "")
            {
                continue;
            }
            // Insert board number into vector and add a false to the used vector.
            insertVector.push_back(stoi(word));
            usedVector.push_back(false);
        }
        // Add vectors to the temp board vectors
        tempBoard.push_back(insertVector);
        tempUsed.push_back(usedVector);
    }

    // Create string stream with the bingo numbers
    stringstream ss(bingoNumbers);
    // String to read into
    string bingoNumber;
    // Keep a pointer of the current board
    BingoBoard *winningBoard = NULL;
    // Used to break out of nested loops
    bool breakValue = false;
    // Keep track of number that was used to win
    int winningNumber = -1;
    // Read bingo numbers after splitting on delimiter
    while(getline(ss, bingoNumber, ','))
    {
        for(BingoBoard *board : boardList)
        {
            // Keep track of current board and number
            winningBoard = board;
            winningNumber = stoi(bingoNumber);
            // Call number for each board and see if it won
            if(board->Call_Number(winningNumber))
            {
                breakValue = true;
                break;
            }
        }
        // Break out of outer loop
        if(breakValue == true)
        {
            break;
        }
    }

    // Return answer
    cout << winningNumber * winningBoard->Sum_Numbers() << endl;
    
    // Free the bingo boards from memory
    for(BingoBoard *board : boardList)
    {
        delete board;
    }

    return 0;
}