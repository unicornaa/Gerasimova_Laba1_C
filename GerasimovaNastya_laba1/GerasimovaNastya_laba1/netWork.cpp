#include "netWork.h"
#include "utils.h"
#include<iostream>

void paddCS(unordered_map<int, CompressorStation>& stations, CompressorStation newCS) {
    stations.insert(pair<int, CompressorStation>(CompressorStation::ID, newCS));
    CompressorStation::ID++;
}
void paddPipe(unordered_map<int, PipeLine>& pipes, PipeLine& newPipe) {
    pipes.insert(pair<int, PipeLine>(PipeLine::ID, newPipe));
    PipeLine::ID++;
}

unordered_map<int, CompressorStation> netWork::getCS()
{
    return unordered_map<int, CompressorStation>(stations);
}

unordered_map<int, PipeLine> netWork::getPipe()
{
    return unordered_map<int, PipeLine>(pipes);
}

void netWork::addPipe()
{
    PipeLine newPipe;
    newPipe.addPipe();
    paddPipe(pipes, newPipe);
}

void netWork::addCS()
{
    CompressorStation newCS;
    newCS.addCS();
    paddCS(stations, newCS);
}

void netWork::printAllObj()
{
    if (pipes.size() == 0) cout << "Input or load pipe to print" << endl;
    for (auto& [key, p] : pipes) {
        cout << "\nPIPE information" << endl;
        p.printPipe();
    }
    if (stations.size() == 0) cout << "Input or load CS to print" << endl;
    for (auto& [key, cs] : stations) {
        cout << "\nCS information" << endl;
        cs.printCS();
    }
}



void netWork::editPipe(vector<int> res)
{
    for (int i = 0; i < res.size(); i++) {
        pipes[res[i]].EditPipe();
    }
}

void netWork::editCS(vector<int> res)
{
    for (int i = 0; i < res.size(); i++) {
        stations[res[i]].EditCS();
    }
}

void netWork::loadFromFile(ifstream& fin)
{
    string marker;
    bool flagP = 0, flagCS = 0;
    pipes.erase(pipes.begin(), pipes.end());
    stations.erase(stations.begin(), stations.end());
    PipeLine::ID = 1;
    CompressorStation::ID = 1;
    if (fin.is_open()) {
        while (!fin.eof() && marker != "G") {
            fin >> marker;
            if (marker == "PIPE") {
                PipeLine newPipe;
                newPipe.loadPipe(fin);
                paddPipe(pipes, newPipe);
                flagP = 1;
            }
            if (marker == "CS") {
                CompressorStation newCS;
                newCS.loadCS(fin);
                paddCS(stations, newCS);
                flagCS = 1;
            }
        }
        if (!flagP) cout << "save the pipe data to a file" << endl;
        if (!flagCS) cout << "save the CS data to a file" << endl;
    }
    else {
        cout << "Error! The file does not exist" << endl;
    }
}

void netWork::saveToFile(ofstream& fout)
{
    if (pipes.size() != 0) {
        for (auto const& pipe : pipes) {
            if (pipes[pipe.first].namePipe != "") {
                pipes[pipe.first].savePipe(fout);
            }
        }
    }
    if (stations.size() != 0) {
        for (auto const& CS : stations) {
            if (stations[CS.first].nameCompressorStation != "") {
                stations[CS.first].saveCS(fout);
            }
        }
    }
}

void netWork::deletePipe(int index)
{
    pipes.erase(index);
}

void netWork::deleteCS(int index)
{
    stations.erase(index);
}