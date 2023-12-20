#include "CompressorStation.h"
#include <iostream>
#include <fstream>
#include "utils.h"

int CompressorStation::ID = 1;
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

bool checkNumWSinOperation(int checkValue, int numWS) {
	if ((checkValue > numWS) || (checkValue < 0)) return 1;
	else return 0;
}


void CompressorStation::addCS() {
	id = ID;
	cout << "Enter the name of the CS:";
	cin >> ws;
	getline(cin, nameCompressorStation);
	cerr << nameCompressorStation << endl;
	cout << "Enter the number of WS:";
	numberWorkshop = inputT(1);
	cout << "Enter the WS in operation:";
	numberWorkshopJob = inputT(1);

	while (1) {
		if (checkNumWSinOperation(numberWorkshopJob, numberWorkshop)) {
			cout << "Enter a number more than 0 and less than or equal to " << numberWorkshop << ": ";
			numberWorkshopJob = inputT(1);
		}
		else break;
	}
	cout << "Enter efficiency:";
	performance = inputT(0.0);
}
//Âûâîä ÊÑ íà êîíñîëü
void CompressorStation::printCS()
{
	if (nameCompressorStation == "") cout << "Input or load data to print" << endl;
	else {
		cout << "id: " << getStationID() << endl;
		cout << "name: " << nameCompressorStation << endl;
		cout << "number of WS: " << numberWorkshop << endl;
		cout << "WS in operation: " << numberWorkshopJob << endl;
		cout << "efficiency: " << performance << endl;
	}
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

///редактирование станции
void CompressorStation::EditCS() {
	cout << "Type \"1\", if you want to start one workshop,type \"2\" - if you want to stop one workshop: ";
	bool decision = inputT(true);
	if (decision == 1) {
		if (numberWorkshopJob == getNumberWorkshop())
			cout << "all workshops are working" << endl;
		else numberWorkshopJob++;
	}
	else {
		if (numberWorkshopJob == 0) 
			cout << "all workshops are stopped" << endl;
		else numberWorkshopJob--;
	}
}
