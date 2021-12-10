#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

// Class to handle the line segments
class LineSegment
{
    public:
        int x1;
        int x2;
        int y1;
        int y2;
        int slope;
        int yIntercept;

        LineSegment()
        {
            this->x1 = 0;
            this->x2 = 0;
            this->y1 = 0;
            this->y2 = 0;
            this->slope = 0;
            this->yIntercept = 0;
        }

        void Calculate_Line()
        {
            if(this->x1 != this->x2)
            {
                this->slope = (this->y2 - this->y1)/(this->x2 - this->x1);
            }
            else
            {
                this->slope = -1;
            }
            this->yIntercept = this->y1 - (this->x1 * this->slope);
        }

        // In Part 1 we only care about horizontal and vertical lines
        void Add_Line_To_Map(vector<vector<int>> &map)
        {
            if(this->x1 == this->x2)
            {
                // If the line is vertical, loop over vertical coordinates
                if(this->y1 < this->y2)
                {
                    for(int i = this->y1; i <= this->y2; i++)
                    {
                        map[i][this->x1]++;
                    }
                }
                else
                {
                    for(int i = this->y2; i <= this->y1; i++)
                    {
                        map[i][this->x1]++;
                    }
                }
            }
            // Else if the line is horizontal, loop over x coordinates
            else if(this->y1 == this->y2)
            {
                if(this->x1 < this->x2)
                {
                    for(int i = this->x1; i <= this->x2; i++)
                    {
                        map[this->y1][i]++;
                    }
                }
                else
                {
                    for(int i = this->x2; i <= this->x1; i++)
                    {
                        map[this->y1][i]++;
                    }
                }
            }
        }
};

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cout << "Invalid use, ./Pt1 InputFile.txt" << endl;
        return 1;
    }

    // Open file
    fstream inputFile;
    inputFile.open(argv[1], ios::in);
    if(!inputFile.is_open())
    {
        cout << "Error in opening input file." << endl;
        return 1;
    }

    // Map to hold the values of where the lines are.
    vector<vector<int>> map = vector<vector<int>>();
    // Used to initialize the map later
    int largestValue = 0;
    // Vector of line semgnets, segments need to be freed as well as vector;
    vector<LineSegment*> lineSegments = vector<LineSegment*>();
    string line;
    while(getline(inputFile, line))
    {
        // Pointer to object that will hold the line segment data.
        LineSegment *temp = new LineSegment();
        // String stream that will break the values on spaces
        stringstream breakLine(line);
        // Keeps track on which the line has been split, important for assignment.
        int lineBreakCounter = 0;
        // Keeps track of how many times the coordinate has been broken, needed for assignment.
        int coordinateBreakCounter = 0;

        string coordinatePair;
        while(getline(breakLine, coordinatePair, ' '))
        {
            // This is the middle section '->'
            if(lineBreakCounter == 1)
            {
                lineBreakCounter++;
                continue;
            }
            // Split the coordinate pair on the ','
            stringstream breakCoordinates(coordinatePair);
            string coordinateValue;
            while(getline(breakCoordinates, coordinateValue, ','))
            {
                // Determines where the value should be assigned
                if(coordinateBreakCounter == 0 && lineBreakCounter == 0)
                {
                    temp->x1 = stoi(coordinateValue);
                    if(temp->x1 > largestValue)
                    {
                        largestValue = temp->x1;
                    }
                }
                else if (coordinateBreakCounter == 1 && lineBreakCounter == 0)
                {
                    temp->y1 = stoi(coordinateValue);
                    if(temp->y1 > largestValue)
                    {
                        largestValue = temp->y1;
                    }
                }
                else if (coordinateBreakCounter == 0 && lineBreakCounter == 2)
                {
                    temp->x2 = stoi(coordinateValue);
                    if(temp->x2 > largestValue)
                    {
                        largestValue = temp->x2;
                    }
                }
                else if (coordinateBreakCounter == 1 && lineBreakCounter == 2)
                {
                    temp->y2 = stoi(coordinateValue);
                    temp->Calculate_Line();
                    if(temp->y2 > largestValue)
                    {
                        largestValue = temp->y2;
                    }
                }
                // Increment coordinate break counter keeping value between 0 and 1
                coordinateBreakCounter = (coordinateBreakCounter + 1) % 2;
            }
            // Increment line break counter keeping value between 0 and 2
            lineBreakCounter = (lineBreakCounter + 1) % 3;
        }
        // Add the temp line segment to the vector
        lineSegments.push_back(temp);
        // Create a new line segment
        temp = new LineSegment();
    }

    // Add zeros to the grid the lines will be plotted on
    for(int i = 0 ; i <= largestValue; i++)
    {
        vector<int> tempRow = vector<int>();
        for(int j = 0; j <= largestValue; j++)
        {
            tempRow.push_back(0);
        }
        map.push_back(tempRow);
    }

    // For each line segment, plot it on the map
    for(vector<LineSegment*>::iterator iterator = lineSegments.begin(); iterator != lineSegments.end(); iterator++)
    {
        (*iterator)->Add_Line_To_Map(map);
    }

    int count = 0;
    // Add all the values in the map
    for(vector<int> row : map)
    {
        for(int value : row)
        {
            if(value > 1)
            {
                count++;
            }
        }
    }
    
    // Print the output
    cout << count << endl;

    // Free the line segments that you created.
    for(LineSegment* lineSeg : lineSegments)
    {
        delete lineSeg;
    }
}