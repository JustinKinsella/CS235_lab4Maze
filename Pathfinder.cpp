#include "Pathfinder.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;


Pathfinder::Pathfinder()
{
	srand(time(NULL));
	//initialize the maze to be all 1's
	// i = depth j = north/south(rows) k = east/west(columns)
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				currentMaze[k][j][i] = "1";
			}
		}
	}

}


Pathfinder::~Pathfinder()
{
}

string Pathfinder::toString() const
{
	ostringstream output;

	for (int i = 0; i < 5; i++)
	{

		for (int j = 0; j < 5; j++)
		{

			for (int k = 0; k < 5; k++)
			{

				if (k < 4) 
				{
					output << currentMaze[k][j][i] << " ";
				}
				else 
				{
					output << currentMaze[k][j][i];
				}

			}

			output << endl;
			
		}

		output << endl;

	}

	return output.str();
}

void Pathfinder::createRandomMaze()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				int input = rand() % 2;
				
				if (input == 1) 
				{
					currentMaze[k][j][i] = "1";
				}
				else
				{
					currentMaze[k][j][i] = "0";
				}
				
			}
		}
	}
	currentMaze[0][0][0] = "1";
	currentMaze[4][4][4] = "1";
}

bool Pathfinder::importMaze(string file_name)
{
	// It does not matter how you loop or what you use in your arrays as long as you are consistent.

	//*Reads in a maze from a file with the given file nameand stores it as the current maze.
	//* Does nothing if the file does not exist or if the file's data does not represent a valid
	//* maze.
	
//FIXME make a helper function that determines if the maze is valid. 

	vector<string> mazeData = validMaze(file_name);
	if (mazeData.empty()) 
	{
		return false;
	}
	int index = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				currentMaze[k][j][i] = mazeData.at(index);
				index++;
			}
		}
	}

	return true;
}

vector<string> Pathfinder::solveMaze()
{
	;
	//use a helperfunction to make it recursive. 
	//private function vector<string> findPath (what to remember across recursive calls.)  Remeber the PATH ... WHERE YOU HAVE VISTED ... X, Y, Z...
	// call maze{x (x+1) (x-1)} maze {y (y+1) (y-1)} etc. 

	//BASE CASES if you are out side of the maze, if you hit a wall. If x y z has been visited return empty. 
	//helper path could have 6 functions, N/S/W/E pathes as well as UP and DOWN.


	return vector<string>();
}

vector<string> Pathfinder::validMaze(string file_name)
{
	ifstream input;
	input.open(file_name);
	vector<string> mazeData;
	string currentItem;

	while (input >> currentItem)
	{
		if (currentItem == "0" || currentItem == "1")
		{
			mazeData.push_back(currentItem);
		}
		else
		{
			mazeData.clear();
			return mazeData;
		}

	}

	if (mazeData.size() != 125)
	{
		mazeData.clear();
		return mazeData;
	}

	if (mazeData.at(0) != "1" && mazeData.at(125) != "1")
	{
		mazeData.clear();
		return mazeData;
	}

	input.close();

	return mazeData;
}
