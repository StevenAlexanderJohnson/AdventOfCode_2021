#include <vector>
#include <sstream>
#include <iostream>
#include <limits.h>
#include <fstream>

using namespace std;

// Same as Pt1 but now we care about diagonal lines
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

        // Get slope and y-intercept
        void Calculate_Line()
        {
            if(this->x1 != this->x2)
            {
                this->slope = (this->y2 - this->y1)/(this->x2 - this->x1);
            }
            else
            {
                this->slope = INT_MAX;
            }
            this->yIntercept = this->y1 - (this->x1 * this->slope);
        }

        void Add_Line_To_Map(vector<vector<int>> &map)
        {
            // If the x values are the same plot the vertical lines.
            if(this->slope == INT_MAX)
            {
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
            // Else find the starting and ending position, then plot using y = mx + b
            else
            {
                int startX;
                int startY;
                int endX;
                if(this->x1 < this->x2)
                {
                    startX = this->x1;
                    startY = this->y1;
                    endX = this->x2;
                }
                else
                {
                    startX = this->x2;
                    startY = this->y2;
                    endX = this->x1;
                }
                if(startX * this->slope + this->yIntercept != startY)
                {
                    cout << "error with line" << endl;
                    return;
                }
                for(int i = startX; i <= endX; i++)
                {
                    map[i*this->slope+this->yIntercept][i]++;
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

    for(int i = 0 ; i <= largestValue; i++)
    {
        vector<int> tempRow = vector<int>();
        for(int j = 0; j <= largestValue; j++)
        {
            tempRow.push_back(0);
        }
        map.push_back(tempRow);
    }

    for(vector<LineSegment*>::iterator iterator = lineSegments.begin(); iterator != lineSegments.end(); iterator++)
    {
        (*iterator)->Add_Line_To_Map(map);
    }

    int count = 0;
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

    cout << count << endl;
    
    // Free the line segments that you created.
    for(LineSegment* lineSeg : lineSegments)
    {
        delete lineSeg;
    }
}