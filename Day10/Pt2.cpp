#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

class Node
{
	public:
		char value;
		Node *next;

		Node(char valueInput)
		{
			this->value = valueInput;
			this->next = nullptr;
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
			this->tail = nullptr;
		}
		
		void Push_Front(char value)
		{
			// Create new node
			Node *temp = new Node(value);
			// If the queue is empty
			if(this->head == nullptr)
			{
				this->head = temp;
				this->tail = temp;
			}
			// Else make the tail node and queue tail pointer point to the new node
			else
			{
				temp->next = this->head;
				this->head = temp;
			}
		}
		
		char Pop_Front()
		{
			Node *temp = this->head;
			char returnValue = temp->value;
			// Assign head to the next value
			this->head = temp->next;
			// If head is null then you reached the end of the list
			if(this->head == nullptr)
			{
				this->tail == nullptr;
			}
			// Free the memory used for the node
			delete temp;
			// Return the return value
			return returnValue;
		}
		
		// Use this before Pop_Front to avoid segmentation faults
		bool Is_Empty()
		{
			// the head will be null when you reach the end of the list
			if(this->head == nullptr)
			{
				return true;
			}
			return false;
		}
		
		// Free all the nodes in the queue
		void Free_Memory()
		{
			Node *temp;
			while(this->head != nullptr)
			{
				temp = this->head;
				this->head = temp->next;
				delete temp;
			}
			
			// Reset the head and tail pointers to nullptr in case they still have values
			this->head = nullptr;
			this->tail = nullptr;
			return;
		}
};

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Invalid use, ./Pt1 InputFile.txt" << endl;
		return 1;
	}

	fstream inputFile;
	inputFile.open(argv[1]);
	if(!inputFile.is_open())
	{
		cout << "Error opening input file." << endl;
	}

	Stack stack = Stack();
	string line;
	bool breakValue = false;
	vector<unsigned long> outputValues = vector<unsigned long>();
	while(getline(inputFile, line))
	{
		breakValue = false;
		char stackValue;
		for(char c : line)
		{
			switch (c)
			{
				// For all opening values push to stack
				case '[':
				case '{':
				case '<':
				case '(':
					stack.Push_Front(c);
					break;
				// Handle each closer the same except add different values for found opener
				case ']':
					stackValue = stack.Pop_Front();
					if(stackValue != '[')
					{
						breakValue = true;
						stack.Free_Memory();
					}
					break;
				case '}':
					stackValue = stack.Pop_Front();
					if(stackValue != '{')
					{
						breakValue = true;
						stack.Free_Memory();
					}
					break;
				case '>':
					stackValue = stack.Pop_Front();
					if(stackValue != '<')
					{
						breakValue = true;
						stack.Free_Memory();
					}
					break;
				case ')':
					stackValue = stack.Pop_Front();
					if(stackValue != '(')
					{
						breakValue = true;
						stack.Free_Memory();
					}
					break;
			}
			if(breakValue)
			{
				break;
			}
		}
		if(breakValue)
		{
			continue;
		}
		unsigned long output = 0;
		while(!stack.Is_Empty())
		{
			char value = stack.Pop_Front();
			output *= 5;
			switch(value)
			{
				case '(':
					output += 1;
					break;
				case '[':
					output += 2;
					break;
				case '{':
					output += 3;
					break;
				case '<':
					output += 4;
					break;
			}
		}
		if(outputValues.size() == 0)
		{
			outputValues.push_back(output);
			continue;
		}
		bool added = false;
		for(vector<unsigned long>::iterator start = outputValues.begin(); start != outputValues.end(); start++)
		{
			if((*start) >= output)
			{
				outputValues.insert(start, output);
				added = true;
				break;
			}
		}
		if(!added)
		{
			outputValues.push_back(output);
		}
	}
	
	for(unsigned long i : outputValues)
	{
		cout << i << endl;
	}
	
	cout << endl << outputValues[outputValues.size()/2] << endl;
	// If the stack still has values free them
	if(!stack.Is_Empty())
	{
		stack.Free_Memory();
	}
	return 0;
}
