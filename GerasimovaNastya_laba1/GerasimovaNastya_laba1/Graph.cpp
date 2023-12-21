#include "Graph.h"
#include "CompressorStation.h"
#include "PipeLine.h"
#include <iostream>
#include <fstream>

using namespace std;
int edge::maxIdG = 0;

void edge::addEdge(int end, int begin, PipeLine& pipe)
{
    id = maxIdG;
    IDExit = end;
    IDEntry = begin;
    ID = pipe.getPipeID();
    diameter = pipe.getDiameter();
    maxIdG++;
}

void edge::printEdge()
{
    cout << "\nEdge" << endl;
    cout << "ID: " << id << endl;
    cout << "IDEntry: " << IDEntry << endl;
    cout << "IDExit: " << IDExit << endl;
    cout << "Pipe ID: " << ID << endl;
    cout << "diameter: " << diameter << endl;
}

void edge::saveEdge(ofstream& fout) {
    if (fout.is_open()) {
        fout << IDEntry << endl << IDExit
            << endl << ID << endl << diameter;
    }

}
void edge::loadEdge(ifstream& fin) {
    id = maxIdG;
    fin >> IDEntry;
    fin >> IDExit;
    fin >> ID;
    fin >> diameter;
}