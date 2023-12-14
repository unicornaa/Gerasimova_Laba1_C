#include "CompressorStation.h"
#include <iostream>
#include <fstream>
#include "utils.h"

int CompressorStation::ID = 0;
void CompressorStation::Reset()
{
	ID = 0;
}

CompressorStation::CompressorStation()
{
	id = ++ID;
	nameCompressorStation = "Unknown";
	numberWorkshop = 1;
	numberWorkshopJob = 0;
	performance = 0;
}

int CompressorStation::getStationID() const
{
	return id;
}

int CompressorStation::getNumberWorkshop() const
{
	return numberWorkshop;
}

std::istream& operator >> (std::istream& in, CompressorStation& station)
{
	cout << "Type name compressor station: ";
	Save(in, station.nameCompressorStation);
	cout << "Type number Workshop: ";
	station.numberWorkshop = CorrectInput(1, 100);
	cout << "Type number Workshop in job: ";
	station.numberWorkshopJob = CorrectInput(0, station.numberWorkshop);
	cout << "Type station performance: ";
	station.performance = CorrectInput(1, 100);
	return in;
}

std::ostream& operator << (std::ostream& out, const CompressorStation& station)
{
	out << "CS\n" << "ID: " << station.id
		<< "\tName: " << station.nameCompressorStation
		<< "\tWorkshops: " << station.numberWorkshop
		<< "\tWorkshops in Job: " << station.numberWorkshopJob
		<< "\tPerformance: " << station.performance << endl;
	return out;
}

void CompressorStation::loadCS(ifstream& fin) {
	if (fin.is_open()) {
		id = ID;
		fin >> ws;
		getline(fin, nameCompressorStation);
		fin >> numberWorkshop;
		fin >> numberWorkshopJob;
		fin >> performance;
	}
}

void CompressorStation::saveCS(ofstream& fout) {
	if (fout.is_open()) {
		fout << "CS" << '\n';
		fout << id << '\n';
		fout << nameCompressorStation << '\n';
		fout << numberWorkshop << '\n';
		fout << numberWorkshopJob << '\n';
		fout << performance << '\n';
	}
}

