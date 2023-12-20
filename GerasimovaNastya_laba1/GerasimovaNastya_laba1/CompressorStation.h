#pragma once
#include <string>
#include <fstream>

class CompressorStation
{
	int id;
	int numberWorkshop;
	double performance;
public:
	static void Reset();
	static int ID;
	CompressorStation();
	int getStationID() const;
	int getNumberWorkshop() const;
	std::string nameCompressorStation;
	int numberWorkshopJob;
	void loadCS(std::ifstream& fin);
	void saveCS(std::ofstream& fout);
	void EditCS();
	void addCS();
	void printCS();


	friend std::istream& operator >> (std::istream& in, CompressorStation& station);
	friend std::ostream& operator << (std::ostream& out, const CompressorStation& station);
};

