#pragma once
#include "PathfinderInterface.h"
#include <vector>
#include <string>

using namespace std;

class Pathfinder :
	public PathfinderInterface
{
public:
	Pathfinder();
	~Pathfinder();
	string toString() const;
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
	vector<string> validMaze(string file_name);

private:
	string currentMaze[5][5][5];
};

