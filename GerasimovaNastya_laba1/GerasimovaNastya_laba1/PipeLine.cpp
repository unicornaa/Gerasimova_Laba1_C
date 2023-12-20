#include "PipeLine.h"
#include <iostream>
#include <fstream>
#include "utils.h"

int PipeLine::ID = 1;

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
    id = ID;
    cout << "Enter name Pipe:";
    cin >> ws;
    getline(cin, namePipe);
    cerr << namePipe << endl;
    cout << "Enter the length of the pipe:";
    length = inputT(0.2);
    cout << "Enter the diameter of the pipe:";
    diameter = inputT(1);
    while (1) {
        if (!checkPipeDiam(diameter)) {
            diameter = inputT(1);
        }
        else break;
    }
    cout << "Enter 1 if the pipe is under repair otherwise 0:";
    InRepairs = inputT(true);
}

void PipeLine::printPipe()
{
    if (namePipe == "") cout << "Input or load data to print" << endl;
    else {
        cout << "id: " << id << endl;
        cout << "name Pipe: " << namePipe << endl;
        cout << "length: " << length << endl;
        cout << "diametr: " << diameter << endl;
        cout << "Inrepair: " << InRepairs << endl;
    }
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
//редактирование трубы
void PipeLine::EditPipe() {
    InRepairs = !(InRepairs);
}


