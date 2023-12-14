#pragma once
#include <string>
#include <fstream>


class PipeLine
{
    int id;
    double length;
    double diameter;
public:
    static void Reset();
    static int ID;
    std::string namePipe;
    bool InRepairs;
    void loadPipe(std::ifstream& fin);
    void savePipe(std::ofstream& fout);

    PipeLine();

    int getPipeID() const;

    friend std::istream& operator >> (std::istream& in, PipeLine& pipe);
    friend std::ostream& operator << (std::ostream& out, const PipeLine& pipe);
};

