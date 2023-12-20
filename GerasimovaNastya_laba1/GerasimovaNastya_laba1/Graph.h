#pragma once
#include <fstream>
#include "PipeLine.h"

using namespace std;

class edge
{
	int id;
public:
	static int maxIdG;
	int IDEntry;
	int IDExit;
	int ID;
	int diameter;
	void addEdge(int begin, int end, PipeLine& pipe);
	void printEdge();
	void saveEdge(ofstream& fout);
	void loadEdge(ifstream& fin);
};