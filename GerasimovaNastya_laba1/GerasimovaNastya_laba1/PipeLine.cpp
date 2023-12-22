#include "PipeLine.h"
#include <iostream>
#include <fstream>
#include "utils.h"

int PipeLine::PipeID = 0;

int PipeLine::getPipeID()
{
    return id;
}

void PipeLine::Reset()
{
    PipeID = 0;
}

PipeLine::PipeLine()
{
    this->id = PipeID++;
    namePipe = "Unknown";
    length = 0.1;
    diameter = 0;
    InRepairs = 0;
}


int PipeLine::getDiameter() const
{
    return diameter;
}

bool checkPipeDiam(int diam) {
    switch (diam) {
    case 500: {
        return 1;
    }
    case 700: {
        return 1;
    }
    case 1000: {
        return 1;
    }
    case 1400: {
        return 1;
    }
    default:
        cout << "Invalid diameter\n Try again: ";
        return 0;
    }
}

void PipeLine::addPipe()
{
    cout << "Type name pipe: ";
    cin >> ws;
    getline(cin, namePipe);
    cerr << namePipe << endl;
    cout << "Type pipe length: ";
    length = inputT(0.2);
    cout << "Type pipe diameter: ";
    diameter = inputT(1);
    while (1) {
        if (!checkPipeDiam(diameter)) {
            diameter = inputT(1);
        }
        else break;
    }
    cout << "Pipe under repair? ";
    InRepairs = inputT(true);
}

void PipeLine::printPipe()
{
    if (namePipe == "") cout << "Input or load data to print" << endl;
    else {
        cout << "ID: " << id << endl;
        cout << "Name Pipe: " << namePipe << endl;
        cout << "Length: " << length << endl;
        cout << "Diameter: " << diameter << endl;
        cout << "In repair: " << InRepairs << endl;
    }
}

void PipeLine::loadPipe(ifstream& fin) {
        fin >> ws;
        getline(fin, namePipe);
        fin >> length;
        fin >> diameter;
        fin >> InRepairs;

}


void PipeLine::savePipe(ofstream& fout) {
    if (fout.is_open()) {
        fout << "\nPIPE" << '\n';
        fout << namePipe << '\n';
        fout << length << '\n';
        fout << diameter << '\n';
        fout << InRepairs;
    }
}

//редактирование трубы
void PipeLine::EditPipe() {
    InRepairs = !(InRepairs);
}


