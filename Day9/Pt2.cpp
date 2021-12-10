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
        Node *tail;

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

        void Push_Back(Node *node)
        {
            // If the head is null then the tail is also null
            if(this->head == nullptr)
            {
                this->head = node;
                this->tail = node;
            }
            else
            {
                // Reset the next pointer in case it still holds a value
                node->next = nullptr;
                // Make the tail point to the new node
                this->tail->next = node;
                this->tail = node;
            }
        }
        void Push_Back(int value, int rowIndex, int columnIndex)
        {
            Node *temp = new Node(value, rowIndex, columnIndex);
            if(this->head == nullptr)
            {
                this->head = temp;
                this->tail = temp;
            }
            else
            {
                this->tail->next = temp;
                this->tail = temp;
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
            // If the head is null then you reached the end of the stack
            // set the tail to null as well
            if(temp == nullptr)
            {
                this->tail = nullptr;
                return nullptr;
            }
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

int Breath_First_Search(vector<vector<int>> &grid, vector<vector<bool>> &pathChecked, Node* node)
{
    // Create stack
    Stack stack = Stack();
    // Push the node to the stack
    stack.Push_Back(node);
    pathChecked[node->rowIndex][node->columnIndex] = true;
    // Temp node used for traversal
    Node *temp = nullptr;
    // Int to return the basin size
    int basinCount = 1;
    while(!stack.Is_Empty())
    {
        // Get the first value
        temp = stack.Pop_Front();
        // Check the value to the left if it has been checked then if it is less than or equal to the current value
        if(temp->columnIndex-1 >= 0 && !pathChecked[temp->rowIndex][temp->columnIndex - 1] && grid[temp->rowIndex][temp->columnIndex -1] != 9)
        {
            basinCount++;
            // Add the value to the left to stack
            stack.Push_Back(grid[temp->rowIndex][temp->columnIndex -1], temp->rowIndex, temp->columnIndex -1);
            // Mark as been search
            pathChecked[temp->rowIndex][temp->columnIndex -1] = true;
        }
        // Dito for the right value
        if(temp->columnIndex+1 < grid[temp->rowIndex].size() && !pathChecked[temp->rowIndex][temp->columnIndex +1] && grid[temp->rowIndex][temp->columnIndex +1] != 9)
        {
            basinCount++;
            stack.Push_Back(grid[temp->rowIndex][temp->columnIndex +1], temp->rowIndex, temp->columnIndex +1);
            pathChecked[temp->rowIndex][temp->columnIndex +1] = true;
        }
        // Dito for the value above
        if(temp->rowIndex-1 >= 0 && !pathChecked[temp->rowIndex - 1][temp->columnIndex] && grid[temp->rowIndex - 1][temp->columnIndex] != 9)
        {
            basinCount++;
            stack.Push_Back(grid[temp->rowIndex - 1][temp->columnIndex], temp->rowIndex - 1, temp->columnIndex);
            pathChecked[temp->rowIndex - 1][temp->columnIndex] = true;
        }
        // Dito for the value under
        if(temp->rowIndex+1 < grid.size() && !pathChecked[temp->rowIndex + 1][temp->columnIndex] && grid[temp->rowIndex + 1][temp->columnIndex] != 9)
        {
            basinCount++;
            stack.Push_Back(grid[temp->rowIndex + 1][temp->columnIndex], temp->rowIndex + 1, temp->columnIndex);
            pathChecked[temp->rowIndex + 1][temp->columnIndex] = true;
        }
        // If none of the previous if statements are true than delete the node and continue to the next node;
        delete temp;
        temp = nullptr;
    }
    if(temp != nullptr)
    {
        delete temp;
    }
    // Free all the nodes in the stack
    stack.Free_Stack();
    // Return the local min value
    return basinCount;
}

Node* Depth_First_Search(vector<vector<int>> &grid, vector<vector<bool>> &pathChecked, int i, int j)
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
                stack.Free_Stack();
                // Mark as been search
                pathChecked[temp->rowIndex][temp->columnIndex -1] = true;
                delete temp;
                // Return invalid value for check later
                return nullptr;
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
                stack.Free_Stack();
                pathChecked[temp->rowIndex][temp->columnIndex +1] = true;
                delete temp;
                return nullptr;
            }
            stack.Push_Front(grid[temp->rowIndex][temp->columnIndex +1], temp->rowIndex, temp->columnIndex +1);
            pathChecked[temp->rowIndex][temp->columnIndex +1] = true;
        }
        // Dito for the value above
        else if(temp->rowIndex-1 >= 0 && grid[temp->rowIndex - 1][temp->columnIndex] <= temp->value)
        {
            if(pathChecked[temp->rowIndex - 1][temp->columnIndex])
            {
                stack.Free_Stack();
                pathChecked[temp->rowIndex - 1][temp->columnIndex] = true;
                delete temp;
                return nullptr;
            }
            stack.Push_Front(grid[temp->rowIndex - 1][temp->columnIndex], temp->rowIndex - 1, temp->columnIndex);
            pathChecked[temp->rowIndex - 1][temp->columnIndex] = true;
        }
        // Dito for the value under
        else if(temp->rowIndex+1 < grid.size() && grid[temp->rowIndex + 1][temp->columnIndex] <= temp->value)
        {
            if(pathChecked[temp->rowIndex + 1][temp->columnIndex])
            {
                stack.Free_Stack();
                pathChecked[temp->rowIndex + 1][temp->columnIndex] = true;
                delete temp;
                return nullptr;
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
    // Free all the nodes in the stack
    stack.Free_Stack();
    // Return the local min value
    return temp;
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
    vector<Node*> localMinimum = vector<Node*>();
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
            Node *localMinValue = Depth_First_Search(grid, pathChecked, i, j);
            // If it found a new local minimum add it to the list
            if(localMinValue != nullptr)
            {
                localMinimum.push_back(localMinValue);
            }
        }
    }

    for(size_t i = 0; i < pathChecked.size(); i++)
    {
        for(size_t j = 0; j < pathChecked[i].size(); j++)
        {
            pathChecked[i][j] = false;
        }
    }

    // Holds the largest 3 basins
    vector<int> basins = vector<int>();
    unsigned long basinSize = 1;
    // Node is freed inside Breath_First_Search
    for(Node* node : localMinimum)
    {
        int testing = Breath_First_Search(grid, pathChecked, node);
        // Basins is going to be sorted based on insertion
        // If the vector is empty initialize it
        if(basins.size() == 0)
        {
            basins.push_back(testing);
        }
        // If the testing is smaller than first value then it should be added
        else if(basins[0] < testing)
        {
            // Boolean to see if the value was added in the loop
            bool added = false;
            for(size_t i = 0; i < basins.size(); i++)
            {
                // If you found the value larger than testing insert before
                if(basins[i] > testing)
                {
                    basins.insert(basins.begin() + i, testing);
                    // Set added flag to true
                    added = true;
                    break;
                }
            }
            // If the value wasn't inserted in the loop add to end
            if(!added)
            {
                basins.push_back(testing);
            }
            // If the size is greater than 3 pop the front
            if(basins.size() > 3)
            {
                basins.erase(basins.begin());
            }
        }
    }

    // Multiply the values together for the output
    for(int basin : basins)
    {
        basinSize *= basin;
    }

    // Print the output
    cout << basinSize << endl;

    return 0;
}