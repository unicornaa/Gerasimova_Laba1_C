#include "PipeLine.h"
#include <iostream>
#include <fstream>
#include "utils.h"

int PipeLine::ID = 0;

void PipeLine::Reset()
{
    ID = 0;
}

PipeLine::PipeLine()
{
    id = ++ID;
    namePipe = "Unknown";
    length = 0.1;
    diameter = 500;
    InRepairs = 0;
}

int PipeLine::getPipeID() const
{
    return id;
}

void PipeLine::loadPipe(ifstream& fin) {
    if (fin.is_open()) {
        id = ID;
        //fin >> ws;
        getline(fin, namePipe);
        fin >> length;
        fin >> diameter;
        fin >> InRepairs;
    }
}


void PipeLine::savePipe(ofstream& fout) {
    if (fout.is_open()) {
        fout << "PIPE" << '\n';
        fout << id << '\n';
        fout << namePipe << '\n';
        fout << length << '\n';
        fout << diameter << '\n';
        fout << InRepairs << '\n';
    }
}

std::istream& operator >> (std::istream& in, PipeLine& pipe)
{
    std::cout << "Type name pipe: ";
    Save(in, pipe.namePipe);
    std::cout << "Type pipe length: ";
    pipe.length = CorrectInput(0.0, 2000.0);
    std::cout << "Type pipe diameter: ";
    pipe.diameter = CorrectInput(0.0, 2000.0);
    std::cout << "Pipe under repair? ";
    pipe.InRepairs = CorrectInput(0, 1);
    return in;
}

std::ostream& operator << (std::ostream& out, const PipeLine& pipe)
{
    out << "Pipe\n" << "ID: " << pipe.id
        << "\tName: " << pipe.namePipe
        << "\tLength: " << pipe.length
        << "\tDiameter: " << pipe.diameter
        << "\tIn Repairs: " << pipe.InRepairs;
    return out;
}

