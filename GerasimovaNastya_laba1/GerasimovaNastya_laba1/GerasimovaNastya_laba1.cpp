﻿#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "PipeLine.h"
#include "utils.h"
#include <unordered_set>
#include "CompressorStation.h"
#include "Graph.h"
#include "netWork.h"
#include <vector>

using namespace std;

//поиск ID
template <typename type>
bool CheckID(const unordered_map<int, type>& x, const int& id)
{
    return (x.find(id) != x.end());
}

void PrintFoundPipes(const int& id, const unordered_map<int, PipeLine>& pipes) {
    if (pipes.find(id) != pipes.end()) {
        cout << "Pipe ID: " << id << " " << pipes.at(id) << std::endl; // Предполагается, что у PipeLine есть оператор вывода
    }
}
//проверка ID
int CorrectIntID() {
    int id;
    while ((cin >> id).fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type again: ";
    }
    cerr << id << endl;
    return id;
}
//удаление трубы
void DeletePipe(unordered_map<int, PipeLine>& pipes, const int& id) {
    pipes.erase(id);
}

//удаление станции
void DeleteStation(unordered_map<int, CompressorStation>& stations) {
    cout << "Type station ID for delete: ";
    int id;
    id = CorrectIntID();
    if (CheckID(stations, id)) {
        stations.erase(id);
    }
    else {
        cout << "No station with such ID" << endl;
    }
}


 //поиск трубы по фильтру
template <typename type>
using PipelineFilter = bool(*)(const PipeLine& pipe, type param);

template <typename type>
unordered_set<int> FindPipelinesByFilter(const unordered_map<int, PipeLine>& pipes, PipelineFilter<type> f, type param) {
    unordered_set<int> result;
    for (const auto& i : pipes)
    {
        if (f(i.second, param)) {
            result.insert(i.first);
        }
    }
    if (!(size(result))) {
        cout << "No found pipelines " << endl;
    }
    return result;
}


bool CheckByName(const PipeLine& pipe, const string param) {
    return pipe.namePipe.find(param) != string::npos;
}

bool CheckByRepair(const PipeLine& pipe, bool param) {
    return (pipe.InRepairs == param);
}


void FindPipeLine(const unordered_map<int, PipeLine>& pipes) {
    cout << "Type '1' - search by name, '2' - by repair" << endl;
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        string namePipe;
        cout << "Input pileline name for searching: ";
        cin.ignore();
        getline(cin, namePipe);
        for (int id : FindPipelinesByFilter<string>(pipes, CheckByName, namePipe)) {
            cout << pipes.at(id) << endl;
        }
    }
    else if (choice == 2)
    {
        cout << "type pipeline status for searching: ";
        bool flag;
        cin >> flag;
        for (int id : FindPipelinesByFilter<bool>(pipes, CheckByRepair, flag)) {
            cout << pipes.at(id) << endl;
        }
    }
}



// поиск Compressor Station по фильтру
template <typename type>
using StationFilter = bool(*)(const CompressorStation& station, type param);

template <typename type>
unordered_set<int> FindStationsByFilter(const unordered_map<int, CompressorStation>& stations, StationFilter<type> f, type param) {
    unordered_set<int> result;
    for (auto& i : stations) {
        if (f(i.second, param)) {
            result.insert(i.first);
        }
    }
    if (!(size(result))) {
        cout << "No stations found" << endl;
    }
    return result;
}

bool CheckByNameCS(const CompressorStation& station, string param) {
    return (station.nameCompressorStation.find(param) != string::npos);
}

bool CheckByUnworkingWorkshops(const CompressorStation& station, double param) {
    return (double(((station.getNumberWorkshop() - station.numberWorkshopJob) / station.getNumberWorkshop()) * 100)) >= param;
}

void FindCS(const unordered_map<int, CompressorStation>& stations) {
    cout << "Type '1' - search by name, '2' - by repair status NOT IN JOB" << endl;
    int choice;
    std::cin >> choice;

    if (choice == 1)
    {
        string nameCompressorStation;
        cout << "Input CS name for searching: ";
        cin.ignore();
        getline(cin, nameCompressorStation);
        for (int id : FindStationsByFilter<string>(stations, CheckByNameCS, nameCompressorStation)) {
            cout << stations.at(id) << endl;
        }
    }
    else if (choice == 2)
    {
        cout << "Input percent of unworking stations for searching: ";
        double percent;
        cin >> percent;
        for (int id : FindStationsByFilter<double>(stations, CheckByUnworkingWorkshops, percent)) {
            cout << stations.at(id) << endl;
        }
    }
}

