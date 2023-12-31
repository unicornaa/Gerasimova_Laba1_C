#pragma once
#include "utils.h"
#include <fstream>
#include <unordered_map>
#include "PipeLine.h"
#include "CompressorStation.h"
#include <vector>

class netWork
{
	unordered_map<int, PipeLine> pipes;
	unordered_map<int, CompressorStation> stations;
public:
	unordered_map<int, CompressorStation> getCS();
	unordered_map<int, PipeLine> getPipe();
	void addPipe();
	void addCS();
	void printAllObj();
	void editPipe(int id);
	void editCS(int id);
	void loadFromFile(ifstream& fin);
	void saveToFile(ofstream& fout);
	void deletePipe(int index);
	void deleteCS(int index);
};