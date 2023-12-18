#include "Graph.h"
#include "CompressorStation.h"
#include "PipeLine.h"
#include <iostream>
#include <fstream>

using namespace std;
int edge::maxIdG = 1;

void edge::addEdge(int begin, int end, PipeLine& pipe)
{
    id = maxIdG;
    IDExit = begin;
    IDEntry = end;
    ID = pipe.getPipeID();
    diameter = pipe.getDiameter();
    maxIdG++;
}

void edge::printEdge()
{
    cout << "\nEdge" << endl;
    cout << "ID: " << id << endl;
    cout << "IDExit: " << IDExit << endl;
    cout << "IDEntry: " << IDEntry << endl;
    cout << "Pipe ID: " << ID << endl;
    cout << "diameter: " << diameter << endl;
}

void edge::saveEdge(ofstream& fout) {
    if (fout.is_open()) {
        fout << IDExit << endl << IDEntry
            << endl << ID << endl << diameter;
    }

}
void edge::loadEdge(ifstream& fin) {
    id = maxIdG;
    fin >> IDExit;
    fin >> IDEntry;
    fin >> ID;
    fin >> diameter;
}