#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "PipeLine.h"
#include "utils.h"
#include <unordered_set>
#include <filesystem>
#include "CompressorStation.h"

using namespace std;

//поиск ID
template <typename type>
bool CheckID(const unordered_map<int, type>& x, const int& id)
{
    return (x.find(id) != x.end());
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

//редактирование трубы
void EditPipe(unordered_map<int, PipeLine>& pipes) {
    cout << "Type pipeline ID for editing: ";
    int id;
    id = CorrectIntID();
    if (CheckID(pipes, id)) {
        pipes[id].InRepairs = !(pipes[id].InRepairs);
    }
    else {
        cout << "No pipeline with such ID" << endl;
    }
}

///редактирование станции
void EditCS(unordered_map<int, CompressorStation>& stations) {
    cout << "Type compressor station ID for editing: ";
    int id;
    id = CorrectIntID();
    if (CheckID(stations, id)) {
        string decision;
        cout << "Type \"1\", if you want to start one workshop,type \"2\" - if you want to stop one workshop: ";
        std::cin >> decision;
        if (decision == "1" && stations[id].numberWorkshopJob < stations[id].getNumberWorkshop()) {
            stations[id].numberWorkshopJob++;
        }
        if (decision == "2" && stations[id].numberWorkshopJob > 0) {
            stations[id].numberWorkshopJob--;
        }
        cerr << decision << endl;
    }
    else {
        cout << "No compressor station with such ID" << endl;
    }
}



// поиск трубы по фильтру
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
        << "10. Find Pipe " << endl
        << "11. Find Compressor Station " << endl
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

void PrintFoundPipes(const int& id, unordered_map<int, PipeLine>& pipes) {
    cout << pipes[id];
}

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


unordered_set<int> PackEdit(unordered_map<int, PipeLine>& pipes) {
    unordered_set<int> pipesID{};
    FindMenu();
    switch (CorrectInput(1, 2)) {
    case 1: {
        string name;
        cout << "Input pileline name for searching: ";
        Save(cin, name);
        for (int id : FindPipelinesByFilter(pipes, CheckByName, name)) {
            PrintFoundPipes(id, pipes);
            pipesID.insert(id);
        }
        break;
    }
    case 2: {
        bool flag;
        cout << "Input station status for searching: ";
        flag = CorrectInput(false, true);
        for (int id : FindPipelinesByFilter(pipes, CheckByRepair, flag)) {
            PrintFoundPipes(id, pipes);
            pipesID.insert(id);
        }
        break;
    }
    }
    return pipesID;
}


//
int main()
{
    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile("logging.txt");
    if (logfile)
        cerr_out.redirect(logfile);

    unordered_map<int, PipeLine> pipes;
    unordered_map<int, CompressorStation> stations;

    while (1)
    {
        PrintMenu();
        switch (CorrectInput(0, 12))
        {
        case 1:
        {
            PipeLine pipe; //location 
            cin >> pipe;
            pipes.insert({ pipe.getPipeID(), pipe });
            break;
        }
        case 2:
        {
            CompressorStation station;
            cin >> station;
            stations.insert({ station.getStationID(), station });
            break;
        }
        case 3:
        {
            for (auto& i : pipes) {
                cout << i.second << endl;
            }
            for (auto& i : stations) {
                cout << i.second << endl;
            }
            break;
        }

        case 4:
        {
            EditPipe(pipes);
            break;
        }
        case 5:
        {
            EditCS(stations);
            break;
        }
        case 6:
        {
            cout << "Type name fail: ";
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
            }
            break;
        }
        case 7:
        {
            cout << "Type name fail: ";
            string read_file;
            cin >> read_file;
            ifstream read(read_file);
            //if (read.peek() == std::ifstream::traits_type::eof()) {
            //    cout << "Error\n";
            //    //break;
            //}
            //else {
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
                //}
            }
            break;
        }
        case 8:
        {
            cout << "Type pipeline ID for delete: ";
            int id;
            id = CorrectIntID();
            if (CheckID(pipes, id)) {
                DeletePipe(pipes, id);
            }
            else {
                cout << "No pipeline with such ID" << endl;
            }
            break;
        }
        case 9:
        {
            DeleteStation(stations);
            break;
        }
        case 10:
        {
            FindPipeLine(pipes);
            break;
        }
        case 11:
        {
            FindCS(stations);
            break;
        }
        case 12:
        {
            unordered_set<int> pipesID = PackEdit(pipes);//будет использоваться для хранения идентификаторов (ID) трубопроводов
            bool flag = true;
            while (flag) {
                EditMenu();
                switch (CorrectInput(0, 4))
                {
                case 1: {
                    pipesID.clear();
                    bool flag = true;
                    while (flag)
                    {
                        cout << "Input ID of pipeline or 0 to complete: ";
                        int id;
                        id = Correct(PipeLine::ID, 0);
                        if (id) {
                            if (CheckID(pipes, id)) {
                                PrintFoundPipes(id, pipes);
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
                    break;
                }
                case 2: {
                    for (const int& id : pipesID) {
                        EditPipeline(pipes, id);
                    }
                    break;
                }
                case 3: {
                    for (const int& id : pipesID) {
                        DeletePipe(pipes, id);

                    }
                    break;
                }
                case 4: {
                    for (auto& i : pipes) {
                        cout << i.second << endl;
                    }
                    break;
                }
                case 0: {
                    flag = false;
                    break;
                }
                }
            }
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
    return 0;
}