template <typename type>
unordered_set<int> FindPipeByFilter(const unordered_map<int, PipeLine>& pipes,  type param) {
    unordered_set<int> result;
    for (auto& i : pipes) {
        if (f(i.second, param)) {
            result.insert(i.first);
        }
    }
    if (!(size(result))) {
        cout << "No stations found" << endl;
    }
    return result;
}

vector<int> findPipebyName(netWork& newNetWork, string name) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getPipe().size(); i++) {
        if (newNetWork.getPipe()[i].namePipe == name)
            res.push_back(i + 1);
    }
    return res;
}
vector<int> findPipeByDiam(netWork& newNetWork, int diam) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getPipe().size() + 1; i++) {
        if (newNetWork.getPipe()[i].getDiameter() == diam)
            res.push_back(i);
    }
    return res;
}
vector<int> findPipebyRepair(netWork& newNetWork, bool repair) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getPipe().size(); i++) {
        if (newNetWork.getPipe()[i].InRepairs == repair)
            res.push_back(i + 1);
    }
    return res;
}
vector<int> findCSbyName(netWork& newNetWork, string name) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getCS().size(); i++) {
        if (newNetWork.getCS()[i].nameCompressorStation == name)
            res.push_back(i + 1);
    }
    return res;
}
vector<int> findCSbyPer(netWork& newNetWork, int per) {
    vector <int> res;
    for (int i = 0; i < newNetWork.getCS().size(); i++) {
        int k = round((100.0 * (newNetWork.getCS()[i].getNumberWorkshop() - newNetWork.getCS()[i].numberWorkshopJob)) / newNetWork.getCS()[i].getNumberWorkshop());
        if (k == per)
            res.push_back(i + 1);
    }
    return res;
}


void editPipeByName(netWork& newNetWork) {

    string nameToSearch;
    cout << "Enter name to search for pipes: ";
    cin >> ws;
    getline(cin, nameToSearch);
    cerr << nameToSearch << endl;
    vector<int> res = findPipebyName(newNetWork, nameToSearch);
    if (res.size() == 0) {
        cout << "There are no pipes with this name.\n";
        return;
    }
    newNetWork.editPipe(res);
}

void editPipeByRepair(netWork& newNetWork) {
    bool state;
    cout << "Enter repair state to search for pipes: ";
    state = inputT(true);
    vector<int> res = findPipebyRepair(newNetWork, state);
    if (res.size() == 0) {
        cout << "There are no pipes with this repair state.\n";
        return;
    }
    newNetWork.editPipe(res);
}

void editCSByName(netWork& newNetWork) {
    cout << "Enter name to search for CS: ";
    string nameToSearch;
    cin >> ws;
    getline(cin, nameToSearch);
    cerr << nameToSearch << endl;
    vector<int> res = findCSbyName(newNetWork, nameToSearch);
    if (res.size() == 0) {
        cout << "There are no CS with this name.\n";
        return;
    }
    newNetWork.editCS(res);
}

void editCSByPer(netWork& newNetWork) {
    cout << "Enter persent to search for pipes: ";
    int per;
    per = inputT(1);
    vector<int> res = findCSbyPer(newNetWork, per);
    if (res.size() == 0) {
        cout << "There are no CS with this percent.\n";
        return;
    }
    newNetWork.editCS(res);
}

void editPipe(netWork& newNetWork) {
    if (newNetWork.getPipe().size() != 0) {

        cout << "Enter 0 to search by name or 1 to search by repair: ";
        bool field = inputT(true);
        if (field == 0) {
            editPipeByName(newNetWork);
        }
        else {
            editPipeByRepair(newNetWork);
        }
    }
    else {
        cout << "Input or load pipe data to edit" << endl;
    }
}

void editCS(netWork& newNetWork) {
    if (newNetWork.getCS().size() != 0) {
        cout << "Enter 0 to search by name or 1 to search by percent: ";
        bool field = inputT(true);
        if (field == 0) {
            editCSByName(newNetWork);
        }
        else {
            editCSByPer(newNetWork);
        }
    }
    else {
        cout << "Input or load CS data to edit" << endl;
    }
}


