#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename T>
//menu
T GetCorrectNumber(T min, T max ) {
    T x;
    while ((cin >> x).fail() || x < min || x > max)
    {
        cin.clear();//сбрасываем биты ошибок и буфер
        cin.ignore(1000000, '\n');//сбрасываем до какого-то символа
        cout << "Type again " << min << "-" << max << ":";
    }
    return x; 
}

struct Pipe {
    string namePipe;
    double length;
    double diameter;
    bool InRepairs;
};

struct CompressorStation {
    string nameCompressorStation;
    int numberWorkshop;
    int numberWorkshopJob;
    double performance;

};



//считывание из файла
void LoadPipe(Pipe& p) {

    ifstream fin;
    string f;
    bool flag = 0;
    fin.open("file.txt", ios::in);

    if (fin.is_open())
    {
        while (!fin.eof()) {
            fin >> f;
            if (f == "PIPE") {
                fin >> ws;
                getline(fin, p.namePipe);
                fin >> p.length;
                fin >> p.diameter;
                fin >> p.InRepairs;
                fin.close();
                flag = 1;
                break;
            }
        }
        if (!flag) cout << "Save data Pipe in file" << endl;
    }
    else {
        cout << "Error" << endl;
    }

}

void LoadCS(CompressorStation& cs) {

    ifstream fin;
    string f;
    bool flag = 0;
    fin.open("file.txt", ios::in);

    if (fin.is_open())
    {
        while (!fin.eof()) {
            fin >> f;
            if (f == "Station") {
                fin >> ws;
                getline(fin, cs.nameCompressorStation);
                fin >> cs.numberWorkshop;
                fin >> cs.numberWorkshopJob;
                fin >> cs.performance;
                fin.close();
                flag = 1;
                break;
            }
        }
        if (!flag) cout << "Save data Compressor Station in file" << endl;
    }
    else {
        cout << "Error" << endl;
    }

}



void SaveAll(const Pipe& p, const CompressorStation& cs) {
    ofstream fout;
    fout.open("file.txt", ios::out);
    if (fout.is_open())
    {
        if (p.namePipe == "" && cs.nameCompressorStation == "") cout << "Enter data " << endl;
        else {
            if (p.namePipe != "") {
                //fout << "PIPE" << p.name << "\nName pipe: " << p.namePipe << "\nLength: " << p.length << "\nDiameter: " << p.diameter << "\nIn repairs: " << p.InRepairs << endl;
                fout << "PIPE" << endl << p.namePipe << endl <<  p.length << endl <<  p.diameter << endl <<  p.InRepairs << endl;

                
            }
            if (cs.nameCompressorStation != "") {
                fout << "Station" << endl << cs.nameCompressorStation << endl << cs.numberWorkshop << endl << cs.numberWorkshopJob << endl << cs.performance << endl;
                
            }

        }fout.close();
    }
}

void PrintMenu() {
    cout << "1. Add Pipe " << endl
        << "2. Add Compressor Station " << endl
        << "3. View all objects " << endl
        << "4. Edit pipe " << endl
        << "5. Edit Compressor Station " << endl
        << "6. Save " << endl
        << "7. Load " << endl
        << "0. Exit " << endl
        << "Choose action: ";
}

//оператор ввода
istream& operator >> (istream& in, Pipe& p)
{
    cout << "Type name pipe: ";
    cin.ignore(10000, '\n');//сбрасываем до какого-то символа
    getline(cin, p.namePipe);

    cout << "Type pipe length: ";
    p.length = GetCorrectNumber(1, 20000);
    cout << "Type pipe diameter: ";
    p.diameter = GetCorrectNumber(1, 20000);

    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Pipe under repair? ";
        cin >> p.InRepairs;
    }while (cin.fail());

    return in;
}

istream& operator >> (istream& in, CompressorStation& cs)
{
    cout << "Type name compressor station: ";
    cin.ignore(10000, '\n');
    getline(cin, cs.nameCompressorStation);

    cout << "Type number Workshop: ";
    cs.numberWorkshop = GetCorrectNumber(1, 20000);

    do {
        cout << "Type number Workshop in job: ";
        cs.numberWorkshopJob = GetCorrectNumber(1, 20000);
    } while (cin.fail() || cs.numberWorkshopJob < 0 || cs.numberWorkshopJob > cs.numberWorkshop);

    
    cout << "Type station performance: ";
    cs.performance = GetCorrectNumber(0, 100);

    return in;
}

//оператор вывода
ostream& operator << (ostream& out, const Pipe& p)
{
    if (p.namePipe != "") {
        out << "Name pipe: " << p.namePipe << "\nLength: " << p.length << "\nDiameter: " << p.diameter << "\nIn repairs: " << p.InRepairs << endl;
    }
    else {
        cout << "No data pipe" << endl;
    }
    return out;
}

ostream& operator << (ostream& out, const CompressorStation& cs)
{
    if (cs.nameCompressorStation != "") {
        out << "Name CS: " << cs.nameCompressorStation << "\nNumber workshop: " << cs.numberWorkshop << "\nNumber workshop in job: " << cs.numberWorkshopJob << "\nPerformance: " << cs.performance << endl;
    }
    else {
        cout << "No data Compressor Station" << endl;
    }
    return out;

}

//редактирование
void EditPipe(Pipe& p) {
    p.InRepairs = !p.InRepairs;
}

bool InputBool() {
    bool state;
    while (!(cin >> state)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Try again: ";
    }
    return state;
}

void EditCS(CompressorStation& cs) {
    if (cs.nameCompressorStation != "") {
        cout << " Start one workshop - ' 1', stop - '0': " << endl;
        bool sign = InputBool();
        if (sign == 1) {
            if (cs.numberWorkshopJob == cs.numberWorkshop) cout << "all workshops are working" << endl;
            else cs.numberWorkshopJob++;
        }
        else {
            if (cs.numberWorkshopJob == 0) cout << "all workshops are sopped" << endl;
            else cs.numberWorkshopJob--;
        }

    }
    else cout << "No data of Compressor Station" << endl;
}

int main()
{
    Pipe pipe1;
    CompressorStation station;
    while (1)
    {
        PrintMenu();
        switch (GetCorrectNumber(0,7))
        {
        case 1:
        {
            cin >> pipe1;
            break;
        }
        case 2:
        {
            cin >> station;
            break;
        }
        case 3:
        {
            cout << pipe1;
            cout << station;
            break;
        }
        
        case 4:
        {
            if (pipe1.namePipe != "") { 
                EditPipe(pipe1); 
            }
            else cout << "No data of Pipe" << endl;
            break;
        }
        case 5:
        {
            EditCS(station);
            break;
        }
        case 6:
        {
            SaveAll(pipe1, station);
            break;
        }
        case 7:
        {
            LoadPipe(pipe1);
            LoadCS(station);
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "wrong action" << endl;
        }
        }

    }
    return 0; 
}
