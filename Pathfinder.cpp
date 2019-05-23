#include "Pathfinder.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <set>

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
	vector<string> solvablePath;
	set<string> visited;
	//use a helperfunction to make it recursive. 
	//private function vector<string> findPath (what to remember across recursive calls.)  Remeber the PATH ... WHERE YOU HAVE VISTED ... X, Y, Z...
	// call maze{x (x+1) (x-1)} maze {y (y+1) (y-1)} etc. 

	//BASE CASES if you are out side of the maze, if you hit a wall. If x y z has been visited return empty. 
	//helper path could have 6 functions, N/S/W/E pathes as well as UP and DOWN.
	path.clear();
	findPath(visited, 0, 0, 0);
	


	return path;
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

	if ((mazeData.at(0) != "1"))
	{
		mazeData.clear();
		return mazeData;
	}
	if(mazeData.at(124) != "1")
	{
	mazeData.clear();
	return mazeData;
	}

	input.close();

	return mazeData;
}

bool Pathfinder::findPath(set<string>& visited, int depth, int row, int column)
{
	ostringstream currentLocation;
	currentLocation << "(" << column << ", " << row << ", " << depth << ")";
	string here = currentLocation.str();
	path.push_back(here);

	if (depth > 4 || row > 4 || column > 4 || depth < 0 || row < 0 || column < 0)
	{
		path.pop_back();
		return false;
	}

	if (visited.count(here) == 1)
	{
		path.pop_back();
		return false;
	}
	else
	{
		visited.insert(here);
	}

	if (currentMaze[column][row][depth] == "0")
	{
		path.pop_back();
		return false;
	}

	if (depth == 4 && row == 4 && column == 4)
	{
		return true;
	}

	if (
		(findPath(visited, depth - 1, row, column)) ||
		(findPath(visited, depth + 1, row, column)) ||
		(findPath(visited, depth, row - 1, column)) ||
		(findPath(visited, depth, row + 1, column)) ||
		(findPath(visited, depth, row, column - 1)) ||
		(findPath(visited, depth, row, column + 1)))
	{
		return true;
	}
	else
	{
		path.pop_back();
		return false;
	}
}