void PrintMenu() {
    cout << "1. Add Pipe " << endl
        << "2. Add Compressor Station " << endl
        << "3. View all objects " << endl
        << "4. Edit pipe " << endl
        << "5. Edit Compressor Station " << endl
        << "6. Save to file " << endl
        << "7. Load from file " << endl
        << "8. Delete Pipe " << endl
        << "9. Delete Compressor Station " << endl
        << "10. Graph " << endl
        << "11. Topologic sort " << endl
        << "12. Pack editing of pipelines " << endl
        << "0. Exit " << endl
        << "Choose action: ";
}

//Пакетное редактирование трубы
void FindMenu() {
    cout << "1. Find pipelines by name" << endl
        << "2. Find pipelines by repair status" << endl
        << "Enter a number from 1 to 2: ";
}

//void PrintFoundPipes(const int& id, unordered_map<int, PipeLine>& pipes) {
//    cout << pipes[id];
//}

void EditMenu() {
    cout << "1. Select pipelines by ID" << endl
        << "2. Edit all found pipelines" << endl
        << "3. Delete all found pipelines" << endl
        << "4. Show all pipelines" << endl
        << "0. Return to main MENU" << endl << endl
        << "Enter a number from 0 to 4: ";
}

void EditPipeline(unordered_map<int, PipeLine>& pipes, const int& id) {
    pipes[id].InRepairs = !(pipes[id].InRepairs);
}


unordered_set<int> PackEdit(netWork& newNetWork) {
    unordered_set<int> pipesID{};
    FindMenu();
    switch (CorrectInput(1, 2)) {
    case 1: {
        string name;
        cout << "Input pileline name for searching: ";
        Save(cin, name);
        for (int id : FindPipelinesByFilter(newNetWork.getPipe(), CheckByName, name)) {
            cout << newNetWork.getPipe()[id];
            //PrintFoundPipes(id, pipes);
            pipesID.insert(id);
        }
        break;
    }
    case 2: {
        bool flag;
        cout << "Input station status for searching: ";
        flag = CorrectInput(false, true);
        for (int id : FindPipelinesByFilter(newNetWork.getPipe(), CheckByRepair, flag)) {
            cout << newNetWork.getPipe()[id];
            //PrintFoundPipes(id, pipes);
            pipesID.insert(id);
        }
        break;
    }
    }
    return pipesID;
}
unordered_set<int> SelectPipesID(netWork& newNetWork) {
    unordered_set<int> pipesID;
    while (1) {
        cout << "Input ID of pipeline or 0 to complete: ";
        int id;
        id = CorrectIntID();
        if (id) {
            if (CheckID(newNetWork.getPipe(), id)) {
                cout << newNetWork.getPipe()[id];
                pipesID.insert(id);
            }
            else {
                cout << "No pipeline with such ID" << endl;
            }
        }
        else {
            break;
        }
    }
    return pipesID;
}

