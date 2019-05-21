#pragma once
#include "PathfinderInterface.h"
#include <vector>
#include <string>
#include <set>

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
	vector<string> findPath(vector<string> path, set<string>& visted, int depth, int row, int column);
};

