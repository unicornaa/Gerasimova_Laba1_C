#pragma once
#include "utils.h"
#include <fstream>
#include <unordered_map>
#include "PipeLine.h"
#include "CompressorStation.h"
#include <unordered_set>

class netWork
{
	unordered_map<int, PipeLine> pipes;
	unordered_map<int, CompressorStation> stations;
public:
	void AddNewPipe(const PipeLine& pipe);
	void AddNewStation(const CompressorStation& station);
	void ShowAllObjects();
	void EditPipeline(int ID);
	void EditStation();
	void SaveData();
	void LoadDate();
	void DeletePipeline(int ID);
	void DeleteStation();
	void ClearPipelines();
	void ClearStations();
	void AddConnection();
	void Disconnection();
	void ShowNetwork();
	int getPipelineID();
	vector<vector<int>> CreateRibs();
	unordered_map<int, int> StepenyVershin();
	unordered_map<int, PipeLine> getPipe();
	unordered_map<int, CompressorStation> getStation();
	void TopologicalSort();
};