bool checkPipeD(int diameter) {
    switch (diameter) {
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

int inputValue() {
    int state;
    while (1) {
        if (!(cin >> state)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Try again: ";
        }
        else if (state >= 1 || state == -1) {
            cerr << state << endl;
            return state;
        }
        else cout << "enter value more than 0: ";
    }
    cerr << state << endl;
    return state;
}


//---------------------------ЗАПРОС ВВОДА ПАРАМЕТРОВ ДЛЯ ГРАФА------------------------------//
//void requestForParameters(int& IDEntry, int& IDExit, int& diam, netWork& newNetWork) {
//    while (1) {
//        cout << "Enter the CS entry ID or enter -1 to create a CS: ";
//        IDEntry = inputValue();
//        if (IDEntry == -1)
//        {
//            newNetWork.addCS();
//            IDEntry = newNetWork.getCS()[newNetWork.getCS().rbegin()->first].getStationID();
//        }
//        cout << "Enter the CS exit ID: ";
//        IDExit = inputT(1);
//        if (newNetWork.getCS().contains(IDEntry) && newNetWork.getCS().contains(IDExit) && IDEntry != IDExit)
//            break;
//        cout << "There are no such IDs. Enter another ID\n";
//    }
//    cout << "Enter diametr of pipe: ";
//    diam = inputT(1);
//    while (1) {
//        if (!checkPipeD(diam)) {
//            diam = inputT(1);
//        }
//        else break;
//    }
//}
//топологическая сортировка

void SaveToFile(netWork& newNetWork, unordered_map<int, edge>& graphG) {
    if (newNetWork.getPipe().size() == 0 && newNetWork.getCS().size() == 0) cout << "Input or load data to save" << endl;
    else {
        string FILENAME;
        cout << "Enter name of file to save:";
        cin >> FILENAME;
        cerr << FILENAME << endl;
        ofstream fout(FILENAME);
        newNetWork.saveToFile(fout);
        if (graphG.size() != 0) fout << "G" << endl;
        for (auto const& edge : graphG) {
            graphG[edge.first].saveEdge(fout);
            if (edge.first != graphG.begin()->first)
                fout << endl;
        }
        fout.close();
    }
}


void loadFromFile(netWork& newNetWork, vector<int>& usedPipe, unordered_map<int, edge>& graphG) {
    string FILENAME;
    string marker;
    cout << "Enter name of file to load:";
    cin >> FILENAME;
    cerr << FILENAME << endl;
    ifstream fin(FILENAME);
    edge::maxIdG = 1;
    if (fin.is_open()) {
        newNetWork.loadFromFile(fin);
        edge newEdge;
        while (!fin.eof()) {
            newEdge.loadEdge(fin);
            graphG.insert(pair<int, edge>(edge::maxIdG, newEdge));
            edge::maxIdG++;
        }
        for (auto& [key, edge] : graphG) {
            for (auto& [ind, p] : newNetWork.getPipe()) {
                bool findEdge = (find(usedPipe.begin(), usedPipe.end(), ind) != usedPipe.end());
                if ((edge.diameter == p.getDiameter()) && !findEdge) {
                    edge.ID = ind;
                    usedPipe.push_back(ind);
                    break;
                }
            }
        }
    }
    fin.close();
}

int SelectEdge(unordered_map<int, edge> graphG) {
    cout << "Enter pipe id: ";
    while (1) {
        unsigned int index = inputT(1);
        if (index >= 1 && index < graphG.size()) {
            return index;
        }
        cout << "enter correct number: ";
    }
}

int SelectPipe(netWork& newNetWork) {
    cout << "Enter pipe id: ";
    while (1) {
        unsigned int index = inputT(1);
        for (auto& [key, p] : newNetWork.getPipe()) {
            if (key == index)
                return index;
        }
        cout << "enter correct number: ";
    }
}

int SelectCS(netWork& newNetWork) {
    cout << "Enter CS id: ";
    while (1) {
        unsigned int index = inputT(1);
        for (auto& [key, cs] : newNetWork.getCS())
        {
            if (key == index)
                return index;
        }
        cout << "enter correct number: ";
    }
}
//int inputValue() {
//    int state;
//    while (true) {
//        if (!(cin >> state)) {
//            cin.clear();
//            cin.ignore(1000, '\n');
//            cout << "Try again: ";
//        }
//        else if (state >= 1 || state == -1) {
//            cerr << state << endl;
//            return state;
//        }
//        else cout << "enter value more than 0: ";
//    }
//    cerr << state << endl;
//    return state;
//}

void requestForParameters(int& IDEntry, int& IDExit, int& diameter, netWork& newNetWork) {
    while (1) {
        cout << "Enter the CS entry ID or enter -1 to create a CS: ";
        IDEntry = inputValue();
        if (IDEntry == -1)
        {
            newNetWork.addCS();
            IDEntry = newNetWork.getCS().begin()->second.getStationID();
        }
        cout << "Enter the CS exit ID: ";
        IDExit = inputT(1);
        if (newNetWork.getCS().find(IDEntry) != newNetWork.getCS().end() &&
            newNetWork.getCS().find(IDExit) != newNetWork.getCS().end() &&
            IDEntry != IDExit)
            break;
        cout << "There are no such IDs. Enter another ID\n";
    }
    cout << "Enter diametr of pipe: ";
    diameter = inputT(1);
    while (1) {
        if (!checkPipeD(diameter)) {
            diameter= inputT(1);
        }
        else break;
    }
}

bool hasCycleDFS(vector<vector<int>>& graph, int node, vector<bool>& visited, vector<bool>& recursionStack) {
    visited[node] = true;
    recursionStack[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor] && hasCycleDFS(graph, neighbor, visited, recursionStack)) {
            return true;
        }
        else if (recursionStack[neighbor]) {
            return true;
        }
    }
    recursionStack[node] = false;
    return false;
}

