#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

template <typename T>
//menu
T GetCorrectNumber(T min, T max ) {
    T x;
    while ((cin >> x).fail() || x < min || x > max)
    {
        cin.clear();//сбрасываем биты ошибок и буфер
        cin.ignore(1000000, '\n');//сбрасываем до какого-то символа
        cout << "Type number (" << min << "-" << max << "):";
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
void Load(Pipe& p, CompressorStation& cs) {
    ifstream fin;
    fin.open("file.txt", ios::in);

    if (fin.is_open())
    {
        fin >> p.namePipe;
        fin >> p.length;
        fin >> p.diameter;
        fin >> p.InRepairs;
        fin >> cs.nameCompressorStation;
        fin >> cs.numberWorkshop;
        fin >> cs.numberWorkshopJob;
        fin >> cs.performance;
        fin.close();
    }
}

//запись в файл
void Save(const Pipe& p, const CompressorStation& cs) {
    ofstream fout;
    fout.open("file.txt", ios::out);
    if (fout.is_open())
    {
        fout << "Name pipe: " << p.namePipe << "\nLength: " << p.length << "\nDiameter: " << p.diameter << "\nIn repairs: " << p.InRepairs << endl << endl;
        fout << "Name CS: " << cs.nameCompressorStation << "\nNumber workshop: " << cs.numberWorkshop << "\nNumber workshop in job: " << cs.numberWorkshopJob << "\nPerformance: " << cs.performance << endl;
        fout.close();
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

    /*if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
    }*/

    do {
        cin.clear();//сбрасываем биты ошибок и буфер
        cin.ignore(10000, '\n');
        cout << "Type pipe length: ";
        cin >> p.length;
        
    } while (cin.fail() || p.length < 0);

    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type pipe diameter: ";
        cin >> p.diameter;
    }while (cin.fail() || p.diameter < 0);

    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Pipe under repair? ";
        cin >> p.InRepairs;
    }while (cin.fail() || (p.InRepairs != 0 && p.InRepairs != 1));
    return in;
}

istream& operator >> (istream& in, CompressorStation& cs)
{
    cout << "Type name compressor station: ";
    cin.ignore(10000, '\n');
    getline(cin, cs.nameCompressorStation);

    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number Workshop: ";
        cin >> cs.numberWorkshop;
    } while (cin.fail() || cs.numberWorkshop < 0);

    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type number Workshop in job: ";
        cin >> cs.numberWorkshopJob;
    } while (cin.fail() || cs.numberWorkshopJob < 0 || cs.numberWorkshopJob > cs.numberWorkshop);

    do {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type station performance: ";
        cin >> cs.performance;
    } while (cin.fail() || cs.performance < 0 || cs.performance > 100);
    return in;
}

//оператор вывода
ostream& operator << (ostream& out, const Pipe& p)
{
    out << "Name pipe: " << p.namePipe << "\nLength: " << p.length << "\nDiameter: " << p.diameter << "\nIn repairs: " << p.InRepairs << endl << endl;
    return out;
}

ostream& operator << (ostream& out, const CompressorStation& cs)
{
    out << "Name CS: " << cs.nameCompressorStation << "\nNumber workshop: " << cs.numberWorkshop << "\nNumber workshop in job: " << cs.numberWorkshopJob << "\nPerformance: " << cs.performance << endl << endl;
    return out;

}

//редактирование
void EditPipe(Pipe& p) {
    p.InRepairs = !p.InRepairs;
}


//void EditCS(CompressorStation& cs) {
//    cout << " Start one workshop - ' 1', stop - '0': " << endl;
//    bool sign = numberWorkshopJob();
//    if (sign == 1) {
//        if () cout << "all workshops are working" << endl;
//        else ++;
//    }
//    else {
//        if () cout << "all workshops are sopped" << endl;
//        else cs. --;
//    }
//}

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
            EditPipe(pipe1);
            break;
        }
        case 5:
        {
            //EditCS(station);
            break;
        }
        case 6:
        {
            Save(pipe1, station);
            break;
        }
        case 7:
        {
            Load(pipe1, station);
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
