#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

// Node structure to be used in the stack
class Node
{
    public:
        int value;
        int rowIndex;
        int columnIndex;
        Node *next;

        // Constructor
        Node(int valueInput, int rowInput, int columnInput)
        {
            this->value = valueInput;
            this->next = nullptr;
            this->rowIndex = rowInput;
            this->columnIndex = columnInput;
        }
};

class Stack
{
    public:
        Node *head;

        Stack()
        {
            this->head = nullptr;
        }

        // Create a new node and assign it to the end of the stack
        void Push_Front(int value, int rowIndex, int columnIndex)
        {
            // Create a new node
            Node *newNode = new Node(value, rowIndex, columnIndex);
            // If the stack is empty make the both pointers point to the new node
            if(this->head == nullptr)
            {
                this->head = newNode;
            }
            // Else make new node point to current head, then make head point to new node
            else
            {
                // Make it point to the head of the stack
                newNode->next = this->head;
                this->head = newNode;
            }
        }
        
        // Returns if the stack is empty
        bool Is_Empty()
        {
            if(this->head == nullptr)
            {
                return true;
            }
            return false;
        }

        Node* Pop_Front()
        {
            // Get address to the head
            Node *temp = this->head;
            // Make the head point to the next value
            this->head = temp->next;
            // Return the node's value
            return temp;
        }

        // Free the memory being used by the stack.
        void Free_Stack()
        {
            Node *head = this->head;
            Node *temp = nullptr;
            while(head != nullptr)
            {
                // Get address to the head
                temp = head;
                // Point head to next node in stack
                head = head->next;
                // Free memory of previous head
                delete temp;
            }
        }
};



int Depth_First_Search(vector<vector<int>> &grid, vector<vector<bool>> &pathChecked, int i, int j)
{
    // Stack is not stored in the heap as it only contains one pointer, there is no need
    Stack stack = Stack();
    // Push a new node to the front of the stack
    stack.Push_Front(grid[i][j], i, j);
    // Set the current position check to true
    pathChecked[i][j] = true;
    // Temp node value used in the while loop
    Node *temp;

    // Continue to loop until the stack is empty or local min is found
    while(!stack.Is_Empty())
    {
        // Get the first value
        temp = stack.Pop_Front();
        // Check the value to the left if it has been checked then if it is less than or equal to the current value
        if(temp->columnIndex-1 >= 0 && grid[temp->rowIndex][temp->columnIndex -1] <= temp->value)
        {
            // If connected to a checked path you already found the local min
            if(pathChecked[temp->rowIndex][temp->columnIndex -1])
            {
                delete temp;
                stack.Free_Stack();
                // Mark as been search
                pathChecked[temp->rowIndex][temp->columnIndex -1] = true;
                // Return invalid value for check later
                return -1;
            }
            // Add the value to the left to stack
            stack.Push_Front(grid[temp->rowIndex][temp->columnIndex -1], temp->rowIndex, temp->columnIndex -1);
            // Mark as been search
            pathChecked[temp->rowIndex][temp->columnIndex -1] = true;
        }
        // Dito for the right value
        else if(temp->columnIndex+1 < grid[temp->rowIndex].size() && grid[temp->rowIndex][temp->columnIndex +1] <= temp->value)
        {
            if(pathChecked[temp->rowIndex][temp->columnIndex +1])
            {
                delete temp;
                stack.Free_Stack();
                pathChecked[temp->rowIndex][temp->columnIndex +1] = true;
                return -1;
            }
            stack.Push_Front(grid[temp->rowIndex][temp->columnIndex +1], temp->rowIndex, temp->columnIndex +1);
            pathChecked[temp->rowIndex][temp->columnIndex +1] = true;
        }
        // Dito for the value above
        else if(temp->rowIndex-1 >= 0 && grid[temp->rowIndex - 1][temp->columnIndex] <= temp->value)
        {
            if(pathChecked[temp->rowIndex - 1][temp->columnIndex])
            {
                delete temp;
                stack.Free_Stack();
                pathChecked[temp->rowIndex - 1][temp->columnIndex] = true;
                return -1;
            }
            stack.Push_Front(grid[temp->rowIndex - 1][temp->columnIndex], temp->rowIndex - 1, temp->columnIndex);
            pathChecked[temp->rowIndex - 1][temp->columnIndex] = true;
        }
        // Dito for the value under
        else if(temp->rowIndex+1 < grid.size() && grid[temp->rowIndex + 1][temp->columnIndex] <= temp->value)
        {
            if(pathChecked[temp->rowIndex + 1][temp->columnIndex])
            {
                delete temp;
                stack.Free_Stack();
                pathChecked[temp->rowIndex + 1][temp->columnIndex] = true;
                return -1;
            }
            stack.Push_Front(grid[temp->rowIndex + 1][temp->columnIndex], temp->rowIndex + 1, temp->columnIndex);
            pathChecked[temp->rowIndex + 1][temp->columnIndex] = true;
        }
        // If none of the previous if statements are true than you are in a local minimum
        else
        {
            break;
        }
        delete temp;
    }
    // Get value to return
    int returnValue = temp->value;
    // Free the node outside the stack
    delete temp;
    // Free all the nodes in the stack
    stack.Free_Stack();
    // Return the local min value
    return returnValue;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Invalid use, ./Pt1 InputFile.txt" << endl;
        return 1;
    }

    // Open the input file
    fstream inputFile;
    inputFile.open(argv[1]);
    if(!inputFile.is_open())
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Create a vector for the number grid and a vector to check if a number has alread been checked
    vector<vector<int>> grid = vector<vector<int>>();
    vector<vector<bool>> pathChecked = vector<vector<bool>>();
    // String to be read to
    string line;
    while(getline(inputFile, line))
    {
        // Vectors to be added to the grid and pathChecked vectors
        vector<int> lineValues = vector<int>();
        vector<bool> tempPath = vector<bool>();
        // Read each number from the string
        for(size_t i = 0; i < line.length(); i++)
        {
            lineValues.push_back(line[i] - 48);
            tempPath.push_back(false);
        }
        grid.push_back(lineValues);
        pathChecked.push_back(tempPath);
    }
    
    // List of local minimums
    vector<int> localMinimum = vector<int>();
    // Loop over each value in the grid
    for(size_t i = 0; i < pathChecked.size(); i++)
    {
        for(size_t j = 0; j < pathChecked[i].size(); j++)
        {
            // If the value has already been checked continue
            if(pathChecked[i][j] == true)
            {
                continue;
            }
            // Else start a depth first search at that value
            int localMinValue = Depth_First_Search(grid, pathChecked, i, j);
            // If it found a new local minimum add it to the list
            if(localMinValue >= 0)
            {
                localMinimum.push_back(localMinValue);
            }
        }
    }

    // Sum the values for the output
    int output = 0;
    for(int i : localMinimum)
    {
        output += 1 + i;
    }
    // Print the output
    cout << output << endl;

    return 0;
}