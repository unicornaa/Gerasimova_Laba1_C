#include "PipeLine.h"
#include <iostream>
#include <fstream>
#include "utils.h"

int PipeLine::PipeID = 1;

int PipeLine::getPipeID() const
{
    return id;
}

void PipeLine::Reset()
{
    PipeID = 0;
}

PipeLine::PipeLine()
{
    id = 0;
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
    id = PipeID;
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

        id = PipeID;
        fin >> ws;
        getline(fin, namePipe);
        fin >> length;
        fin >> diameter;
        fin >> InRepairs;
    
}


void PipeLine::savePipe(ofstream& fout) {
    if (fout.is_open()) {
        fout << "\nPIPE\n";
        //fout << id << '\n';
        fout << namePipe << endl;
        fout << length << endl;
        fout << diameter << endl;
        fout << InRepairs;
    }
}

//std::istream& operator >> (std::istream& in, PipeLine& pipe)
//{
//    std::cout << "Type name pipe: ";
//    Save(in, pipe.namePipe);
//    std::cout << "Type pipe length: ";
//    pipe.length = CorrectInput(0.0, 2000.0);
//    std::cout << "Type pipe diameter: ";
//    pipe.diameter = CorrectInput(0.0, 2000.0);
//    std::cout << "Pipe under repair? ";
//    pipe.InRepairs = CorrectInput(0, 1);
//    return in;
//}
//
//std::ostream& operator << (std::ostream& out, const PipeLine& pipe)
//{
//    out << "Pipe\n" << "ID: " << pipe.id
//        << "\tName: " << pipe.namePipe
//        << "\tLength: " << pipe.length
//        << "\tDiameter: " << pipe.diameter
//        << "\tIn Repairs: " << pipe.InRepairs;
//    return out;
//}
//редактирование трубы
void PipeLine::EditPipe() {
    InRepairs = !(InRepairs);
}