vector<vector<int>> createMatrix(unordered_map<int, edge>& graphG, int numNodes) {
    vector<vector<int>> matrix(numNodes);
    for (auto& [key, p] : graphG) {
        matrix[p.IDExit - 1].push_back(p.IDEntry - 1);
    }
    return matrix;
}

bool hasCycle(vector<vector<int>>& graph, int numNodes) {
    vector<bool> visited(numNodes, false);
    vector<bool> recursionStack(numNodes, false);

    for (int i = 0; i < numNodes; i++) {
        if (!visited[i] && hasCycleDFS(graph, i, visited, recursionStack)) {
            return true;
        }
    }
    return false;
}

void topologicalSort(vector<vector<int>>& Graph, int node, vector<bool>& visited, vector<int>& recursionStack) {
    visited[node] = true;
    for (int neighbor : Graph[node])
        if (!visited[neighbor])
            topologicalSort(Graph, neighbor, visited, recursionStack);
    recursionStack.push_back(node);
}

void Sort(unordered_map<int, edge>& graphG, netWork& newNetWork, vector<int>& deletedCS) {
    vector<vector<int>>matrix = createMatrix(graphG, newNetWork.getCS().size());
    vector<int> resOfTop;
    if (hasCycle(matrix, newNetWork.getCS().size())) {
        cout << "Graph has a cicle" << endl;
    }
    else {
        cout << "Graph does not have a cicle" << endl;
        vector<bool>visited(newNetWork.getCS().size());
        for (int node = 0; node < newNetWork.getCS().size(); node++)
            if (!visited[node])
                topologicalSort(matrix, node, visited, resOfTop);

        reverse(resOfTop.begin(), resOfTop.end());
        for (int i = 0; i < deletedCS.size(); i++) {
            for (int j = 0; j < resOfTop.size(); j++) {
                if (resOfTop[j] + 1 >= deletedCS[i]) resOfTop[j]++;
            }
        }
        for (int node : resOfTop) {
            cout << node + 1 << " ";
        }
        cout << endl;
    }
}

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("logging.txt");
    if (logfile)
        cerr_out.redirect(logfile);

    unordered_map<int, edge> graphG;
    vector <int> usedPipe;
    vector <int> deletedCS;
    netWork newNetWork;
    /*unordered_map<int, PipeLine> pipes;
    unordered_map<int, CompressorStation> stations;*/

    while (1)
    {
        PrintMenu();
        int i = CorrectInput(0, 14);
        switch (i)
        //switch (CorrectInput(0, 12))
        {
        case 1:
        {
            //PipeLine pipe; //location 
            //cin >> pipe;
            //pipes.insert({ pipe.getPipeID(), pipe });
            newNetWork.addPipe();
            break;
        }
        case 2:
        {
            /*CompressorStation station;
            cin >> station;*/
            //stations.insert({station.getStationID(), station});
            newNetWork.addCS();
            break;
        }
        case 3:
        {
            /*for (auto& i : pipes) {
                cout << i.second << endl;
            }
            for (auto& i : stations) {
                cout << i.second << endl;
            }
            break;*/
            newNetWork.printAllObj();
            for (auto const& edge : graphG) {
                graphG[edge.first].printEdge();
            }
            break;
        }

        case 4:
        {
            editPipe(newNetWork);
            break;
        }
        case 5:
        {
            editCS(newNetWork);
            break;
        }
        case 6:
        {
            /*cout << "Type name fail: ";
            string in_file;
            cin >> in_file;
            ofstream fout(in_file);
            if (pipes.empty()) {
                cout << "no pipe" << endl;
            }
            if (stations.empty()) {
                cout << "no CS" << endl;
            }
            for (auto const& pipe : pipes) {
                if (!pipe.second.namePipe.size()) {
                    pipes[pipe.first].savePipe(fout);
                }
            }
            for (auto const& cs : stations) {
                if (!cs.second.nameCompressorStation.size()) {
                    stations[cs.first].saveCS(fout);
                }
            }*/
            SaveToFile(newNetWork, graphG);
            break;
        }
        case 7:
        {
            /*cout << "Type name fail: ";
            string read_file;
            cin >> read_file;
            ifstream read(read_file);
            string marker;
            while (getline(read, marker)) {
                if (marker == "PIPE") {
                    PipeLine read_pipe;
                    read_pipe.loadPipe(read);
                    pipes.insert({ read_pipe.getPipeID(), read_pipe });
                }
                if (marker == "CS") {
                    CompressorStation read_ks;
                    read_ks.loadCS(read);
                    stations.insert({ read_ks.getStationID(), read_ks });
                }
             
            }*/
            loadFromFile(newNetWork, usedPipe, graphG);
            break;
        }
        case 8:
        {
            int index = SelectPipe(newNetWork);
            for (auto& [ind, edge] : graphG) {
                if (newNetWork.getPipe()[index].getDiameter()  == edge.diameter && index == edge.ID)
                {
                    graphG.erase(ind);
                    break;
                }
            }
            newNetWork.deletePipe(index);
            break;
        }
        case 9:
        {
            vector<int> deleteEdge;
            int index = SelectCS(newNetWork);
            for (auto& [ind, edge] : graphG) {
                if (index == edge.IDEntry || index == edge.IDExit)
                {
                    deleteEdge.push_back(ind);
                }
            }
            for (int i = 0; i < deleteEdge.size(); i++) {
                graphG.erase(deleteEdge[i]);
            }
            deletedCS.push_back(index);
            newNetWork.deleteCS(index);
            break;
        }
        case 10:
        {
            int IDEntry, IDExit, diam;
            bool flag = 0;
            requestForParameters(IDEntry, IDExit, diam, newNetWork);
            while (1)
            {
                vector <int> res = findPipeByDiam(newNetWork, diam);
                for (auto& p : res) {
                    bool pipeInUse = (find(usedPipe.begin(), usedPipe.end(), p) != usedPipe.end());
                    if (!pipeInUse) {
                        edge newEdge;
                        newEdge.addEdge(IDEntry, IDExit, newNetWork.getPipe()[p]);
                        graphG.insert(pair<int, edge>(edge::maxIdG, newEdge));
                        usedPipe.push_back(p);
                        flag = 1;
                        break;
                    }
                }
                if (flag) {
                    break;
                }
                newNetWork.addPipe();
            }
            for (auto& [key, p] : graphG) {
                p.printEdge();
            }
            break;
        }
        case 11:
        {
            Sort(graphG, newNetWork, deletedCS);
            break;
        }
        //case 12:
        //{
        //    unordered_set<int> pipesID = PackEdit(newNetWork);//будет использоваться для хранения идентификаторов (ID) трубопроводов
        //    bool flag = true;
        //    while (flag) {
        //        EditMenu();
        //        switch (CorrectInput(0, 4))
        //        {
        //        case 1: {
        //            pipesID.clear();
        //            bool flag = true;
        //            while (flag)
        //            {
        //                cout << "Input ID of pipeline or 0 to complete: ";
        //                int id;
        //                id = Correct(PipeLine::ID, 0);
        //                if (id) {
        //                    if (CheckID(pipes, id)) {
        //                        PrintFoundPipes(id, pipes);
        //                        pipesID.insert(id);
        //                    }
        //                    else {
        //                        cout << "No pipeline with such ID" << endl;
        //                    }
        //                }
        //                else {
        //                    break;
        //                }
        //            }
        //            break;
        //        }
        //        case 2: {
        //            for (const int& id : pipesID) {
        //                EditPipeline(pipes, id);
        //            }
        //            break;
        //        }
        //        case 3: {
        //            for (const int& id : pipesID) {
        //                DeletePipe(pipes, id);

        //            }
        //            break;
        //        }
        //        case 4: {
        //            for (auto& i : pipes) {
        //                cout << i.second << endl;
        //            }
        //            break;
        //        }
        //        case 0: {
        //            flag = false;
        //            break;
        //        }
        //        }
        //    }
        //    break;
        //}
        case 0:
        {
            return 0;
        }
        }
    }
    return 0;
}